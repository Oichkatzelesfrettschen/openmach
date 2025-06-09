
#include <ctype.h>
#include <stdlib.h>

/**
 * @brief Convert a decimal string to a long.
 *
 * The function stops parsing when a non-digit character is
 * encountered.
 *
 * @param str ASCII string representation of a number.
 * @return Parsed long integer value.
 */
long
atol(const char *str)
{
	long n = 0;
	while (isdigit(*str))
	{
		n = (n * 10) + *str - '0';
		str++;
	}
	return n;
}

