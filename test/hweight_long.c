/* Minimal Linux-like bit manipulation helper functions test
 *
 * Copyright (c) 2012-2017, Sven Eckelmann <sven@narfation.org>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#include "../bitops.h"
#include <assert.h>
#include <limits.h>
#include <stddef.h>

#include "common.h"

static unsigned int trivial_hweight(unsigned long x)
{
	size_t i;
	unsigned int c = 0;

	for (i = 0; i < BITS_PER_LONG; i++) {
		if ((1UL << i) & x)
			c++;
	}

	return c;
}

int main(void)
{
	size_t i;
	unsigned long x;

	assert(hweight_long(0) == 0);
	assert(hweight_long(1) == 1);
	assert(hweight_long(2) == 1);
	assert(hweight_long(3) == 2);
	assert(hweight_long(ULONG_MAX) == BITS_PER_LONG);

	for (i = 0; i < 1024; i++) {
		x = get_unsigned_long();

		assert(hweight_long(x) == trivial_hweight(x));
	}

	return 0;
}
