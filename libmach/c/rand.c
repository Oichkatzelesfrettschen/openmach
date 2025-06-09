/* SPDX-License-Identifier: Utah-BSD-Style */
/* See LICENSE file for full copyright notice */

#include <sys/types.h>
#include <stdlib.h>

static unsigned seed[2];

/**
 * @brief Pseudo-random number generator.
 *
 * @return A random integer in the range [0, RAND_MAX].
 */
int
rand(void)
{
	seed[0] += 0xa859c317;
	seed[0] += (seed[1] << 13) | (seed[1] >> 19);
	seed[1] += seed[0];
	return seed[0] % ((u_long)RAND_MAX + 1);
}

/**
 * @brief Seed the pseudo-random number generator.
 *
 * @param new_seed Initial seed value.
 */
void
srand(unsigned new_seed)
{
	seed[0] = seed[1] = new_seed;
}

#if 0 /* test code */

#define CYCLES 100000000

void main(int argc, char **argv)
{
	unsigned orig_seed = atol(argv[1]);
	int i;

	srand(orig_seed);
	for(i = 0; i < CYCLES; i++)
	{
		int r = rand();
		/*printf("%08x\n", r);*/
		if ((seed[0] == orig_seed) && (seed[1] == orig_seed))
		{
			printf("repeates after %d cycles\n", i);
			exit(0);
		}
	}
	printf("still not repeating after %d cycles\n", CYCLES);
}

#endif

