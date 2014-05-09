#ifndef SHUFFLER_RAND_MT_H
#define SHUFFLER_RAND_MT_H

#include <stdint.h>
#include "../rand.h"

typedef struct mt_state_t{
	uint32_t MT[MT_SIZE];
	int index;
	unsigned int initialized;
}mt_state_t;

void mt_check(void *vrs);
void mt_init_gen(void *vrs, const uint32_t seed);
void mt_gen(void *vrs);
uint32_t mt_extract(void *vrs);


#endif
