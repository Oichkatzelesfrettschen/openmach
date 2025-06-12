/*
 * Mach Operating System
 * Copyright (c) 1991,1990,1989 Carnegie Mellon University.
 * Copyright (c) 1993,1994 The University of Utah and
 * the Computer Systems Laboratory (CSL).
 * All rights reserved.
 *
 * Permission to use, copy, modify and distribute this software and its
 * documentation is hereby granted, provided that both the copyright
 * notice and this permission notice appear in all copies of the
 * software, derivative works or modified versions, and any portions
 * thereof, and that both notices appear in supporting documentation.
 *
 * CARNEGIE MELLON, THE UNIVERSITY OF UTAH AND CSL ALLOW FREE USE OF
 * THIS SOFTWARE IN ITS "AS IS" CONDITION, AND DISCLAIM ANY LIABILITY
 * OF ANY KIND FOR ANY DAMAGES WHATSOEVER RESULTING FROM THE USE OF
 * THIS SOFTWARE.
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
 *
/*
 *	File:	ipc/ipc_entry.c
 *	Author:	Rich Draves
 *	Date:	1989
 *
/**
 * @file ipc/ipc_entry.c
 * @brief Primitive functions to manipulate IPC port name translation entries.
 * @author Rich Draves
 * @date 1989
 *
 * This file implements core functionalities for managing entries within a
 * task's IPC space. An IPC space maps Mach port names (integers used by tasks)
 * to kernel IPC objects (like ports or port sets). These entries represent
 * port rights held by a task.
 *
 * The implementation uses a combination of a direct-mapped table (`is_table`) for
 * small port name indices and a splay tree (`is_tree`) for larger indices or
 * to handle collisions in the direct-mapped table.
 */

#include <mach/kern_return.h>
#include <mach/port.h>
#include <kern/assert.h>
#include <kern/sched_prim.h> /* For assert_wait, thread_block, thread_wakeup */
#include <kern/zalloc.h>     /* For zone_t, ite_alloc, ite_free (likely zone operations for tree entries) */
#include <ipc/port.h>        /* For IO_NULL (ipc_object_t) */
#include <ipc/ipc_types.h>   /* For ipc_entry_t, ipc_space_t, ipc_tree_entry_t etc. */
#include <ipc/ipc_entry.h>   /* Function declarations for this file */
#include <ipc/ipc_space.h>   /* For ipc_space structure details (is_active, is_table, etc.) */
#include <ipc/ipc_splay.h>   /* For splay tree operations (ipc_splay_tree_*) */
#include <ipc/ipc_hash.h>    /* For ipc_hash_global_delete, ipc_hash_local_insert */
#include <ipc/ipc_table.h>   /* For ipc_table_size_t, it_entries_realloc, etc. */
#include <ipc/ipc_object.h>  /* For ipc_object_t definition (IO_NULL) */

/** @brief Zone for allocating IPC tree entries (`ipc_tree_entry_t`). */
zone_t ipc_tree_entry_zone;

/**
 * @brief Checks if a given port name would collide (by index) with an existing name in the space's splay tree.
 *
 * A collision occurs if the splay tree already contains an entry whose port name
 * has the same index as the provided `name`. This function is used to determine
 * if a new entry in the table part would cause an index collision with an entry
 * already in the tree part of the IPC space.
 *
 * @param space The IPC space to check.
 * @param name The Mach port name to check for potential index collision.
 * @return TRUE if a name with the same index as `name` exists in the splay tree, FALSE otherwise.
 * @pre The space must be locked (read or write) and active.
 */
boolean_t
ipc_entry_tree_collision(
	ipc_space_t	space,
	mach_port_t	name)
{
	mach_port_index_t index;
	mach_port_t lower, upper;

	assert(space->is_active);

	/*
	 *	Check if we collide with the next smaller name
	 *	or the next larger name in the splay tree based on name value.
	 *  Then check if their indices match the target name's index.
	 */
	ipc_splay_tree_bounds(&space->is_tree, name, &lower, &upper);

	index = MACH_PORT_INDEX(name);
	return (((lower != (mach_port_t)(~0)) && (MACH_PORT_INDEX(lower) == index)) || /* Ensure lower is not max value before checking */
		((upper != MACH_PORT_NULL) && (MACH_PORT_INDEX(upper) == index)));   /* Ensure upper is not null before checking */
}

/**
 * @brief Searches for an IPC entry within a given space by its Mach port name.
 *
 * It first attempts to find the entry in the direct-mapped table if the name's
 * index falls within the table's bounds. If the generation numbers don't match
 * and a collision is indicated, or if the index is out of table bounds, it
 * then searches the splay tree.
 *
 * @param space The IPC space to search within.
 * @param name The Mach port name (including generation number) to look up.
 * @return A pointer to the found `ipc_entry_t` if an active entry with the
 *         matching name and generation number exists. Returns `IE_NULL` if no
 *         such entry is found or if the found entry has no type (is free).
 * @pre The space must be locked (read or write) and active.
 */
ipc_entry_t
ipc_entry_lookup(
	ipc_space_t	space,
	mach_port_t	name)
{
	mach_port_index_t index;
	ipc_entry_t entry;

	assert(space->is_active);

	index = MACH_PORT_INDEX(name);
	if (index < space->is_table_size) { /* Is the index within the flat table part? */
		entry = &space->is_table[index];
		if (IE_BITS_GEN(entry->ie_bits) != MACH_PORT_GEN(name)) { /* Generation number mismatch? */
			if (entry->ie_bits & IE_BITS_COLLISION) { /* Is there a collision at this table slot? */
				assert(space->is_tree_total > 0); /* Tree must exist if collision bit is set */
				goto tree_lookup; /* Fall through to splay tree lookup */
			} else {
				entry = IE_NULL; /* No collision, gen mismatch means name not found here */
			}
		} else if (IE_BITS_TYPE(entry->ie_bits) == MACH_PORT_TYPE_NONE) { /* Correct generation, but entry is free? */
			entry = IE_NULL;
		}
		/* If generation matches and type is not NONE, entry is valid */
	} else if (space->is_tree_total == 0) { /* Index outside table, but no tree entries? */
		entry = IE_NULL;
	} else {
	    tree_lookup: /* Label for goto from table lookup on collision */
		/* Search in the splay tree part */
		entry = (ipc_entry_t)
				ipc_splay_tree_lookup(&space->is_tree, name);
	}

	assert((entry == IE_NULL) || IE_BITS_TYPE(entry->ie_bits)); /* A valid entry must have a type */
	return entry;
}

/**
 * @brief Attempts to find and allocate a free entry from the direct-mapped table part of an IPC space.
 *
 * This function looks for a free slot in `space->is_table` using the free list
 * maintained within the table itself (`table->ie_next` points to the first free index).
 * If a free entry is found, it's removed from the free list, its generation number
 * is incremented, and it's prepared for use.
 *
 * @param space The IPC space from which to allocate.
 * @param namep Output: Pointer to store the new Mach port name (index + generation) if successful.
 * @param entryp Output: Pointer to store the address of the allocated `ipc_entry_t` if successful.
 * @return `KERN_SUCCESS` if a free entry was found and allocated.
 * @return `KERN_NO_SPACE` if the table's free list is empty.
 * @pre The space is write-locked and active. This function does not allocate memory.
 */
kern_return_t
ipc_entry_get(
	ipc_space_t	space,
	mach_port_t	*namep,
	ipc_entry_t	*entryp)
{
	ipc_entry_t table;
	mach_port_index_t first_free;
	mach_port_t new_name;
	ipc_entry_t free_entry;

	assert(space->is_active);

	table = space->is_table;
	first_free = table->ie_next; /* Index 0 of table stores head of free list */

	if (first_free == 0) /* Free list is empty */
		return KERN_NO_SPACE;

	free_entry = &table[first_free];
	table->ie_next = free_entry->ie_next; /* Remove from free list */

	/*
	 *	Initialize the new entry.  We need only
	 *	increment the generation number and clear ie_request.
	 */
    {
		mach_port_gen_t gen;

		assert((free_entry->ie_bits &~ IE_BITS_GEN_MASK) == 0); /* Ensure only gen bits are set if any */
		gen = IE_BITS_GEN(free_entry->ie_bits) + IE_BITS_GEN_ONE; /* Increment generation */
		if (gen == 0) /* Handle generation wrap-around */
		    gen = IE_BITS_GEN_ONE; /* Should not reuse gen 0 if MACH_PORT_NULL has gen 0 */
		free_entry->ie_bits = gen; /* Set new generation, type is implicitly MACH_PORT_TYPE_NONE */
		free_entry->ie_request = 0;
		new_name = MACH_PORT_MAKE(first_free, gen);
    }

	/*
	 *	The new name can't be MACH_PORT_NULL because index (first_free)
	 *	is non-zero (index 0 is used for free list head).
	 *  It can't be MACH_PORT_DEAD because the generation number is fresh.
	 *	(Original comment about table size and MACH_PORT_DEAD might be less relevant with robust gen numbers).
	 */
	assert(MACH_PORT_VALID(new_name));
	assert(free_entry->ie_object == IO_NULL); /* A free entry should not point to an object */

	*namep = new_name;
	*entryp = free_entry;
	return KERN_SUCCESS;
}

/**
 * @brief Allocates a new IPC entry in the given space.
 *
 * This function first tries to get a free entry using `ipc_entry_get`.
 * If that fails (meaning the current table's free list is exhausted),
 * it attempts to grow the table using `ipc_entry_grow_table` and then retries.
 *
 * @param space The IPC space in which to allocate the entry.
 * @param namep Output: Pointer to store the Mach port name of the allocated entry.
 * @param entryp Output: Pointer to store the address of the allocated `ipc_entry_t`.
 * @return `KERN_SUCCESS` if an entry was successfully allocated.
 * @return `KERN_INVALID_TASK` if the space is inactive (dead).
 * @return `KERN_NO_SPACE` if the table cannot be grown further.
 * @return `KERN_RESOURCE_SHORTAGE` if memory allocation for table growth fails.
 * @note The space is not locked initially. It will be write-locked upon successful return.
 *       If an error occurs (except for `KERN_INVALID_TASK` where it's unlocked before return),
 *       the lock state might depend on the error path (e.g., `ipc_entry_grow_table` unlocks on failure).
 */
kern_return_t
ipc_entry_alloc(
	ipc_space_t	space,
	mach_port_t	*namep,
	ipc_entry_t	*entryp)
{
	kern_return_t kr;

	is_write_lock(space);

	for (;;) { /* Loop to retry after table growth */
		if (!space->is_active) {
			is_write_unlock(space);
			return KERN_INVALID_TASK;
		}

		kr = ipc_entry_get(space, namep, entryp); /* Try to get from current table */
		if (kr == KERN_SUCCESS)
			return kr; /* Success, space remains locked */

		/* KERN_NO_SPACE from ipc_entry_get, try to grow the table */
		kr = ipc_entry_grow_table(space); /* Unlocks/relocks space or returns it unlocked on error */
		if (kr != KERN_SUCCESS)
			return kr; /* Return error, space is unlocked by ipc_entry_grow_table on error */
		/* ipc_entry_grow_table returns with space write-locked on success. Loop to retry ipc_entry_get. */
	}
}

/**
 * @brief Allocates or finds an IPC entry for a specific Mach port name.
 *
 * This function attempts to reserve a specific name in the IPC space.
 * - If the name's index falls within the table and is free, it's allocated.
 * - If the name's index is in the table but used (possibly by a different generation),
 *   or if the index is outside the table, it searches/inserts into the splay tree.
 * - If the name already exists with the correct generation number (either in table or tree),
 *   the existing entry is returned.
 * - The function may attempt to grow the table if it's more space-efficient than using the tree.
 * - May allocate memory for tree entries or for growing the table.
 *
 * @param space The IPC space.
 * @param name The specific Mach port name (index + generation) to allocate/find.
 * @param entryp Output: Pointer to store the address of the allocated or found `ipc_entry_t`.
 * @return `KERN_SUCCESS` if the entry was found or newly allocated.
 * @return `KERN_INVALID_TASK` if the space is inactive.
 * @return `KERN_RESOURCE_SHORTAGE` if memory allocation fails.
 * @note The space is not locked initially. It will be write-locked upon successful return.
 *       If an error occurs, the lock state depends on the error path.
 *       A `tree_entry` is pre-allocated outside the lock to avoid holding lock during allocation.
 */
kern_return_t
ipc_entry_alloc_name(
	ipc_space_t	space,
	mach_port_t	name,
	ipc_entry_t	*entryp)
{
	mach_port_index_t index = MACH_PORT_INDEX(name);
	mach_port_gen_t gen = MACH_PORT_GEN(name);
	ipc_tree_entry_t tree_entry = ITE_NULL; /* Pre-allocate tree entry if needed */

	assert(MACH_PORT_VALID(name));

	is_write_lock(space);

	for (;;) { /* Loop to handle table growth and retry logic */
		ipc_entry_t entry;
		ipc_tree_entry_t tentry; /* For tree lookups */
		ipc_table_size_t its;    /* Info about next table size */

		if (!space->is_active) {
			is_write_unlock(space);
			if (tree_entry != ITE_NULL) ite_free(tree_entry); /* Free pre-allocated entry */
			return KERN_INVALID_TASK;
		}

		/* Case 1: Name's index is within the current flat table */
		if ((index > 0) && (index < space->is_table_size)) { /* Index 0 is reserved */
			ipc_entry_t table = space->is_table;
			entry = &table[index];

			if (IE_BITS_TYPE(entry->ie_bits) != MACH_PORT_TYPE_NONE) { /* Entry is in use */
				if (IE_BITS_GEN(entry->ie_bits) == gen) { /* Correct name (index+gen)? */
					*entryp = entry;
					if (tree_entry != ITE_NULL) ite_free(tree_entry);
					return KERN_SUCCESS; /* Found existing entry */
				}
				/* Else, index is used by a different generation. This is a collision for this name.
				   The requested name must go into the tree, or if already there, be found there.
				   The table entry itself will be marked with IE_BITS_COLLISION if not already.
				   This path will eventually lead to the tree lookup below. */
			} else { /* Entry at this index is free */
				/* Remove from free list and allocate */
				mach_port_index_t free_idx, next_idx;
				for (free_idx = 0; (next_idx = table[free_idx].ie_next) != index; free_idx = next_idx) {
					assert(next_idx != 0); /* Should find it if it's free */
				}
				table[free_idx].ie_next = table[next_idx].ie_next; /* Unlink */

				entry->ie_bits = gen | IE_BITS_TYPE(MACH_PORT_TYPE_NONE); /* Set generation, type is still NONE until right is inserted */
				assert(entry->ie_object == IO_NULL);
				entry->ie_request = 0;
				*entryp = entry;
				if (tree_entry != ITE_NULL) ite_free(tree_entry);
				return KERN_SUCCESS; /* Allocated from table free list */
			}
		}

		/* Case 2: Name's index is outside table, or table slot is occupied by different generation.
		   Must use splay tree. First, check if it's already in the tree. */
		if ((space->is_tree_total > 0) &&
		    ((tentry = ipc_splay_tree_lookup(&space->is_tree, name)) != ITE_NULL)) {
			assert(tentry->ite_space == space);
			assert(IE_BITS_TYPE(tentry->ite_bits) != MACH_PORT_TYPE_NONE); /* Tree entries are always in use */
			*entryp = &tentry->ite_entry;
			if (tree_entry != ITE_NULL) ite_free(tree_entry);
			return KERN_SUCCESS; /* Found in tree */
		}

		/* Entry not found yet. Consider growing table vs. allocating tree entry. */
		its = space->is_table_next; /* Info about the next possible table size */

		/* Heuristic: if name fits in next table size AND table growth is cheaper than tree node... */
		if ((space->is_table_size <= index) && /* Name is currently outside table */
		    (index < its->its_size) &&        /* But would fit in the next table size increment */
		    (((its->its_size - space->is_table_size) * sizeof(struct ipc_entry)) < /* Cost of new table slots */
		     ((space->is_tree_small + 1) * sizeof(struct ipc_tree_entry)))) { /* Cost of tree node + impact on small_tree count */
			kern_return_t kr;
			/* Grow table, then restart the whole process. */
			kr = ipc_entry_grow_table(space); /* Unlocks/relocks space */
			assert(kr != KERN_NO_SPACE); /* Should be able to grow if heuristic was met */
			if (kr != KERN_SUCCESS) {
				if (tree_entry != ITE_NULL) ite_free(tree_entry);
				return kr; /* Space is unlocked by ipc_entry_grow_table on error */
			}
			continue; /* Restart lookup/alloc from the beginning with the larger table */
		}

		/* Decision is to use/allocate a tree entry. */
		if (tree_entry == ITE_NULL) { /* Do we need to allocate one? */
			is_write_unlock(space); /* Unlock before memory allocation */
			tree_entry = ite_alloc();
			if (tree_entry == ITE_NULL)
				return KERN_RESOURCE_SHORTAGE;
			is_write_lock(space);
			continue; /* Restart to ensure space is still active and handle races */
		}

		/* We have a pre-allocated tree_entry, and decided to use the tree. Insert it. */
		space->is_tree_total++;

		if (index < space->is_table_size) { /* Name's index is in table, but gen mismatch or slot taken by other gen */
			space->is_table[index].ie_bits |= IE_BITS_COLLISION; /* Mark table slot as having a tree collision */
		} else if ((index < its->its_size) && /* Name's index is outside current table but would fit next increment */
			   !ipc_entry_tree_collision(space, name)) { /* And no *other* tree entry shares this index yet */
			space->is_tree_small++; /* This new tree entry is in the "small" index range */
		}

		ipc_splay_tree_insert(&space->is_tree, name, tree_entry);

		tree_entry->ite_bits = gen | IE_BITS_TYPE(MACH_PORT_TYPE_NONE); /* Set generation, type is NONE initially */
		tree_entry->ite_object = IO_NULL;
		tree_entry->ite_request = 0;
		tree_entry->ite_space = space; /* Backlink to space */
		*entryp = &tree_entry->ite_entry;
		/* tree_entry is now used, don't free it */
		return KERN_SUCCESS;
	}
}

/**
 * @brief Deallocates an IPC entry from an IPC space.
 *
 * The entry must represent no port rights (ie_object should be IO_NULL)
 * and have no pending requests (ie_request should be 0).
 *
 * If the entry is in the table part:
 *  - If it was part of a collision chain (IE_BITS_COLLISION was set),
 *    a suitable entry from the splay tree (with the same index) is moved
 *    into this table slot to replace it. The collision bit may be cleared
 *    if no more tree entries share this index.
 *  - Otherwise (no collision), the entry is simply added to the table's free list.
 * If the entry is in the splay tree part:
 *  - It is removed from the tree.
 *  - If its index falls within the table range and this removal resolves a
 *    collision for that table slot, the IE_BITS_COLLISION is cleared.
 *  - The `is_tree_small` count is updated if necessary.
 *
 * @param space The IPC space from which to deallocate.
 * @param name The Mach port name of the entry to deallocate.
 * @param entry Pointer to the `ipc_entry_t` to deallocate. This can be
 *              an entry in `space->is_table` or an `ipc_tree_entry_t`.
 * @pre The space must be write-locked and active.
 * @pre `entry->ie_object == IO_NULL` and `entry->ie_request == 0`.
 */
void
ipc_entry_dealloc(
	ipc_space_t	space,
	mach_port_t	name,
	ipc_entry_t	entry)
{
	ipc_entry_t table;
	ipc_entry_num_t size; /* current table size */
	mach_port_index_t index;

	assert(space->is_active);
	assert(entry->ie_object == IO_NULL);
	assert(entry->ie_request == 0);

	index = MACH_PORT_INDEX(name);
	table = space->is_table;
	size = space->is_table_size;

	if ((index < size) && (entry == &table[index])) { /* Entry is in the table part */
		assert(IE_BITS_GEN(entry->ie_bits) == MACH_PORT_GEN(name));

		if (entry->ie_bits & IE_BITS_COLLISION) { /* Was this table slot part of a collision? */
			struct ipc_splay_tree small_unused, collisions_at_index;
			ipc_tree_entry_t tentry_to_move;
			mach_port_t tname_to_move;
			boolean_t picked_one;
			ipc_entry_bits_t bits_to_move;
			ipc_object_t obj_to_move;

			/* A tree entry collided with this table slot (same index, different gen).
			 * Now that this table entry is free, we can try to move one of the
			 * colliding tree entries into this table slot.
			 */
			/* Isolate tree entries that map to this index */
			ipc_splay_tree_split(&space->is_tree, MACH_PORT_MAKE(index + 1, 0), &collisions_at_index);
			ipc_splay_tree_split(&collisions_at_index, MACH_PORT_MAKE(index, 0), &small_unused);

			picked_one = ipc_splay_tree_pick(&collisions_at_index, &tname_to_move, &tentry_to_move);
			assert(picked_one); /* Must find at least one if collision bit was set */
			assert(MACH_PORT_INDEX(tname_to_move) == index);

			/* Copy data from chosen tree entry to the table entry */
			bits_to_move = tentry_to_move->ite_bits;
			entry->ie_bits = bits_to_move | MACH_PORT_GEN(tname_to_move); /* Set correct gen */
			entry->ie_object = obj_to_move = tentry_to_move->ite_object;
			entry->ie_request = tentry_to_move->ite_request;
			assert(tentry_to_move->ite_space == space);

			/* If it was a send right, update hash tables */
			if (IE_BITS_TYPE(bits_to_move) == MACH_PORT_TYPE_SEND) {
				ipc_hash_global_delete(space, obj_to_move, tname_to_move, (ipc_entry_t)tentry_to_move);
				ipc_hash_local_insert(space, obj_to_move, index, entry);
			}

			ipc_splay_tree_delete(&collisions_at_index, tname_to_move, tentry_to_move);
			ite_free(tentry_to_move); /* Free the now-empty tree node */

			assert(space->is_tree_total > 0);
			space->is_tree_total--;

			/* Check if there are still other tree entries colliding at this index */
			picked_one = ipc_splay_tree_pick(&collisions_at_index, &tname_to_move, &tentry_to_move);
			if (picked_one) {
				/* entry->ie_bits |= IE_BITS_COLLISION; -- already set, remains set */
				ipc_splay_tree_join(&space->is_tree, &collisions_at_index);
			} else {
				entry->ie_bits &= ~IE_BITS_COLLISION; /* No more collisions for this table slot */
			}
			ipc_splay_tree_join(&space->is_tree, &small_unused); /* Join back unused parts */
		} else { /* Not a collision entry, just a normal table entry being freed */
			entry->ie_bits &= IE_BITS_GEN_MASK; /* Keep generation, clear type & other bits */
			entry->ie_next = table->ie_next;   /* Add to head of free list */
			table->ie_next = index;
		}
	} else { /* Entry is in the splay tree part */
		ipc_tree_entry_t tentry = (ipc_tree_entry_t) entry;

		assert(tentry->ite_space == space); /* Should belong to this space */

		ipc_splay_tree_delete(&space->is_tree, name, tentry);
		ite_free(tentry); /* Free the tree node itself */

		assert(space->is_tree_total > 0);
		space->is_tree_total--;

		if (index < size) { /* If the freed tree entry's index was within current table range */
			ipc_entry_t ientry_at_table = &table[index];
			assert(ientry_at_table->ie_bits & IE_BITS_COLLISION); /* Table entry must have shown collision */

			/* Check if this was the *last* tree entry colliding with table[index] */
			if (!ipc_entry_tree_collision(space, name)) /* name's index is 'index' */
				ientry_at_table->ie_bits &= ~IE_BITS_COLLISION;
		} else if ((index < space->is_table_next->its_size) && /* Index was in "small tree" range */
			   !ipc_entry_tree_collision(space, name)) {
			/* If no other tree entry now shares this index, it's no longer contributing to is_tree_small
			   if it was the *only* one at that index. This logic seems to decrement if any
			   tree node with this index is removed and no other tree node *at that same index* exists.
			   The original code's is_tree_small update might be more nuanced with its check.
			*/
			assert(space->is_tree_small > 0);
			space->is_tree_small--; /* Decrement count of tree entries in the "small" index range */
		}
	}
}

/**
 * @brief Grows the direct-mapped entry table (`is_table`) within an IPC space.
 *
 * This function is called when the table is full or when allocating a specific
 * name suggests that growing the table would be more space-efficient than
 * using the splay tree. It handles reallocating/allocating the table,
 * copying old entries, initializing new entries, and migrating entries from
 * the splay tree into the newly expanded table portion if they fit and don't collide.
 *
 * @param space The IPC space whose table is to be grown.
 * @return `KERN_SUCCESS` if the table was grown, or if another thread grew it,
 *         or if the space died during the operation.
 * @return `KERN_NO_SPACE` if the table is already at its maximum defined size.
 * @return `KERN_RESOURCE_SHORTAGE` if memory allocation for the new table fails.
 * @pre The space must be write-locked and active upon entry.
 * @post If successful, the space is returned write-locked.
 *       If `KERN_RESOURCE_SHORTAGE` or `KERN_NO_SPACE` is returned, the space is write-unlocked.
 *       If the space dies, it's write-locked upon return (but inactive).
 *       The function handles potential races with other threads also trying to grow the table
 *       by using `space->is_growing` flag and `assert_wait`/`thread_block`/`thread_wakeup`.
 */
kern_return_t
ipc_entry_grow_table(
	ipc_space_t	space)
{
	ipc_entry_num_t osize, size, nsize;

	do {
		ipc_entry_t otable, table;
		ipc_table_size_t oits, its, nits;
		mach_port_index_t i, free_index_head;

		assert(space->is_active);

		if (space->is_growing) {
			/* Another thread is already growing the table. Wait for it. */
			assert_wait((event_t) space, FALSE);
			is_write_unlock(space);
			thread_block((void (*)()) 0); /* Wait for wakeup */
			is_write_lock(space);
			return KERN_SUCCESS; /* Assume other thread succeeded or handled error */
		}

		otable = space->is_table;
		its = space->is_table_next;    /* Current table size descriptor */
		size = its->its_size;          /* Target size for this growth step */
		oits = its - 1;                /* Previous table size descriptor */
		osize = oits->its_size;        /* Actual previous size */
		nits = its + 1;                /* Next potential table size descriptor */
		nsize = nits->its_size;        /* Actual next potential size */

		if (osize == size) { /* Table is already at the size indicated by 'its' (max size for current 'its') */
			is_write_unlock(space);
			return KERN_NO_SPACE; /* Cannot grow using current 'its'; may need new 'its' if not max */
		}

		assert((osize < size) && (size <= nsize)); /* Sanity checks */

		space->is_growing = TRUE;
		is_write_unlock(space); /* Unlock for memory allocation */

		if (it_entries_reallocable(oits)) /* Can we realloc in place? */
			table = it_entries_realloc(oits, otable, its);
		else
			table = it_entries_alloc(its); /* Allocate new table */

		is_write_lock(space); /* Relock space */
		space->is_growing = FALSE;

		if (table == IE_NULL) {
			is_write_unlock(space);
			thread_wakeup((event_t) space); /* Wake waiters who might have been blocked on is_growing */
			return KERN_RESOURCE_SHORTAGE;
		}

		if (!space->is_active) { /* Space died while we were unlocked */
			is_write_unlock(space);
			thread_wakeup((event_t) space);
			it_entries_free(its, table); /* Free newly allocated table */
			/* otable is still the one in the (now dead) space struct, will be freed with space */
			is_write_lock(space); /* Lock for consistency, though space is dead */
			return KERN_SUCCESS;  /* Or KERN_INVALID_TASK, but caller might retry */
		}

		/* Ensure no other thread modified space state while unlocked */
		assert(space->is_table == otable);
		assert(space->is_table_next == its);
		assert(space->is_table_size == osize);

		/* Update space to use the new table */
		space->is_table = table;
		space->is_table_size = size;
		space->is_table_next = nits; /* Point to next size descriptor */

		if (!it_entries_reallocable(oits)) { /* If new table was allocated, copy old content */
			(void) memcpy((void *) table, (const void *) otable,
			      osize * sizeof(struct ipc_entry));
		}

		/* Clear ie_index for old entries (used by some hash schemes, now zeroed for safety) */
		for (i = 0; i < osize; i++)
			table[i].ie_index = 0;

		/* Initialize newly added part of the table to zero */
		(void) memset((void *) (table + osize), 0,
		      (size - osize) * sizeof(struct ipc_entry));

		/* Re-hash existing send rights from the old table part into the (potentially new) hash table */
		for (i = 0; i < osize; i++) {
			ipc_entry_t entry = &table[i];
			if (IE_BITS_TYPE(entry->ie_bits) == MACH_PORT_TYPE_SEND) {
				/* If !it_entries_reallocable, old hash entries are stale.
				 * If realloced, hash entries might still be valid if hash table not instance based.
				 * Assuming ipc_hash_local_insert handles duplicates or updates correctly.
				 */
				ipc_hash_local_insert(space, entry->ie_object, i, entry);
			}
		}

		/* Migrate eligible entries from the splay tree to the newly expanded table part */
		if (space->is_tree_total > 0) {
			mach_port_index_t current_idx; /* Corrected type for index */
			boolean_t delete_node;
			struct ipc_splay_tree tree_part_ignore, tree_part_tomove, tree_part_tosmall;
			ipc_entry_num_t new_small_count;
			ipc_tree_entry_t tentry;

			/* Split tree into: <osize, [osize,size), [size,nsize), >=nsize */
			ipc_splay_tree_split(&space->is_tree, MACH_PORT_MAKE(nsize, 0), &tree_part_tosmall);
			ipc_splay_tree_split(&tree_part_tosmall, MACH_PORT_MAKE(size, 0), &tree_part_tomove);
			ipc_splay_tree_split(&tree_part_tomove, MACH_PORT_MAKE(osize, 0), &tree_part_ignore);

			/* Process entries that can now move from tree to table ([osize, size) range) */
			for (tentry = ipc_splay_traverse_start(&tree_part_tomove);
			     tentry != ITE_NULL;
			     tentry = ipc_splay_traverse_next(&tree_part_tomove, delete_node)) {
				mach_port_t entry_name = tentry->ite_name;
				mach_port_gen_t entry_gen = MACH_PORT_GEN(entry_name);
				mach_port_index_t entry_idx = MACH_PORT_INDEX(entry_name);
				ipc_entry_t table_slot_entry;

				assert(tentry->ite_space == space);
				assert((osize <= entry_idx) && (entry_idx < size));

				table_slot_entry = &table[entry_idx];

				if (IE_BITS_TYPE(table_slot_entry->ie_bits) != MACH_PORT_TYPE_NONE) { /* Table slot unexpectedly occupied? */
					assert(IE_BITS_GEN(table_slot_entry->ie_bits) != entry_gen); /* Must be different gen */
					table_slot_entry->ie_bits |= IE_BITS_COLLISION; /* Mark collision */
					delete_node = FALSE; /* Don't delete from tree yet */
					continue;
				}

				/* Move tree entry to table */
				table_slot_entry->ie_bits = tentry->ite_bits | entry_gen;
				table_slot_entry->ie_object = tentry->ite_object;
				table_slot_entry->ie_request = tentry->ite_request;

				if (IE_BITS_TYPE(tentry->ite_bits) == MACH_PORT_TYPE_SEND) {
					ipc_hash_global_delete(space, tentry->ite_object, entry_name, (ipc_entry_t)tentry);
					ipc_hash_local_insert(space, table_slot_entry->ie_object, entry_idx, table_slot_entry);
				}
				space->is_tree_total--;
				delete_node = TRUE; /* Mark for deletion from tree_part_tomove */
				ite_free(tentry);   /* Free the tree node structure */
			}
			ipc_splay_traverse_finish(&tree_part_tomove);

			/* Recalculate is_tree_small based on entries in [size, nsize) range */
			new_small_count = 0; current_idx = (mach_port_index_t)-1; /* Ensure first entry counts */
			for (tentry = ipc_splay_traverse_start(&tree_part_tosmall);
			     tentry != ITE_NULL;
			     tentry = ipc_splay_traverse_next(&tree_part_tosmall, FALSE)) {
				mach_port_index_t nindex = MACH_PORT_INDEX(tentry->ite_name);
				if (nindex != current_idx) { /* Count unique indices in this range */
					new_small_count++;
					current_idx = nindex;
				}
			}
			ipc_splay_traverse_finish(&tree_part_tosmall);
			space->is_tree_small = new_small_count;

			/* Reconstruct the main splay tree */
			ipc_splay_tree_join(&space->is_tree, &tree_part_tosmall);
			ipc_splay_tree_join(&space->is_tree, &tree_part_tomove); /* Should be empty */
			ipc_splay_tree_join(&space->is_tree, &tree_part_ignore);
		}

		/* Add newly available table slots to the free list (in reverse order for natural name allocation) */
		free_index_head = table[0].ie_next; /* Current head of free list */
		for (i = size - 1; i >= osize; --i) {
			ipc_entry_t current_new_entry = &table[i];
			if (IE_BITS_TYPE(current_new_entry->ie_bits) == MACH_PORT_TYPE_NONE) { /* If not filled by tree migration */
				current_new_entry->ie_bits = IE_BITS_GEN_MASK; /* Initialize with max generation */
				current_new_entry->ie_next = free_index_head;
				free_index_head = i;
			}
		}
		table[0].ie_next = free_index_head; /* Set new head of free list */

		/* Free the old table memory if a new one was allocated */
		if (!it_entries_reallocable(oits)) {
			is_write_unlock(space); /* Unlock for memory deallocation */
			thread_wakeup((event_t) space); /* Wake up any waiters */
			it_entries_free(oits, otable);
			is_write_lock(space); /* Relock */
		} else { /* Realloc happened, just wake up */
			is_write_unlock(space);
			thread_wakeup((event_t) space);
			is_write_lock(space);
		}

		if (!space->is_active || (space->is_table_next != nits)) /* State changed while unlocked? */
			return KERN_SUCCESS; /* Let caller retry if needed */

	} while ((space->is_tree_small > 0) && /* Check if further growth is beneficial */
		 (((nsize - size) * sizeof(struct ipc_entry)) <
		  (space->is_tree_small * sizeof(struct ipc_tree_entry))));

	return KERN_SUCCESS;
}


#if	MACH_KDB
#include <ddb/db_output.h>
/**
 * @def printf
 * @brief In kernel debugging (MACH_KDB) context, map printf to kdbprintf.
 */
#define	printf	kdbprintf

/**
 * @brief Kernel debugger function to look up an IPC object by task and port name.
 * This function is only available if MACH_KDB is enabled.
 * @param task The task whose IPC space to search.
 * @param name The Mach port name to look up.
 * @return Pointer to the `ipc_entry_t` representing the kernel object if found,
 *         otherwise `IE_NULL`. It prints debug information if the object is found.
 */
ipc_entry_t	db_ipc_object_by_name(
			task_t		task,
			mach_port_t	name);


/**
 * @implementation db_ipc_object_by_name
 */
ipc_entry_t
db_ipc_object_by_name(
	task_t		task,
	mach_port_t	name)
{
        ipc_space_t space = task->itk_space;
        ipc_entry_t entry;
 
 
        entry = ipc_entry_lookup(space, name);
        if(entry != IE_NULL) {
                iprintf("(task 0x%x, name 0x%x) ==> object 0x%x", /* Assuming iprintf is kdbprintf */
			(unsigned int)task, (unsigned int)name, (unsigned int)entry->ie_object); /* Casts for printf */
                return (ipc_entry_t) entry->ie_object; /* Returns the object pointer, not the entry itself */
        }
        return entry; /* Returns IE_NULL if not found */
}
#endif	/* MACH_KDB */
