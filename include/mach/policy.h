/* 
 * Mach Operating System
 * Copyright (c) 1991,1990,1989,1988 Carnegie Mellon University
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

/**
 * @file mach/policy.h
 * @brief Definitions for thread scheduling policies.
 *
 * This file defines constants representing different scheduling policies
 * that can be applied to threads in the Mach kernel.
 */
#ifndef	_MACH_POLICY_H_
#define _MACH_POLICY_H_

/*
 *	mach/policy.h
 *
 *	Definitions for scheduing policy.
 */

/**
 * @name Scheduling Policy Definitions
 * Policies should ideally be powers of 2 if they are intended to be used as bitmasks,
 * though current definitions are simple integers.
 * @{
 */

/**
 * @def POLICY_TIMESHARE
 * @brief Time-sharing scheduling policy.
 * Threads under this policy share the processor based on a time-slicing
 * algorithm, typically with dynamically adjusted priorities.
 */
#define	POLICY_TIMESHARE	1

/**
 * @def POLICY_FIXEDPRI
 * @brief Fixed-priority scheduling policy.
 * Threads under this policy are scheduled strictly based on their fixed
 * priority levels. Higher priority threads run before lower priority ones.
 * This is often used for real-time applications.
 */
#define POLICY_FIXEDPRI		2

/**
 * @def POLICY_LAST
 * @brief Marks the last defined standard policy identifier.
 * Used for validating policy values.
 */
#define POLICY_LAST		2
/** @} */

/**
 * @def invalid_policy(policy)
 * @brief Macro to check if a given policy value is invalid.
 * A policy is considered invalid if it is less than or equal to 0,
 * or greater than `POLICY_LAST`.
 * @param policy The policy value to check.
 * @return True if the policy is invalid, false otherwise.
 */
#define invalid_policy(policy)	(((policy) <= 0) || ((policy) > POLICY_LAST))

#endif /* _MACH_POLICY_H_ */
