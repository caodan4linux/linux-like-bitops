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
#include <stddef.h>
#include <stdint.h>

#include "common.h"

static unsigned int trivial_hweight(uint64_t x)
{
	size_t i;
	unsigned int c = 0;

	for (i = 0; i < BITS_PER_BYTE * sizeof(uint64_t); i++) {
		if ((UINT64_C(1) << i) & x)
			c++;
	}

	return c;
}

int main(void)
{
	size_t i;
	uint64_t x;

	assert(hweight64(0) == 0);
	assert(hweight64(1) == 1);
	assert(hweight64(2) == 1);
	assert(hweight64(3) == 2);
	assert(hweight64(UINT64_C(0xff)) == 8);
	assert(hweight64(UINT64_C(0xffff)) == 16);
	assert(hweight64(UINT64_C(0xffffff)) == 24);
	assert(hweight64(UINT64_C(0xffffffff)) == 32);
	assert(hweight64(UINT64_C(0xffffffffff)) == 40);
	assert(hweight64(UINT64_C(0xffffffffffff)) == 48);
	assert(hweight64(UINT64_C(0xffffffffffffff)) == 56);
	assert(hweight64(UINT64_C(0xffffffffffffffff)) == 64);

	for (i = 0; i < 1024; i++) {
		x = get_unsigned64();

		assert(hweight64(x) == trivial_hweight(x));
	}

	return 0;
}
