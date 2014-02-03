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

int main(void)
{
	// Part for testing.
	//uint8_t num_words = 4;
	//test_init(input_length , num_words);
	test_start(8, 1 << 7/*, num_words*/);
	return 1;
}
