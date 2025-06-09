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
 * 	File: 	malloc.c
 *	Author: Eric Cooper, Carnegie Mellon University
 *	Date:	July, 1988
 *
 * 	Memory allocator for use with multiple threads.
 */

#include <mach/cthreads.h>
#include <string.h>
  union header *next;
  struct free_list *fl;

#define MIN_SIZE 8 /* minimum block size */
  spin_lock_t lock; /* spin lock for mutual exclusion */
  header_t head;    /* head of free list for this size */
#if defined(DEBUG)
  int in_use; /* # mallocs - # frees */
#endif        /* defined(DEBUG) */
#define NBUCKETS 29
/**
 * @brief Initialize the thread-safe allocator.
 */
void malloc_init(void) {
  register int i;

  for (i = 0; i < NBUCKETS; i++)
    spin_lock_init(&malloc_free_list[i].lock);
/**
 * @brief Obtain additional memory from the system.
 *
 * @param size Allocation size.
 * @param fl   Free list to populate.
 */
static void more_memory(int size, register free_list_t fl) {
  register int amount;
  register int n;
  vm_address_t where;
  register header_t h;
  kern_return_t r;
  if (size <= vm_page_size) {
    amount = vm_page_size;
    n = vm_page_size / size;
    /*
     * We lose vm_page_size - n*size bytes here.
     */
  } else {
    amount = size;
    n = 1;
  }
  MACH_CALL(vm_allocate(mach_task_self(), &where, (vm_size_t)amount, TRUE), r);
  if (r == KERN_SUCCESS) {
    h = (header_t)where;
    do {
      h->next = fl->head;
      fl->head = h;
      h = (header_t)((char *)h + size);
    } while (--n != 0);
  } else {
    printf("more_memory: vm_allocate(x%x, &x%x, x%x, TRUE)->x%x\n",
           mach_task_self(), where, amount, r);
  }
/**
 * @brief Allocate memory from the thread-safe allocator.
 *
 * @param size Number of bytes requested.
 * @return Pointer to usable memory or NULL.
 */
void *malloc(register vm_size_t size) {
  register int i, n;
  register free_list_t fl;
  register header_t h;
  if (size == 0) /* sanity check */
    return 0;
  size += sizeof(union header);
  /*
   * Find smallest power-of-two block size
   * big enough to hold requested size plus header.
   */
  i = 0;
  n = MIN_SIZE;
  while (n < size) {
    i += 1;
    n <<= 1;
  }
  ASSERT(i < NBUCKETS);
  fl = &malloc_free_list[i];
  spin_lock(&fl->lock);
  h = fl->head;
  if (h == 0) {
    /*
     * Free list is empty;
     * allocate more blocks.
     */
    more_memory(n, fl);
    h = fl->head;
    if (h == 0) {
      /*
       * Allocation failed.
       */
      spin_unlock(&fl->lock);
      return 0;
    }
  }
  /*
   * Pop block from free list.
   */
  fl->head = h->next;
#if defined(DEBUG)
  fl->in_use += 1;
#endif /* defined(DEBUG) */
  spin_unlock(&fl->lock);
  /*
   * Store free list pointer in block header
   * so we can figure out where it goes
   * at free() time.
   */
  h->fl = fl;
  /**
   * @brief Free a block allocated by malloc.
   *
   * @param base Pointer returned by malloc or realloc.
   */
  /*
   * Return pointer past the block header.
   */
  return ((char *)h) + sizeof(union header);
void free(void *base) {
  register header_t h;
  register free_list_t fl;
  register int i;
  if (base == 0)
    return;
  /*
   * Find free list for block.
   */
  h = (header_t)((char *)base - sizeof(union header));
  fl = h->fl;
  i = fl - malloc_free_list;
  /*
   * Sanity checks.
   */
  if (i < 0 || i >= NBUCKETS) {
    ASSERT(0 <= i && i < NBUCKETS);
    return;
  }
  if (fl != &malloc_free_list[i]) {
    ASSERT(fl == &malloc_free_list[i]);
    return;
  }
  /*
   * Push block on free list.
/**
* @brief Reallocate a previously allocated block.
*
* @param old_base Existing allocation.
* @param new_size Desired new size.
* @return Pointer to reallocated memory or NULL.
*/
  */ spin_lock(&fl->lock);
  h->next = fl->head;
  fl->head = h;
#if defined(DEBUG)
  fl->in_use -= 1;
#endif /* defined(DEBUG) */
  spin_unlock(&fl->lock);
  return;
void *realloc(void *old_base, vm_size_t new_size) {
  register header_t h;
  register free_list_t fl;
  register int i;
  vm_size_t old_size;
  void *new_base;
  if (old_base == 0)
    return malloc(new_size);
  if (new_size == 0) {
    free(old_base);
    return 0;
  }
  /*
   * Find size of old block.
   */
  h = (header_t)((char *)old_base - sizeof(union header));
  fl = h->fl;
  i = fl - malloc_free_list;
  /*
   * Sanity checks.
   */
  if (i < 0 || i >= NBUCKETS) {
    ASSERT(0 <= i && i < NBUCKETS);
    return 0;
  }
  if (fl != &malloc_free_list[i]) {
    ASSERT(fl == &malloc_free_list[i]);
    return 0;
  }
  /*
   * Free list with index i contains blocks of size 2^(i+3) including header.
   */
  old_size = (1 << (i + 3)) - sizeof(union header);
  /*
   * Allocate new block, copy old bytes, and free old block.
   */
  new_base = malloc(new_size);
  if (new_base != 0) {
    memcpy(new_base, old_base, (old_size < new_size ? old_size : new_size));
    free(old_base);
  }
  return new_base;
#if defined(DEBUG)
/**
 * @brief Debug helper printing the malloc free list state.
 */
#endif /* defined(DEBUG) */

/**
 * @brief Prepare malloc for a process fork.
 */
  register int i;

  for (i = 0; i < NBUCKETS; i++) {
    spin_lock(&malloc_free_list[i].lock);
  }
/**
 * @brief Resume allocator operation in the parent after fork.
 */
  register int i;
  for (i = NBUCKETS - 1; i >= 0; i--) {
    spin_unlock(&malloc_free_list[i].lock);
  }
/**
 * @brief Resume allocator operation in the child after fork.
 */
  register int i;
  for (i = NBUCKETS - 1; i >= 0; i--) {
    spin_unlock(&malloc_free_list[i].lock);
  }
	i = fl - malloc_free_list;
	/*
	 * Sanity checks.
	 */
	if (i < 0 || i >= NBUCKETS) {
		ASSERT(0 <= i && i < NBUCKETS);
		return 0;
	}
	if (fl != &malloc_free_list[i]) {
		ASSERT(fl == &malloc_free_list[i]);
		return 0;
	}
	/*
	 * Free list with index i contains blocks of size 2^(i+3) including header.
	 */
	old_size = (1 << (i+3)) - sizeof(union header);
	/*
	 * Allocate new block, copy old bytes, and free old block.
	 */
	new_base = malloc(new_size);
	if (new_base != 0) {
		memcpy(new_base, old_base,
		      (old_size < new_size ? old_size : new_size));
		free(old_base);
	}
	return new_base;
}

#if	defined(DEBUG)
#if 0 /* XX change DEBUG to CTHREADS_DEBUG */
void
print_malloc_free_list(void)
{
  	register int i, size;
	register free_list_t fl;
	register int n;
  	register header_t h;
	int total_used = 0;
	int total_free = 0;

	/* fprintf(stderr, "      Size     In Use       Free      Total\n"); */
  	for (i = 0, size = MIN_SIZE, fl = malloc_free_list;
	     i < NBUCKETS;
	     i += 1, size <<= 1, fl += 1) {
		spin_lock(&fl->lock);
		if (fl->in_use != 0 || fl->head != 0) {
			total_used += fl->in_use * size;
			for (n = 0, h = fl->head; h != 0; h = h->next, n += 1)
				;
			total_free += n * size;
			/* fprintf(stderr, "%10d %10d %10d %10d\n",
				size, fl->in_use, n, fl->in_use + n); */
		}
		spin_unlock(&fl->lock);
  	}
  	/* fprintf(stderr, " all sizes %10d %10d %10d\n",
		total_used, total_free, total_used + total_free); */
}
#endif
#endif	/* defined(DEBUG) */

void malloc_fork_prepare(void)
/*
 * Prepare the malloc module for a fork by insuring that no thread is in a
 * malloc critical section.
 */
{
    register int i;
    
    for (i = 0; i < NBUCKETS; i++) {
	spin_lock(&malloc_free_list[i].lock);
    }
}

void malloc_fork_parent(void)
/*
 * Called in the parent process after a fork() to resume normal operation.
 */
{
    register int i;

    for (i = NBUCKETS-1; i >= 0; i--) {
	spin_unlock(&malloc_free_list[i].lock);
    }
}

void malloc_fork_child(void)
/*
 * Called in the child process after a fork() to resume normal operation.
 */
{
    register int i;

    for (i = NBUCKETS-1; i >= 0; i--) {
	spin_unlock(&malloc_free_list[i].lock);
    }
}
