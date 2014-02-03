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

#include "hashes.h"
#include "random.h"
#include "bloom.h"

#include "include/bloom_test.h"
#include "include/sets.h"

#define MYSEED 0x83d385c0 /* random number */

// Eingabepuffer enthält immer nur EIN Wort.
uint32_t* current_element;
// Enthält alle Wörter
uint32_t* set;
// Einfügepuffer enthält ALLE eingefügten Wörter.
uint32_t* subset;
// Zeiger, der immer auf die aktuelle Position in BUFFER_INSERTED zeigt.
uint32_t* insertion_pos;

void test_start(size_t num_hashes, size_t array_size, uint8_t input_length,
		uint8_t num_words) {
	printf("------ test_start ------ \n");
	printf("------ Hallo!!!!! ------ \n");
	printf("------ num_hashes: %d ------ \n", num_hashes);
	// Hashfunktionen durchlaufen
	for (uint8_t current_hash_nr = 1; current_hash_nr < num_hashes;
			current_hash_nr++) {
		// array size durchlaufen
		for (uint8_t current_array_size = 2; current_array_size < array_size;
				current_array_size++) {
			struct bloom_t *bloom;

			switch (current_hash_nr) {
			case 2:
				bloom = bloom_new(current_array_size, current_hash_nr, fnv_hash,
						sax_hash);
				break;
			case 3:
				bloom = bloom_new(current_array_size, current_hash_nr, fnv_hash,
						sax_hash, sdbm_hash);
				break;
			case 4:
				bloom = bloom_new(current_array_size, current_hash_nr, fnv_hash,
						sax_hash, sdbm_hash, djb2_hash);
				break;
			case 5:
				bloom = bloom_new(current_array_size, current_hash_nr, fnv_hash,
						sax_hash, sdbm_hash, djb2_hash, kr_hash);
				break;
			case 6:
				bloom = bloom_new(current_array_size, current_hash_nr, fnv_hash,
						sax_hash, sdbm_hash, djb2_hash, kr_hash, dek_hash);
				break;
			case 7:
				bloom = bloom_new(current_array_size, current_hash_nr, fnv_hash,
						sax_hash, sdbm_hash, djb2_hash, kr_hash, dek_hash,
						rotating_hash);
				break;
			case 8:
				bloom = bloom_new(current_array_size, current_hash_nr, fnv_hash,
						sax_hash, sdbm_hash, djb2_hash, kr_hash, dek_hash,
						rotating_hash, one_at_a_time_hash);
				break;
			default:
				continue;
				break;
				//	TODO: default -> Abbrechen und nicht den Test in der nächsten for Schleife starten.
			}
			struct bloom_t *bloom = bloom_new(1 << 7, 6, fnv_hash, sax_hash,
					sdbm_hash, djb2_hash, kr_hash, dek_hash, rotating_hash,
					one_at_a_time_hash);

			printf("Testing Bloom filter.\n\n");
			printf("m: %zd\nk: %zd\n\n", bloom->m, bloom->k);

			for (int i = 0; i < lenB; i++) {
				bloom_add(bloom, (const uint8_t *) B[i], strlen(B[i]));
				printf("Added \"%s\"\n", B[i]);
			}

			int in = 0;
			int not_in = 0;

			for (int i = 0; i < lenA; i++) {
				if (bloom_check(bloom, (const uint8_t *) A[i], strlen(A[i]))) {
					in++;
				} else {
					not_in++;
				}
			}

			printf("\n");
			printf("%d elements probably in the filter.\n", in);
			printf("%d elements not in the filter.\n", not_in);
			double false_positive_rate = (double) in / (double) lenA;
			printf("%f false positive rate.\n", false_positive_rate);

			bloom_del(bloom);
			printf("\nAll done!\n");

			// Set pointer to start of buffer.
			insertion_pos = subset;
			for (int i = 0; i < num_words; i++) {
				bool result;
				result = bloom_check(bloom, (uint8_t*) insertion_pos,
						input_length * 4);
				printf("%d\n", result);
				insertion_pos += input_length;
			}
			free(bloom->a);
		}
	}
	printf("fertig!");
	free(subset);
	free(current_element);
}

void fill_buffer(uint32_t* buffer, uint32_t buffer_len) {
	// Input buffer füllen
	for (uint32_t i = 0; i < buffer_len; i++) {
		buffer[i] = genrand_uint32();
	}
}

void test_init(uint8_t input_length, uint8_t num_words) {
	printf("Bloom testing initialized...\n");
	genrand_init(MYSEED);
	current_element = (uint32_t*) malloc(input_length * 4);
	subset = (uint32_t*) malloc(num_words * input_length * 4);
	printf("inserted_buffer is %d big.", num_words * input_length);
}
