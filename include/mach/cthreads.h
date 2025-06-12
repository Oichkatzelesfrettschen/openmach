/* 
 * Mach Operating System
 * Copyright (c) 1993,1992,1991,1990,1989 Carnegie Mellon University
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
 * 	File: 	cthreads.h
 *	Author: Eric Cooper, Carnegie Mellon University
 *	Date:	Jul, 1987
 *
 * 	Definitions for the C Threads package.
 *
 */
/**
 * @file mach/cthreads.h
 * @brief Definitions for the C Threads package.
 *
 * This file provides the public interface for the C Threads library,
 * a user-level threads package. It includes definitions for thread management,
 * mutexes, condition variables, and basic queue operations.
 */

#ifndef	_CTHREADS_
#define	_CTHREADS_ 1

#include <mach/machine/cthreads.h> /* Low-level, machine-dependent cthread definitions */
#include <mach.h>		/* Mach kernel interface */
#include <mach/macro_help.h>	/* Macro utilities */
#include <mach/machine/vm_param.h> /* VM parameters */

#ifdef __STDC__
extern void *malloc(unsigned long size);
#else
extern char *malloc();
#endif

/**
 * @typedef any_t
 * @brief Generic pointer type.
 * @deprecated This type is obsolete and should be deleted. Use `void *` instead.
 */
typedef void *any_t;	    /* XXX - obsolete, should be deleted. */

#if	defined(TRUE)
#else	/* not defined(TRUE) */
/**
 * @def TRUE
 * @brief Boolean true value, typically 1.
 */
#define	TRUE	1
/**
 * @def FALSE
 * @brief Boolean false value, typically 0.
 */
#define	FALSE	0
#endif

/**
 * @name C Threads Package Initialization
 * @{
 */

/**
 * @brief Initializes the C Threads package.
 *
 * This function must be called before any other C Threads function.
 * It sets up the necessary data structures for thread management.
 * @return vm_offset_t Returns a vm_offset_t value, usage context dependent.
 * Typically, this is the initial stack pointer or a status code.
 */
extern vm_offset_t cthread_init(void);
/** @} */


/**
 * @name Queues
 * @{
 */

/**
 * @struct cthread_queue
 * @brief A simple queue structure for managing cthread_queue_item_t elements.
 */
typedef struct cthread_queue {
	struct cthread_queue_item *head; ///< Pointer to the head of the queue.
	struct cthread_queue_item *tail; ///< Pointer to the tail of the queue.
} *cthread_queue_t; ///< Pointer to a cthread_queue structure.

/**
 * @struct cthread_queue_item
 * @brief An item that can be placed on a cthread_queue.
 */
typedef struct cthread_queue_item {
	struct cthread_queue_item *next; ///< Pointer to the next item in the queue.
} *cthread_queue_item_t; ///< Pointer to a cthread_queue_item structure.

/**
 * @def NO_QUEUE_ITEM
 * @brief Represents a null or empty queue item.
 */
#define	NO_QUEUE_ITEM	((cthread_queue_item_t) 0)

/**
 * @def QUEUE_INITIALIZER
 * @brief An initializer for a cthread_queue structure.
 * Initializes head and tail to NO_QUEUE_ITEM.
 */
#define	QUEUE_INITIALIZER	{ NO_QUEUE_ITEM, NO_QUEUE_ITEM }

/**
 * @def cthread_queue_alloc()
 * @brief Allocates and initializes a new cthread_queue.
 * @return A pointer to the allocated cthread_queue_t, or NULL on failure.
 * Uses calloc for allocation.
 */
#define	cthread_queue_alloc()	((cthread_queue_t) calloc(1, sizeof(struct cthread_queue)))

/**
 * @def cthread_queue_init(q)
 * @brief Initializes an existing cthread_queue.
 * Sets head and tail to NULL.
 * @param q Pointer to the cthread_queue_t to initialize.
 */
#define	cthread_queue_init(q)	((q)->head = (q)->tail = 0)

/**
 * @def cthread_queue_free(q)
 * @brief Frees a cthread_queue allocated by cthread_queue_alloc().
 * @param q Pointer to the cthread_queue_t to free.
 */
#define	cthread_queue_free(q)	free((q))

/**
 * @def cthread_queue_enq(q, x)
 * @brief Enqueues an item at the tail of the queue.
 * @param q Pointer to the cthread_queue_t.
 * @param x Pointer to the cthread_queue_item_t to enqueue.
 */
#define	cthread_queue_enq(q, x) \
	MACRO_BEGIN \
		((cthread_queue_item_t)(x))->next = 0; \
		if ((q)->tail == 0) \
			(q)->head = (cthread_queue_item_t) (x); \
		else \
			(q)->tail->next = (cthread_queue_item_t) (x); \
		(q)->tail = (cthread_queue_item_t) (x); \
	MACRO_END

/**
 * @def cthread_queue_preq(q, x)
 * @brief Enqueues an item at the head of the queue (prepends).
 * @param q Pointer to the cthread_queue_t.
 * @param x Pointer to the cthread_queue_item_t to prepend.
 */
#define	cthread_queue_preq(q, x) \
	MACRO_BEGIN \
		if ((q)->tail == 0) \
			(q)->tail = (cthread_queue_item_t) (x); \
		((cthread_queue_item_t) (x))->next = (q)->head; \
		(q)->head = (cthread_queue_item_t) (x); \
	MACRO_END

/**
 * @def cthread_queue_head(q, t)
 * @brief Returns the head item of the queue without dequeuing it.
 * @param q Pointer to the cthread_queue_t.
 * @param t The type to cast the head item to.
 * @return The head item cast to type t, or NULL if the queue is empty.
 */
#define	cthread_queue_head(q, t)	((t) ((q)->head))

/**
 * @def cthread_queue_deq(q, t, x)
 * @brief Dequeues an item from the head of the queue.
 * @param q Pointer to the cthread_queue_t.
 * @param t The type to cast the dequeued item to.
 * @param x Output parameter; the dequeued item will be stored here, cast to type t.
 *          Set to NULL if the queue was empty.
 */
#define	cthread_queue_deq(q, t, x) \
	MACRO_BEGIN \
	if (((x) = (t) ((q)->head)) != 0 && \
	    ((q)->head = (cthread_queue_item_t) (((cthread_queue_item_t)(x))->next)) == 0) \
		(q)->tail = 0; \
	MACRO_END

/**
 * @def cthread_queue_map(q, t, f)
 * @brief Iterates over each item in the queue and applies a function.
 * The function `f` should not modify the queue structure (e.g., by dequeuing items).
 * @param q Pointer to the cthread_queue_t.
 * @param t The type to cast each item to before passing to the function `f`.
 * @param f The function to apply to each item. It should take one argument of type t.
 */
#define	cthread_queue_map(q, t, f) \
	MACRO_BEGIN \
		register cthread_queue_item_t x, next; \
		for (x = (cthread_queue_item_t) ((q)->head); x != 0; x = next){\
			next = x->next; \
			(*(f))((t) x); \
		} \
	MACRO_END
/** @} */

/**
 * @name Spin Locks
 * @{
 */

/**
 * @brief Acquires a spin lock, blocking if necessary.
 *
 * This function spins until the lock is acquired. This is a low-level
 * blocking call used if `spin_try_lock` fails.
 * @param _lock Pointer to the spin_lock_t object.
 */
extern void		spin_lock_solid(spin_lock_t *_lock);

#if	defined(spin_unlock)
/* spin_unlock is already defined (likely as a macro in machine/cthreads.h) */
#else	/* not defined(spin_unlock) */
/**
 * @brief Releases a spin lock.
 * @param _lock Pointer to the spin_lock_t object.
 */
extern void		spin_unlock(spin_lock_t *_lock);
#endif

#if	defined(spin_try_lock)
/* spin_try_lock is already defined (likely as a macro in machine/cthreads.h) */
#else	/* not defined(spin_try_lock) */
/**
 * @brief Attempts to acquire a spin lock without blocking.
 * @param _lock Pointer to the spin_lock_t object.
 * @return TRUE if the lock was acquired, FALSE otherwise.
 */
extern boolean_t	spin_try_lock(spin_lock_t *_lock);
#endif

/**
 * @def spin_lock(p)
 * @brief Acquires a spin lock.
 *
 * This macro first attempts a non-blocking `spin_try_lock`. If that fails,
 * it calls `spin_lock_solid` to block until the lock is acquired.
 * @param p Pointer to the spin_lock_t object.
 */
#define spin_lock(p) \
	MACRO_BEGIN \
	if (!spin_try_lock(p)) { \
		spin_lock_solid(p); \
	} \
	MACRO_END
/** @} */

/**
 * @name Mutex Objects
 * @{
 */

/**
 * @struct mutex
 * @brief Mutex object for synchronizing access to shared resources.
 *
 * Mutexes are built on top of spin locks and queues to provide
 * a blocking synchronization primitive.
 */
typedef struct mutex {
	spin_lock_t lock;		///< Spin lock protecting the mutex's internal data.
	const char *name;		///< Optional name for debugging.
	struct cthread_queue queue;	///< Queue of threads waiting for this mutex.
	spin_lock_t held;		///< Spin lock indicating if the mutex is currently held.
	/** For WAIT_DEBUG: pointer to the cthread holding the mutex.
	 *  Not ifdef'd to keep structure size constant.
	 */
	struct cthread *holder;
} *mutex_t; ///< Pointer to a mutex structure.

/**
 * @def MUTEX_INITIALIZER
 * @brief An initializer for a mutex structure.
 */
#define	MUTEX_INITIALIZER	{ SPIN_LOCK_INITIALIZER, 0, QUEUE_INITIALIZER, SPIN_LOCK_INITIALIZER, 0 }

/**
 * @def MUTEX_NAMED_INITIALIZER(Name)
 * @brief An initializer for a named mutex structure.
 * @param Name The string name for the mutex.
 */
#define	MUTEX_NAMED_INITIALIZER(Name) { SPIN_LOCK_INITIALIZER, Name, QUEUE_INITIALIZER, SPIN_LOCK_INITIALIZER, 0 }

#ifdef WAIT_DEBUG
/**
 * @def mutex_set_holder(m, h)
 * @brief Sets the holder field of the mutex (for debugging).
 * @param m Pointer to the mutex_t.
 * @param h Pointer to the cthread holding the mutex.
 */
#define mutex_set_holder(m,h)	((m)->holder = (h))
#else
#define mutex_set_holder(m,h)	/* Do nothing */
#endif

/**
 * @def mutex_alloc()
 * @brief Allocates and initializes a new mutex.
 * @return Pointer to the allocated mutex_t, or NULL on failure.
 * Uses calloc for allocation.
 */
#define	mutex_alloc()		((mutex_t) calloc(1, sizeof(struct mutex)))

/**
 * @def mutex_init(m)
 * @brief Initializes an existing mutex.
 * @param m Pointer to the mutex_t to initialize.
 */
#define	mutex_init(m) \
	MACRO_BEGIN \
	spin_lock_init(&(m)->lock); \
	cthread_queue_init(&(m)->queue); \
	spin_lock_init(&(m)->held); \
	mutex_set_holder(m, (struct cthread *)0); \
	(m)->name = 0; \
	MACRO_END

/**
 * @def mutex_set_name(m, x)
 * @brief Sets the name of a mutex (for debugging).
 * @param m Pointer to the mutex_t.
 * @param x The string name.
 */
#define	mutex_set_name(m, x)	((m)->name = (x))

/**
 * @def mutex_name(m)
 * @brief Gets the name of a mutex.
 * @param m Pointer to the mutex_t.
 * @return The name of the mutex, or "?" if not set.
 */
#define	mutex_name(m)		((m)->name != 0 ? (m)->name : "?")

/**
 * @def mutex_clear(m)
 * @brief Clears a mutex.
 * @param m Pointer to the mutex_t.
 * @note This is currently a no-op in some configurations (indicated by `???`).
 * Proper cleanup might involve waking up all waiting threads.
 */
#define	mutex_clear(m)		/* nop */ /* ??? Should wake up waiters? */

/**
 * @def mutex_free(m)
 * @brief Frees a mutex allocated by mutex_alloc().
 * @param m Pointer to the mutex_t to free.
 */
#define	mutex_free(m)		free((m))

/**
 * @brief Acquires a mutex, blocking if necessary (solid path).
 *
 * This function is called when a non-blocking attempt (`mutex_try_lock`) fails.
 * It handles the logic for adding the current thread to the mutex's wait queue
 * and blocking until the mutex is available.
 * @param _mutex Pointer to the mutex_t.
 */
extern void	mutex_lock_solid(mutex_t _mutex);	/* blocking */

/**
 * @brief Releases a mutex (solid path).
 *
 * This function is called when a thread releases a mutex and there might be
 * other threads waiting for it. It handles waking up the next thread in the queue.
 * @param _mutex Pointer to the mutex_t.
 */
extern void	mutex_unlock_solid(mutex_t _mutex);

/**
 * @def mutex_try_lock(m)
 * @brief Attempts to acquire a mutex without blocking.
 * @param m Pointer to the mutex_t.
 * @return TRUE if the mutex was acquired, FALSE otherwise.
 * If acquired, sets the holder of the mutex.
 */
#define mutex_try_lock(m) \
	(spin_try_lock(&(m)->held) ? (mutex_set_holder((m), cthread_self()), TRUE) : FALSE)

/**
 * @def mutex_lock(m)
 * @brief Acquires a mutex, blocking if necessary.
 *
 * This macro first attempts a non-blocking `mutex_try_lock`. If that fails,
 * it calls `mutex_lock_solid` to block until the mutex is acquired.
 * Sets the holder of the mutex upon successful acquisition.
 * @param m Pointer to the mutex_t.
 */
#define mutex_lock(m) \
	MACRO_BEGIN \
	if (!spin_try_lock(&(m)->held)) { \
		mutex_lock_solid(m); \
	} \
	mutex_set_holder(m, cthread_self()); \
	MACRO_END

/**
 * @def mutex_unlock(m)
 * @brief Releases a mutex.
 *
 * Clears the holder of the mutex. If there are threads waiting on the mutex's
 * queue, it calls `mutex_unlock_solid` to handle waking them up. Otherwise,
 * it simply releases the `held` spin lock.
 * @param m Pointer to the mutex_t.
 */
#define mutex_unlock(m) \
	MACRO_BEGIN \
	mutex_set_holder(m, (struct cthread *)0); \
	if (spin_unlock(&(m)->held), \
	    cthread_queue_head(&(m)->queue, vm_offset_t) != 0) { \
		mutex_unlock_solid(m); \
	} \
	MACRO_END
/** @} */

/**
 * @name Condition Variables
 * @{
 */
/**
 * @struct condition
 * @brief Condition variable for thread synchronization.
 *
 * Condition variables allow threads to wait for a specific condition
 * to become true. They are used in conjunction with mutexes.
 */
 * @struct condition
	spin_lock_t lock;		///< Spin lock protecting the condition's internal data.
	struct cthread_queue queue;	///< Queue of threads waiting on this condition.
	const char *name;		///< Optional name for debugging.
} *condition_t; ///< Pointer to a condition structure.

/**
 * @def CONDITION_INITIALIZER
 * @brief An initializer for a condition variable structure.
 */
#define	CONDITION_INITIALIZER		{ SPIN_LOCK_INITIALIZER, QUEUE_INITIALIZER, 0 }

/**
 * @def CONDITION_NAMED_INITIALIZER(Name)
 * @brief An initializer for a named condition variable structure.
 * @param Name The string name for the condition variable.
 */
#define	CONDITION_NAMED_INITIALIZER(Name) { SPIN_LOCK_INITIALIZER, QUEUE_INITIALIZER, Name }

/**
 * @def condition_alloc()
 * @brief Allocates and initializes a new condition variable.
 * @return Pointer to the allocated condition_t, or NULL on failure.
 * Uses calloc for allocation.
 */
#define	condition_alloc() \
	((condition_t) calloc(1, sizeof(struct condition)))

/**
 * @def condition_init(c)
 * @brief Initializes an existing condition variable.
 * @param c Pointer to the condition_t to initialize.
 */
#define	condition_init(c) \
	MACRO_BEGIN \
	spin_lock_init(&(c)->lock); \
	cthread_queue_init(&(c)->queue); \
	(c)->name = 0; \
	MACRO_END

/**
 * @def condition_set_name(c, x)
 * @brief Sets the name of a condition variable (for debugging).
 * @param c Pointer to the condition_t.
 * @param x The string name.
 */
#define	condition_set_name(c, x)	((c)->name = (x))

/**
 * @def condition_name(c)
 * @brief Gets the name of a condition variable.
 * @param c Pointer to the condition_t.
 * @return The name of the condition variable, or "?" if not set.
 */
#define	condition_name(c)		((c)->name != 0 ? (c)->name : "?")

/**
 * @def condition_clear(c)
 * @brief Clears a condition variable.
 * This typically involves broadcasting to all waiting threads and then
 * acquiring the internal lock (though the lock acquisition here might be
 * for ensuring state consistency before potential deallocation).
 * @param c Pointer to the condition_t.
 */
#define	condition_clear(c) \
	MACRO_BEGIN \
	condition_broadcast(c); \
	spin_lock(&(c)->lock); /* Potentially to ensure no more operations before free */ \
	MACRO_END

/**
 * @def condition_free(c)
 * @brief Frees a condition variable allocated by condition_alloc().
 * It first clears the condition variable.
 * @param c Pointer to the condition_t to free.
 */
#define	condition_free(c) \
	MACRO_BEGIN \
	condition_clear(c); \
	free((c)); \
	MACRO_END

/**
 * @def condition_signal(c)
 * @brief Signals (wakes up) one thread waiting on the condition variable.
 * If no threads are waiting, this is a no-op.
 * @param c Pointer to the condition_t.
 */
#define	condition_signal(c) \
	MACRO_BEGIN \
	if ((c)->queue.head) { \
		cond_signal(c); \
	} \
	MACRO_END

/**
 * @def condition_broadcast(c)
 * @brief Broadcasts (wakes up) all threads waiting on the condition variable.
 * If no threads are waiting, this is a no-op.
 * @param c Pointer to the condition_t.
 */
#define	condition_broadcast(c) \
	MACRO_BEGIN \
	if ((c)->queue.head) { \
		cond_broadcast(c); \
	} \
	MACRO_END

/**
 * @brief Signals one thread waiting on the specified condition variable.
 * This is the internal function called by the `condition_signal` macro.
 * @param _cond Pointer to the condition_t.
 */
extern void	cond_signal(condition_t _cond);

/**
 * @brief Wakes up all threads waiting on the specified condition variable.
 * This is the internal function called by the `condition_broadcast` macro.
 * @param _cond Pointer to the condition_t.
 */
extern void	cond_broadcast(condition_t _cond);

/**
 * @brief Waits on a condition variable.
 *
 * Atomically releases the associated mutex and blocks the current thread
 * until the condition is signaled or broadcast. The mutex is re-acquired
 * before this function returns.
 * @param _cond Pointer to the condition_t to wait on.
 * @param _mutex Pointer to the mutex_t associated with this condition.
 *               This mutex MUST be held by the calling thread.
 */
extern void	condition_wait(condition_t _cond, mutex_t _mutex);
/** @} */

/**
 * @name Threads
 * @{
 */

/**
 * @typedef cthread_fn_t
 * @brief Type definition for a C thread function.
 * Thread functions take a `void *` argument and return a `void *` result.
 */
typedef void *	(*cthread_fn_t)(void *arg);

/* XXX We really should be using the setjmp.h that goes with the libc
 * that we're planning on using, since that's where the setjmp()
 * functions are going to be comming from.
 */
#include <mach/setjmp.h> /* For jmp_buf, used in cthread structure for cthread_exit */

/**
 * @struct cthread
 * @brief Represents a C thread.
 *
 * This structure contains all the state associated with a single C thread,
 * including its execution context (via jmp_buf for exits), function,
 * argument, result, and synchronization primitives.
 */
typedef struct cthread {
	struct cthread *next;		///< Pointer to the next cthread in a list (e.g., run queue).
	struct mutex lock;		///< Mutex for protecting this cthread's state.
	struct condition done;		///< Condition variable signaled when the thread exits.
	int state;			///< Current state of the thread (e.g., running, blocked).
	jmp_buf catch_exit;		///< Jump buffer used by cthread_exit to unwind.
	cthread_fn_t func;		///< Pointer to the function this thread executes.
	void *arg;			///< Argument passed to the thread function.
	void *result;			///< Result returned by the thread function.
	const char *name;		///< Optional name for the thread (for debugging).
	void *data;			///< General-purpose thread-specific data pointer.
	void *ldata;			///< Another general-purpose thread-specific data pointer.
	void *private_data;		///< Reserved for C Threads internal use or POSIX-style thread-specific data.
	struct ur_cthread *ur;		///< Pointer to the underlying "user reference" cthread structure.
} *cthread_t; ///< Pointer to a cthread structure.

/**
 * @def NO_CTHREAD
 * @brief Represents a null or invalid cthread_t.
 */
#define	NO_CTHREAD	((cthread_t) 0)

/**
 * @brief Creates and starts a new C thread.
 * @param _func The function for the new thread to execute.
 * @param _arg The argument to be passed to `_func`.
 * @return A pointer to the newly created cthread_t, or NO_CTHREAD on failure.
 */
extern cthread_t	cthread_fork(cthread_fn_t _func, void *_arg);

/**
 * @brief Detaches a C thread.
 * A detached thread cannot be joined using `cthread_join`. Its resources
 * will be reclaimed automatically when it exits.
 * @param _thread The thread to detach.
 */
extern void		cthread_detach(cthread_t _thread);

/**
 * @brief Waits for a C thread to terminate and retrieves its result.
 * If the thread has already terminated, this function returns immediately.
 * Cannot be called on a detached thread.
 * @param _thread The thread to join.
 * @return The result returned by the thread function (via `cthread_exit`).
 * @deprecated The return type `any_t` is obsolete; use `void *`.
 */
extern any_t		cthread_join(cthread_t _thread);

/**
 * @brief Yields the processor to other runnable threads.
 * The calling thread remains runnable.
 */
extern void		cthread_yield(void);

/**
 * @brief Terminates the calling C thread.
 * @param _result The result value to be returned to any thread joining this thread.
 * This function does not return.
 */
extern void		cthread_exit(void *_result);

/**
 * @struct ur_cthread
 * @brief User reference cthread structure.
 * This structure is likely an internal or machine-dependent representation
 * of a thread, associated with a cthread_t. It must agree with struct cproc
 * in cthread_internals.h.
 */
typedef struct ur_cthread {
	struct ur_cthread *next;	///< Pointer to the next ur_cthread.
	cthread_t incarnation;		///< Pointer to the cthread_t this ur_cthread represents.
} *ur_cthread_t; ///< Pointer to a ur_cthread structure.

#ifndef	cthread_sp
/**
 * @brief Gets the current stack pointer for the calling C thread.
 * This function might be machine-dependent and implemented in assembler.
 * @return The current stack pointer as a vm_offset_t.
 */
extern vm_offset_t
cthread_sp(void);
#endif

extern vm_offset_t cthread_stack_mask; ///< Mask used for aligning or identifying stack regions.

#if	defined(STACK_GROWTH_UP)
/**
 * @def ur_cthread_ptr(sp)
 * @brief Gets a pointer to the ur_cthread structure from a stack pointer (for upward growing stacks).
 * @param sp The stack pointer.
 * @return Pointer to the ur_cthread_t.
 */
#define	ur_cthread_ptr(sp) \
	(* (ur_cthread_t *) ((sp) & cthread_stack_mask))
#else	/* not defined(STACK_GROWTH_UP) */
/**
 * @def ur_cthread_ptr(sp)
 * @brief Gets a pointer to the ur_cthread structure from a stack pointer (for downward growing stacks).
 * @param sp The stack pointer.
 * @return Pointer to the ur_cthread_t.
 */
#define	ur_cthread_ptr(sp) \
	(* (ur_cthread_t *) ( ((sp) | cthread_stack_mask) + 1 \
			      - sizeof(ur_cthread_t *)) )
#endif	/* defined(STACK_GROWTH_UP) */

/**
 * @def ur_cthread_self()
 * @brief Gets the ur_cthread_t for the currently running C thread.
 * @return Pointer to the ur_cthread_t of the caller.
 */
#define	ur_cthread_self()	(ur_cthread_ptr(cthread_sp()))

/**
 * @def cthread_assoc(id, t)
 * @brief Associates a ur_cthread (id) with a cthread (t).
 * Sets the `incarnation` field of the ur_cthread and the `ur` field of the cthread.
 * @param id Pointer to the ur_cthread_t.
 * @param t Pointer to the cthread_t.
 */
#define	cthread_assoc(id, t)	((((ur_cthread_t) (id))->incarnation = (t)), \
				((t) ? ((t)->ur = (ur_cthread_t)(id)) : (ur_cthread_t)0))

/**
 * @def cthread_self()
 * @brief Gets the cthread_t for the currently running C thread.
 * @return Pointer to the cthread_t of the caller.
 */
#define	cthread_self()		(ur_cthread_self()->incarnation)

/**
 * @brief Sets the name of a C thread (for debugging).
 * @param _thread The thread whose name is to be set.
 * @param _name The new name for the thread.
 */
extern void		cthread_set_name(cthread_t _thread, const char *_name);

/**
 * @brief Gets the name of a C thread.
 * @param _thread The thread whose name is to be retrieved.
 * @return The name of the thread, or a default string if not set.
 */
extern const char *	cthread_name(cthread_t _thread);

/**
 * @brief Gets the current number of active C threads.
 * @return The count of C threads.
 */
extern int		cthread_count(void);

/**
 * @brief Sets the limit on the total number of C threads that can be created.
 * @param _limit The new limit.
 */
extern void		cthread_set_limit(int _limit);

/**
 * @brief Gets the current limit on the total number of C threads.
 * @return The current C thread limit.
 */
extern int		cthread_limit(void);

/**
 * @brief Sets the limit on the number of kernel threads (Mach threads) used by C Threads.
 * @param _n The new kernel thread limit.
 */
extern void		cthread_set_kernel_limit(int _n);

/**
 * @brief Gets the current limit on the number of kernel threads used by C Threads.
 * @return The current kernel thread limit.
 */
extern int		cthread_kernel_limit(void);

/**
 * @brief Wires the calling C thread to its underlying kernel thread.
 * A wired thread will always run on the same kernel thread, preventing
 * migration between kernel threads. This can be used for interacting
 * with non-thread-safe libraries or for real-time purposes.
 */
extern void		cthread_wire(void);

/**
 * @brief Unwires the calling C thread from its underlying kernel thread.
 * Allows the C thread to be scheduled on different kernel threads.
 */
extern void		cthread_unwire(void);

/**
 * @brief Informs the C Threads scheduler about message activity on a port,
 * specifically when a thread might block sending a message.
 * This helps the scheduler manage the number of active kernel threads.
 * @param _port The Mach port involved in the message operation.
 * @param _min Minimum number of kernel threads desired for this activity.
 * @param _max Maximum number of kernel threads desired for this activity.
 */
extern void		cthread_msg_busy(mach_port_t _port, int _min, int _max);

/**
 * @brief Informs the C Threads scheduler about message activity on a port,
 * specifically when a thread is actively receiving or processing messages.
 * This helps the scheduler manage the number of active kernel threads.
 * @param _prt The Mach port involved in the message activity. (Note: parameter name is _prt)
 * @param _min Minimum number of kernel threads desired for this activity.
 * @param _max Maximum number of kernel threads desired for this activity.
 */
extern void		cthread_msg_active(mach_port_t _prt, int _min, int _max);

/**
 * @brief A C Threads wrapper for `mach_msg`.
 *
 * This function provides a thread-safe way to call `mach_msg` from within
 * a C Threads environment. It may interact with the C Threads scheduler
 * to manage blocking and kernel thread allocation.
 * @param _header Pointer to the `mach_msg_header_t`.
 * @param _option Message options.
 * @param _send_size Size of the send buffer.
 * @param _rcv_size Size of the receive buffer.
 * @param _rcv_name Port to receive on.
 * @param _timeout Message timeout value.
 * @param _notify Notification port.
 * @param _min Minimum number of kernel threads desired for this operation.
 * @param _max Maximum number of kernel threads desired for this operation.
 * @return The return value from `mach_msg`.
 */
extern mach_msg_return_t cthread_mach_msg(mach_msg_header_t *_header,
					  mach_msg_option_t _option,
					  mach_msg_size_t _send_size,
					  mach_msg_size_t _rcv_size,
					  mach_port_t _rcv_name,
					  mach_msg_timeout_t _timeout,
					  mach_port_t _notify,
					  int _min, int _max);

/**
 * @brief Prepares the C Threads environment for a `fork()` system call.
 * This should be called in the parent process before `fork()`.
 */
extern void		cthread_fork_prepare(void);

/**
 * @brief Actions to be taken in the parent process after a `fork()`.
 * Releases resources acquired by `cthread_fork_prepare`.
 */
extern void		cthread_fork_parent(void);

/**
 * @brief Actions to be taken in the child process after a `fork()`.
 * Re-initializes the C Threads environment for the child. Only the
 * calling thread (the one that executed `fork()`) will exist in the child.
 */
extern void		cthread_fork_child(void);
/** @} */ /* End of Threads group */

#if	defined(THREAD_CALLS)
/**
 * @name C Threads Replacements for Mach thread_* calls
 * These functions provide a C Threads interface that mimics some of the
 * functionality of the underlying Mach `thread_*` calls, but operate on
 * `cthread_t` objects.
 * @{
 */

/**
 * @brief Gets the execution state of a C thread.
 * (Analogous to `thread_get_state` for Mach threads).
 * @param _thread The target C thread.
 * @return A kern_return_t indicating success or failure. The actual state
 *         information would typically be passed via additional pointer arguments
 *         if this were a full replacement (not shown in this declaration).
 */
extern kern_return_t	cthread_get_state(cthread_t _thread);

/**
 * @brief Sets the execution state of a C thread.
 * (Analogous to `thread_set_state` for Mach threads).
 * @param _thread The target C thread.
 * @return A kern_return_t indicating success or failure.
 */
extern kern_return_t	cthread_set_state(cthread_t _thread);

/**
 * @brief Aborts a C thread.
 * (Analogous to `thread_abort` for Mach threads).
 * @param _thread The C thread to abort.
 * @return A kern_return_t indicating success or failure.
 */
extern kern_return_t	cthread_abort(cthread_t _thread);

/**
 * @brief Resumes a suspended C thread.
 * (Analogous to `thread_resume` for Mach threads).
 * @param _thread The C thread to resume.
 * @return A kern_return_t indicating success or failure.
 */
extern kern_return_t	cthread_resume(cthread_t _thread);

/**
 * @brief Suspends a C thread.
 * (Analogous to `thread_suspend` for Mach threads).
 * @param _thread The C thread to suspend.
 * @return A kern_return_t indicating success or failure.
 */
extern kern_return_t	cthread_suspend(cthread_t _thread);

/**
 * @brief Notifies a C thread, possibly for event handling.
 * The exact semantics of `thread_call_on` are specific to the Mach
 * implementation and how it's used for thread event delivery.
 * @param _thread The C thread to notify.
 * @return A kern_return_t indicating success or failure.
 */
extern kern_return_t	cthread_call_on(cthread_t _thread);
/** @} */
#endif	/* defined(THREAD_CALLS) */

#if	defined(CTHREAD_DATA_XX)
/**
 * @name Legacy Thread-Specific Data
 * @{
 */
/*
 * Set or get thread specific "global" variable
 *
 * The thread given must be the calling thread (ie. thread_self).
 * XXX This is for compatibility with the old cthread_data. XXX
 */

/**
 * @brief Sets a thread-specific data value (legacy version).
 * @param _thread The calling thread (must be `cthread_self()`).
 * @param _val The value to set.
 * @return An integer status code (typically 0 for success).
 * @deprecated This is a legacy interface. Use POSIX-style thread-specific data.
 */
extern int		cthread_set_data(cthread_t _thread, void *_val);

/**
 * @brief Gets a thread-specific data value (legacy version).
 * @param _thread The calling thread (must be `cthread_self()`).
 * @return The thread-specific data value.
 * @deprecated This is a legacy interface. Use POSIX-style thread-specific data.
 */
extern void *		cthread_data(cthread_t _thread);
/** @} */
#else	/* defined(CTHREAD_DATA_XX) */
/**
 * @name Thread-Specific Data Macros
 * These macros provide direct access to `data` and `ldata` fields
 * in the `cthread_t` structure.
 * @{
 */

/**
 * @def cthread_set_data(_thread, _val)
 * @brief Sets the `data` field of the specified C thread.
 * @param _thread Pointer to the cthread_t.
 * @param _val The value to set.
 */
#define cthread_set_data(_thread, _val) ((_thread)->data) = (void *)(_val)

/**
 * @def cthread_data(_thread)
 * @brief Gets the `data` field of the specified C thread.
 * @param _thread Pointer to the cthread_t.
 * @return The value of the `data` field.
 */
#define cthread_data(_thread) ((_thread)->data)

/**
 * @def cthread_set_ldata(_thread, _val)
 * @brief Sets the `ldata` field of the specified C thread.
 * @param _thread Pointer to the cthread_t.
 * @param _val The value to set.
 */
#define cthread_set_ldata(_thread, _val) ((_thread)->ldata) = (void *)(_val)

/**
 * @def cthread_ldata(_thread)
 * @brief Gets the `ldata` field of the specified C thread.
 * @param _thread Pointer to the cthread_t.
 * @return The value of the `ldata` field.
 */
#define cthread_ldata(_thread) ((_thread)->ldata)
/** @} */
#endif	/* defined(CTHREAD_DATA_XX) */


/**
 * @name POSIX-Style Thread-Specific Data
 * This interface provides a more standard way to handle thread-specific data,
 * similar to POSIX threads (pthreads). It allows multiple thread-specific
 * data items per thread, accessed via keys.
 * @{
 */

/**
 * @def CTHREAD_DATA_VALUE_NULL
 * @brief Represents a null value for thread-specific data.
 */
#define CTHREAD_DATA_VALUE_NULL		(void *)0

/**
 * @def CTHREAD_KEY_INVALID
 * @brief Represents an invalid key for thread-specific data.
 */
#define	CTHREAD_KEY_INVALID		(cthread_key_t)-1

/**
 * @typedef cthread_key_t
 * @brief Type for a key used to access thread-specific data.
 */
typedef int	cthread_key_t;

/**
 * @brief Creates a new key for thread-specific data.
 * The created key is visible to all threads in the task.
 * Different threads may use the same key, but the values bound to the key
 * are maintained on a per-thread basis and are initially NULL.
 * @param _key Pointer to a cthread_key_t where the new key will be stored.
 * @return 0 on success, or an error code on failure.
 */
extern int		cthread_keycreate(cthread_key_t *_key);

/**
 * @brief Gets the value currently bound to a key for the calling thread.
 * @param _key The key whose value is to be retrieved.
 * @param _value Pointer to a `void *` where the retrieved value will be stored.
 * @return 0 on success, or an error code if the key is invalid.
 */
extern int		cthread_getspecific(cthread_key_t _key, void **_value);

/**
 * @brief Binds a value to a given key for the calling thread.
 * @param _key The key to which the value will be bound.
 * @param _value The value to bind.
 * @return 0 on success, or an error code if the key is invalid.
 */
extern int		cthread_setspecific(cthread_key_t _key, void *_value);
/** @} */

#endif	/* not defined(_CTHREADS_) */
