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
 * cthread_internals.h
 *
 *
 * Private definitions for the C Threads implementation.
 *
 * The cproc structure is used for different implementations
 * of the basic schedulable units that execute cthreads.
 *
 */

#include <mach/port.h>
  struct cproc *next;    /* for lock, condition, and ready queues */
  cthread_t incarnation; /* for cthread_self() */
  struct cproc *list; /* for master cproc list */
  /* Not ifdeffed (WAIT_DEBUG) to keep size constant */
  volatile char *waiting_for; /* address of mutex/cond waiting for */

  mach_port_t reply_port; /* for mig_get_reply_port() */
  natural_t context;
  spin_lock_t lock;
  volatile int state; /* current state */
#define CPROC_RUNNING 0
#define CPROC_BLOCKED 2
#define CPROC_CONDWAIT 4

  mach_port_t wired; /* is cthread wired to kernel thread */
  vm_offset_t busy;  /* used with cthread_msg calls */
  mach_msg_header_t msg;

  vm_offset_t stack_base;
  vm_offset_t stack_size;
#if defined(WAIT_DEBUG)
  enum wait_enum {
    CTW_NONE,
    CTW_MUTEX,
    CTW_CONDITION,
    CTW_PORT_ENTRY
  } wait_type;
#endif /* defined(WAIT_DEBUG) */
#define NO_CPROC ((cproc_t)0)
#define cproc_self() ((cproc_t)ur_cthread_self())
#if defined(CHECK_STATUS)
#define MACH_CALL(expr, ret)                                                   \
  if (((ret) = (expr)) != KERN_SUCCESS) {                                      \
    quit(1, "error in %s at %d: %s\n", __FILE__, __LINE__,                     \
         mach_error_string(ret));                                              \
  } else
#else /* not defined(CHECK_STATUS) */
#endif /* defined(CHECK_STATUS) */
#if defined(ASSERT)
#else /* not defined(ASSERT) */
#define yield() (void)thread_switch(MACH_PORT_NULL, SWITCH_OPTION_DEPRESS, 10)
#if defined(DEBUG)
extern void print_malloc_free_list(void);
#endif /* defined(DEBUG) */

/**
 * @brief Prepare the allocator before a process forks.
 */
extern void malloc_fork_prepare(void);
/**
 * @brief Reenable the allocator in the parent process after fork.
 */
extern void malloc_fork_parent(void);
/**
 * @brief Reenable the allocator in the child process after fork.
 */
extern void malloc_fork_child(void);
/**
 * @brief Initialize the stack for the given cproc.
 *
 * @param _cproc The cproc for which to create the initial stack.
 * @return Base address of the allocated stack.
 */
extern vm_offset_t stack_init(cproc_t _cproc);
/**
 * @brief Allocate an additional stack for the given cproc.
 *
 * @param _cproc Target cproc.
 */
extern void alloc_stack(cproc_t _cproc);
/**
 * @brief Get the base address of the cproc stack with an offset.
 *
 * @param _cproc Target cproc.
 * @param _offset Offset from the base address.
 * @return Computed stack address.
 */
extern vm_offset_t cproc_stack_base(cproc_t _cproc, int _offset);
/**
 * @brief Reset stack state in the child after fork.
 */
extern void stack_fork_child(void);
/**
 * @brief Initialize the cproc layer.
 *
 * @return Base address of the initial stack.
 */
extern vm_offset_t cproc_init(void);
/**
 * @brief Mark a cproc as waiting.
 *
 * @param _waiter The waiting cproc.
 */
extern void cproc_waiting(cproc_t _waiter);
/**
 * @brief Create a new cproc.
 *
 * @return Newly created cproc.
 */
extern cproc_t cproc_create(void);
/**
 * @brief Prepare all cprocs for a fork operation.
 */
extern void cproc_fork_prepare(void);
/**
 * @brief Resume cproc operation in the parent after fork.
 */
extern void cproc_fork_parent(void);
/**
 * @brief Resume cproc operation in the child after fork.
 */
extern void cproc_fork_child(void);
/**
 * @brief Entry point for new cthreads.
 *
 * @param _self The executing cproc.
 */
extern void cthread_body(cproc_t _self);

/**
 * @brief Switch execution from one cproc to another.
 *
 * @param _cur  Currently running context pointer.
 * @param _new  New context to switch to.
 * @param _lock Spin lock held during the switch.
 */
extern void cproc_switch(natural_t *_cur, const natural_t *_new,
                         spin_lock_t *_lock);
/**
 * @brief Put a child cproc into the wait state.
 *
 * @param _parent Parent context pointer.
 * @param _child  Child cproc.
 * @param _stackp Stack pointer to use.
 * @param _lock   Spin lock held during operation.
 */
extern void cproc_start_wait(natural_t *_parent, cproc_t _child,
                             vm_offset_t _stackp, spin_lock_t *_lock);
/**
 * @brief Prepare a child cproc for execution.
 *
 * @param _child          The child cproc.
 * @param _child_context  Context storage for the child.
 * @param _stackp         Initial stack pointer.
 */
extern void cproc_prepare(cproc_t _child, natural_t *_child_context,
                          vm_offset_t _stackp);
/**
 * @brief Finalize setup of a newly created cproc.
 *
 * @param _child       The cproc to set up.
 * @param _mach_thread Mach thread bound to the cproc.
 * @param _routine     Entry routine for execution.
 */
extern void cproc_setup(cproc_t _child, thread_t _mach_thread,
                        void (*_routine)(cproc_t));
#if defined(DEBUG)
#if defined(ASSERT)
#else /* not defined(ASSERT) */
#define ASSERT(p)                                                              \
  MACRO_BEGIN                                                                  \
  if (!(p)) {                                                                  \
    fprintf(stderr, "File %s, line %d: assertion " #p " failed.\n", __FILE__,  \
            __LINE__);                                                         \
    abort();                                                                   \
  }                                                                            \
  MACRO_END
#endif /* defined(ASSERT) */

#define SHOULDNT_HAPPEN 0

#else /* not defined(DEBUG) */
#if defined(ASSERT)
#else /* not defined(ASSERT) */
#define ASSERT(p)
#endif /* defined(ASSERT) */
#endif /* defined(DEBUG) */
 */

extern vm_offset_t	stack_init(cproc_t _cproc);

extern void		alloc_stack(cproc_t _cproc);

extern vm_offset_t	cproc_stack_base(cproc_t _cproc, int _offset);

extern void		stack_fork_child(void);

/*
 * Functions implemented in cprocs.c.
 */

extern vm_offset_t	cproc_init(void);

extern void		cproc_waiting(cproc_t _waiter);

extern cproc_t		cproc_create(void);

extern void		cproc_fork_prepare(void);

extern void		cproc_fork_parent(void);

extern void		cproc_fork_child(void);

/*
 * Function implemented in cthreads.c.
 */

extern void		cthread_body(cproc_t _self);

/*
 * Functions from machine dependent files.
 */

extern void		cproc_switch(natural_t *_cur, const natural_t *_new,
				     spin_lock_t *_lock);

extern void		cproc_start_wait(natural_t *_parent, cproc_t _child,
					 vm_offset_t _stackp,
					 spin_lock_t *_lock);

extern void		cproc_prepare(cproc_t _child, natural_t *_child_context,
				      vm_offset_t _stackp);

extern void		cproc_setup(cproc_t _child, thread_t _mach_thread,
				    void (*_routine)(cproc_t));

/*
 * Debugging support.
 */
#if	defined(DEBUG)

extern int stderr;

#if	defined(ASSERT)
#else	/* not defined(ASSERT) */
/*
 * Assertion macro, similar to <assert.h>
 */
#define	ASSERT(p) \
	MACRO_BEGIN \
	if (!(p)) { \
		fprintf(stderr, \
			"File %s, line %d: assertion "#p" failed.\n", \
			__FILE__, __LINE__); \
		abort(); \
	} \
	MACRO_END

#endif	/* defined(ASSERT) */

#define	SHOULDNT_HAPPEN	0

extern int cthread_debug;

#else	/* not defined(DEBUG) */

#if	defined(ASSERT)
#else	/* not defined(ASSERT) */
#define	ASSERT(p)
#endif	/* defined(ASSERT) */

#endif	/* defined(DEBUG) */

