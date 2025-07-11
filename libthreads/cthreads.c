/*
 * Mach Operating System
 * Copyright (c) 1992,1991,1990,1989 Carnegie Mellon University
 * All Rights Reserved.
 *
 * Permission to use, copy, modify and distribute this software and its
 * documentation is hereby granted, provided that both the copyright
 * notice and this permission notice appear in all copies of the
 * software, derivative works or modified versions, and any portions
 * thereof, and that both notices appear in supporting documentation.
 *
 * CARNEGIE MELLON ALLOWS FREE USE OF THIS SOFTWARE IN ITS "AS IS"
 * CONDITION.  CARNEGIE MELLON DISCLAIMS ANY LIABILITY OF ANY KIND FOR
 * ANY DAMAGES WHATSOEVER RESULTING FROM THE USE OF THIS SOFTWARE.
 *
 * Carnegie Mellon requests users of this software to return to
 *
 *  Software Distribution Coordinator  or  Software.Distribution@CS.CMU.EDU
 *  School of Computer Science
 *  Carnegie Mellon University
 *  Pittsburgh PA 15213-3890
 *
 * any improvements or extensions that they make and grant Carnegie Mellon
 * the rights to redistribute these changes.
 */
/*
 * 	File:	cthreads.c
 *	Author:	Eric Cooper, Carnegie Mellon University
 *	Date:	July, 1987
 *
 * 	Implementation of fork, join, exit, etc.
 */

#include "cthread_internals.h"
#define T_MAIN 0x1
#define T_RETURNED 0x2
#define T_DETACHED 0x4

#if defined(DEBUG)
#endif /* defined(DEBUG) */
private cthread_t free_cthreads = NO_CTHREAD;          /* free list */
private spin_lock_t free_lock = SPIN_LOCK_INITIALIZER; /* unlocked */
private struct cthread initial_cthread = {0};
/**
 * @brief Allocate and initialize a cthread structure.
 *
 * @param func Entry point for the new thread.
 * @param arg  Argument to pass to the entry point.
 * @return Newly allocated cthread.
 */
private cthread_t cthread_alloc(cthread_fn_t func, void *arg) {
  register cthread_t t = NO_CTHREAD;

  if (free_cthreads != NO_CTHREAD) {
    /*
     * Don't try for the lock unless
     * the list is likely to be nonempty.
     * We can't be sure, though, until we lock it.
     */
    spin_lock(&free_lock);
    t = free_cthreads;
    if (t != NO_CTHREAD)
      free_cthreads = t->next;
    spin_unlock(&free_lock);
  }
  if (t == NO_CTHREAD) {
    /*
     * The free list was empty.
     * We may have only found this out after
     * locking it, which is why this isn't an
     * "else" branch of the previous statement.
     */
    t = (cthread_t)malloc(sizeof(struct cthread));
  }
  *t = initial_cthread;
  mutex_init(&t->lock);
  condition_init(&t->done);
  t->func = func;
  t->arg = arg;
  return t;
/**
 * @brief Return a cthread structure to the free list.
 *
 * @param t The cthread to recycle.
 */
private void cthread_free(cthread_t t) {
  spin_lock(&free_lock);
  t->next = free_cthreads;
  free_cthreads = t;
  spin_unlock(&free_lock);
/**
 * @brief Initialize the cthreads subsystem.
 *
 * @return Stack pointer for the initial thread.
 */
  static int cthreads_started = FALSE;
  register cproc_t p;
  register cthread_t t;
  vm_offset_t stack;
  if (cthreads_started)
    return 0;
  malloc_init();
  stack = cproc_init();
  cthread_cprocs = 1;
  t = cthread_alloc((cthread_fn_t)0, (void *)0);
  cthread_md_init();
  cthread_cthreads = 1;
  t->state |= T_MAIN;
  cthread_set_name(t, "main");
  /* cproc_self() doesn't work yet, because
     we haven't yet switched to the new stack. */
  p = *(cproc_t *)&ur_cthread_ptr(stack);
  p->incarnation = t;
  mig_init(p); /* enable multi-threaded mig interfaces */
  cthreads_started = TRUE;
  return stack;
}

/**
 * @brief Main loop executed by all worker cprocs.
 *
 * @param self The cproc executing the loop.
 */
void cthread_body(cproc_t self) {
  register cthread_t t;

  ASSERT(cproc_self() == self);
  TRACE(printf("[idle] cthread_body(%x)\n", self));
  mutex_lock(&cthread_lock);
  for (;;) {
    /*
     * Dequeue a thread invocation request.
     */
    cthread_queue_deq(&cthreads, cthread_t, t);
    if (t != NO_CTHREAD) {
      /*
       * We have a thread to execute.
       */
      mutex_unlock(&cthread_lock);
      cthread_assoc(self, t);            /* assume thread's identity */
      if (_setjmp(t->catch_exit) == 0) { /* catch for cthread_exit() */
        /*
         * Execute the fork request.
         */
        t->result = (*(t->func))(t->arg);
      }
      /*
       * Return result from thread.
       */
      TRACE(printf("[%s] done()\n", cthread_name(t)));
      mutex_lock(&t->lock);
      if (t->state & T_DETACHED) {
        mutex_unlock(&t->lock);
        cthread_free(t);
      } else {
        t->state |= T_RETURNED;
        mutex_unlock(&t->lock);
        condition_signal(&t->done);
      }
      cthread_assoc(self, NO_CTHREAD);
      mutex_lock(&cthread_lock);
      cthread_cthreads -= 1;
    } else {
      /*
       * Queue is empty.
       * Signal that we're idle in case the main thread
       * is waiting to exit, then wait for reincarnation.
       */
      condition_signal(&cthread_idle);
      condition_wait(&cthread_needed, &cthread_lock);
    }
  }
cthread_t cthread_fork(cthread_fn_t func, void *arg)
/**
 * @brief Spawn a new cthread.
 *
 * @param func Entry point of the new thread.
 * @param arg  Argument to the entry function.
 * @return Handle for the created thread.
 */
  register cthread_t t;

  TRACE(printf("[%s] fork()\n", cthread_name(cthread_self())));
  mutex_lock(&cthread_lock);
  t = cthread_alloc(func, arg);
  cthread_queue_enq(&cthreads, t);
  if (++cthread_cthreads > cthread_cprocs &&
      (cthread_max_cprocs == 0 || cthread_cprocs < cthread_max_cprocs)) {
    cthread_cprocs += 1;
    cproc_create();
  }
  mutex_unlock(&cthread_lock);
  condition_signal(&cthread_needed);
  return t;
void cthread_detach(t)
    /**
     * @brief Detach a cthread so its resources are reclaimed automatically.
     *
     * @param t Thread to detach.
     */
    cthread_t t;
  TRACE(printf("[%s] detach(%s)\n", cthread_name(cthread_self()),
               cthread_name(t)));
  mutex_lock(&t->lock);
  if (t->state & T_RETURNED) {
    mutex_unlock(&t->lock);
    cthread_free(t);
  } else {
    t->state |= T_DETACHED;
    mutex_unlock(&t->lock);
  }
void *cthread_join(cthread_t t)
/**
 * @brief Wait for a thread to terminate and retrieve its result.
 *
 * @param t Thread to join.
 * @return Result value supplied to cthread_exit.
 */
  void *result;

  TRACE(
      printf("[%s] join(%s)\n", cthread_name(cthread_self()), cthread_name(t)));
  mutex_lock(&t->lock);
  ASSERT(!(t->state & T_DETACHED));
  while (!(t->state & T_RETURNED))
    condition_wait(&t->done, &t->lock);
  result = t->result;
  mutex_unlock(&t->lock);
  cthread_free(t);
  return result;
/**
 * @brief Terminate the current thread.
 *
 * @param result Value returned to any joiner.
 */
  register cthread_t t = cthread_self();

  TRACE(printf("[%s] exit()\n", cthread_name(t)));
  t->result = result;
  if (t->private_data != 0) {
    free((char *)t->private_data);
    t->private_data = 0;
  }
  if (t->state & T_MAIN) {
    mutex_lock(&cthread_lock);
    while (cthread_cthreads > 1)
      condition_wait(&cthread_idle, &cthread_lock);
    mutex_unlock(&cthread_lock);
    exit((int)result);
  } else {
    _longjmp(t->catch_exit, TRUE);
  }
int (*_cthread_exit_routine)() = (int (*)())cthread_exit;
/**
 * @brief Assign a human readable name to a thread.
 *
 * @param t    Thread to rename.
 * @param name Null terminated thread name.
 */
  t->name = name;
/**
 * @brief Retrieve a thread's human readable name.
 *
 * @param t Thread whose name is requested.
 * @return The thread name or "?".
 */
const char *cthread_name(cthread_t t) {
  return (t == NO_CTHREAD ? "idle" : (t->name == 0 ? "?" : t->name));
/**
 * @brief Query the configured maximum number of cprocs.
 *
 * @return Current thread limit.
 */
  return cthread_max_cprocs;
/**
 * @brief Set the maximum number of underlying cprocs.
 *
 * @param n New thread limit.
 */
void cthread_set_limit(int n) { cthread_max_cprocs = n; }
/**
 * @brief Get the number of currently active threads.
 *
 * @return Active thread count.
 */
int cthread_count(void) { return cthread_cthreads; }
/**
 * @brief Prepare thread system for a process fork.
 */
  spin_lock(&free_lock);
  mutex_lock(&cthread_lock);
  /**
   * @brief Restore state in the parent after a fork.
   */
  malloc_fork_prepare();
  cproc_fork_prepare();
void cthread_fork_parent(void)
/**
 * @brief Reinitialize state in the child after a fork.
 */
{
  cproc_fork_parent();
  malloc_fork_parent();
  mutex_unlock(&cthread_lock);
  spin_unlock(&free_lock);
void cthread_fork_child(void) {
  cthread_t t;
  cproc_t p;

  malloc_fork_child();
  cproc_fork_child();
  mutex_unlock(&cthread_lock);
  spin_unlock(&free_lock);
  condition_init(&cthread_needed);
  condition_init(&cthread_idle);

  cthread_max_cprocs = 0;

  stack_fork_child();

  while (TRUE) { /* Free cthread runnable list */
    cthread_queue_deq(&cthreads, cthread_t, t);
    if (t == NO_CTHREAD)
      break;
    free((char *)t);
  }

  while (free_cthreads != NO_CTHREAD) { /* Free cthread free list */
    t = free_cthreads;
    free_cthreads = free_cthreads->next;
    free((char *)t);
  }

  cthread_cprocs = 1;
  t = cthread_self();
  cthread_cthreads = 1;
  t->state |= T_MAIN;
  cthread_set_name(t, "main");

  p = cproc_self();
  p->incarnation = t;
  mig_init(p); /* enable multi-threaded mig interfaces */
cthread_set_name(cthread_t t, const char *name)
{
	t->name = name;
}

const char *
cthread_name(cthread_t t)
{
	return (t == NO_CTHREAD ? "idle" : (t->name == 0 ? "?" : t->name));
}

int
cthread_limit(void)
{
	return cthread_max_cprocs;
}

void
cthread_set_limit(int n)
{
	cthread_max_cprocs = n;
}

int
cthread_count(void)
{
	return cthread_cthreads;
}

void
cthread_fork_prepare(void)
{
    spin_lock(&free_lock);
    mutex_lock(&cthread_lock);
    malloc_fork_prepare();
    cproc_fork_prepare();
}

void
cthread_fork_parent(void)
{
    cproc_fork_parent();
    malloc_fork_parent();
    mutex_unlock(&cthread_lock);
    spin_unlock(&free_lock);
}

void
cthread_fork_child(void)
{
    cthread_t t;
    cproc_t p;

    malloc_fork_child();
    cproc_fork_child();
    mutex_unlock(&cthread_lock);
    spin_unlock(&free_lock);
    condition_init(&cthread_needed);
    condition_init(&cthread_idle);

    cthread_max_cprocs = 0;

    stack_fork_child();

    while (TRUE) {		/* Free cthread runnable list */
	cthread_queue_deq(&cthreads, cthread_t, t);
	if (t == NO_CTHREAD) break;
	free((char *) t);
    }

    while (free_cthreads != NO_CTHREAD) {	/* Free cthread free list */
	t = free_cthreads;
	free_cthreads = free_cthreads->next;
	free((char *) t);
    }

    cthread_cprocs = 1;
    t = cthread_self();
    cthread_cthreads = 1;
    t->state |= T_MAIN;
    cthread_set_name(t, "main");

    p = cproc_self();
    p->incarnation = t;
    mig_init(p);		/* enable multi-threaded mig interfaces */
}
