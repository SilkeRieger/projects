/*
 * Copyright (C) 2014 Silke Rieger <srieger@inf.fu-berlin.de>
 *
 * This file subject to the terms and conditions of the GNU Lesser General
 * Public License. See the file LICENSE in the top level directory for more
 * details.
 */

#include <inttypes.h>

#include <stdio.h>

#include "hashes.h"
#include "bloom.h"
#include "hwtimer.h"
#include "include/bloom_test.h"

//#include "random.h"
	//size_t m = 128;	// m is the number of bits in the array
	//size_t k = 8;		// k is the number of hash functions

	//size_t size; 		// size of the bit array in the filter
	//size_t num_hashes = 8;	// the number of hash functions

int main(void)
{
	// Part for testing.
	uint8_t input_length = 50;
	uint8_t num_words = 4;
	test_init(input_length, num_words);
	test_start(8, 4, input_length, num_words);
	return 1;
}


	// n=9 => 0000 0000 | 0000 0000 | 0000 0000
	// 0000 0001 => 0000 0010
	//
	// 8 % 8 = 0000 0010
	//
	// SETBIT(a, n) (a[n/CHAR_BIT] |= (128>>(n%CHAR_BIT)))
	//                  a                b
	// SETBIT(a, n) (a[n/8] |= (1<<(n%8))
    // n= 9 =>  a[9/8] = a[9/8] | (1<<(9%8))
	//          a[1] = a[1] | (1 << 1)
	//          a[1] = xxxx xxxx | 0000 0010 => xxxx xx1x
	//          a[0] = 1 oder 0
	//          a[0] = xx1x xxxx
	// SETBIT(a, n) (a[n/8] = a[n/8] | (1<<(n%8))



