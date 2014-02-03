/*
 * test_bloom.c
 *
 *  Created on: 28.01.2014
 *      Author: silke
 */

#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "hashes.h"
#include "random.h"
#include "bloom.h"

#include "include/bloom_test.h"
#include "include/sets.h"

struct bloom_t* create_bloom_filter(uint8_t hash_function_count,
		uint8_t array_size) {
	struct bloom_t* bloom;
	switch (hash_function_count) {
	case 2:
		bloom = bloom_new(array_size, hash_function_count, fnv_hash, sax_hash);
		break;
	case 3:
		bloom = bloom_new(array_size, hash_function_count, fnv_hash, sax_hash,
				sdbm_hash);
		break;
	case 4:
		bloom = bloom_new(array_size, hash_function_count, fnv_hash, sax_hash,
				sdbm_hash, djb2_hash);
		break;
	case 5:
		bloom = bloom_new(array_size, hash_function_count, fnv_hash, sax_hash,
				sdbm_hash, djb2_hash, kr_hash);
		break;
	case 6:
		bloom = bloom_new(array_size, hash_function_count, fnv_hash, sax_hash,
				sdbm_hash, djb2_hash, kr_hash, dek_hash);
		break;
	case 7:
		bloom = bloom_new(array_size, hash_function_count, fnv_hash, sax_hash,
				sdbm_hash, djb2_hash, kr_hash, dek_hash, rotating_hash);
		break;
	case 8:
		bloom = bloom_new(array_size, hash_function_count, fnv_hash, sax_hash,
				sdbm_hash, djb2_hash, kr_hash, dek_hash, rotating_hash,
				one_at_a_time_hash);
		break;
	default:
		continue;
		break;
	}
	return bloom;
}

void test_start(size_t num_hashes, size_t array_size /*, uint8_t num_words*/) {
	printf("------ test_start ------ \n");
	printf("------ num_hashes: %d ------ \n", num_hashes);
	// Hashfunktionen durchlaufen
	for (uint8_t current_hash_nr = 1; current_hash_nr < num_hashes;
			current_hash_nr++) {
		// array size durchlaufen
		for (uint8_t current_array_size = 2; current_array_size < array_size;
				current_array_size++) {

			struct bloom_t* bloom = create_bloom_filter(current_hash_nr, current_array_size);

			printf("Testing Bloom filter.\n\n");
			printf("m: %zd k: %zd\n", bloom->m, bloom->k);

			for (int i = 0; i < lenB; i++) {
				bloom_add(bloom, (const uint8_t *) B[i], strlen(B[i]));
				//printf("Added \"%s\"\n", B[i]);
			}

			int in = 0;
			int not_in = 0;

			// Diese Schleife prüft, ob Element aus A im bloom Filter ist.
			// in => ist in Bloom filter.
			// not_in => ist NICHT in bloom filter.
			for (int i = 0; i < lenA; i++) {
				if (bloom_check(bloom, (const uint8_t *) A[i], strlen(A[i]))) {
					in++;
				} else {
					not_in++;
				}
			}
			printf("\n");
			printf("%d elements are NOT in the filter but returned true (false_positive).\n", in);
			//printf("%d elements are NOT in the filter and returned false.\n", not_in);
			double false_positive_rate = (double) in / (double) lenA;
			printf("%f false positive rate.\n", false_positive_rate);

			in = 0;
			not_in = 0;
			for (int i = 0; i < lenB; i++) {
				if (bloom_check(bloom, (const uint8_t *) B[i], strlen(B[i]))) {
					in++;
				} else {
					not_in++;
				}
			}
			double false_negative_rate = (double) not_in / (double) lenB;
			printf("%d elements are IN the filter but returned false (false_negative).\n", not_in);
			printf("%f false negative rate.\n", false_negative_rate);
			assert(not_in == 0);

			bloom_del(bloom);
			printf("\nAll done!\n");
		}
	}
	printf("fertig!");
}
