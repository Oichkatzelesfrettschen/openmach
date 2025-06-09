/*
 * Mach Operating System
 * Copyright (c) 1992,1991 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */

#include <mach/cthreads.h>

#define NULL 0

#define CTHREAD_KEY_MAX (cthread_key_t)8 /* max. no. of keys */
#define CTHREAD_KEY_NULL (cthread_key_t)0

#if defined(CTHREAD_DATA)
/*
 *	Key reserved for cthread_data
 */
#define CTHREAD_KEY_RESERVED CTHREAD_KEY_NULL

#define CTHREAD_KEY_FIRST (cthread_key_t)1 /* first free key */
#else                                      /* not defined(CTHREAD_DATA) */
#define CTHREAD_KEY_FIRST CTHREAD_KEY_NULL /* first free key */
#endif                                     /* defined(CTHREAD_DATA) */

/* lock protecting key creation */
struct mutex cthread_data_lock = MUTEX_INITIALIZER;

/* next free key */
cthread_key_t cthread_key = CTHREAD_KEY_FIRST;

/**
 * @brief Create a key for thread-specific data.
 *
 * Different threads may use the same key, but each maintains its own value.
 *
 * @param key Returned key value.
 * @return 0 on success or -1 if no keys remain.
 */
int cthread_keycreate(cthread_key_t *key) {
  if (cthread_key >= CTHREAD_KEY_FIRST && cthread_key < CTHREAD_KEY_MAX) {
    mutex_lock((mutex_t)&cthread_data_lock);
    *key = cthread_key++;
    mutex_unlock((mutex_t)&cthread_data_lock);
    return (0);
  } else { /* out of keys */
    *key = CTHREAD_KEY_INVALID;
    return (-1);
  }
}

/**
 * @brief Retrieve private data associated with a key.
 *
 * @param key Key to look up.
 * @param value Location to store the result.
 * @return 0 on success or -1 if the key is invalid.
 */
int cthread_getspecific(cthread_key_t key, void **value) {
  register cthread_t self;
  register void **thread_data;

  *value = CTHREAD_DATA_VALUE_NULL;
  if (key < CTHREAD_KEY_NULL || key >= cthread_key)
    return (-1);

  self = cthread_self();
  thread_data = (void **)(self->private_data);
  if (thread_data != NULL)
    *value = thread_data[key];

  return (0);
}

/**
 * @brief Set private data associated with a key.
 *
 * @param key Key to set.
 * @param value Value to store.
 * @return 0 on success or -1 on failure.
 */
int cthread_setspecific(cthread_key_t key, void *value) {
  register int i;
  register cthread_t self;
  register void **thread_data;

  if (key < CTHREAD_KEY_NULL || key >= cthread_key)
    return (-1);

  self = cthread_self();
  thread_data = (void **)(self->private_data);
  if (thread_data != NULL)
    thread_data[key] = value;
  else {
    /*
     *	Allocate and initialize thread data table,
     *	point cthread_data at it, and then set the
     *	data for the given key with the given value.
     */
    thread_data = malloc(CTHREAD_KEY_MAX * sizeof(void *));
    if (thread_data == NULL) {
      printf("cthread_setspecific: malloc failed\n");
      return (-1);
    }
    self->private_data = thread_data;

    for (i = 0; i < CTHREAD_KEY_MAX; i++)
      thread_data[i] = CTHREAD_DATA_VALUE_NULL;

    thread_data[key] = value;
  }
  return (0);
}

#if defined(CTHREAD_DATA_XX)
/**
 * @brief Set thread specific "global" variable.
 *
 * Uses new POSIX routines and only operates on the calling thread.
 *
 * @param t Target thread, must equal the caller.
 * @param x New value.
 * @return 0 on success or -1 on failure.
 */
int cthread_set_data(cthread_t t, void *x) {
  register cthread_t self;

  self = cthread_self();
  if (t == self)
    return (cthread_setspecific(CTHREAD_KEY_RESERVED, x));
  else {
    ASSERT(t == self);
    return (-1);
  }
}

/**
 * @brief Retrieve thread specific "global" variable.
 *
 * Uses new POSIX routines and must be called by the target thread.
 */
void *cthread_data(cthread_t t) {
  register cthread_t self;
  void *value;

  self = cthread_self();
  if (t == self) {
    (void)cthread_getspecific(CTHREAD_KEY_RESERVED, &value);
    return (value);
  } else {
    ASSERT(t == self);
    return (NULL);
  }
}
#endif /* defined(CTHREAD_DATA_XX) */
