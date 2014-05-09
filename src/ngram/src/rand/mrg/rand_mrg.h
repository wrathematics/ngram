#ifndef SHUFFLER_RAND_MRG_H
#define SHUFFLER_RAND_MRG_H

#include <stdint.h>

typedef struct mrg_state_t{
	uint32_t x1n[3];
	uint32_t x2n[3];
	int initialized;
}mrg_state_t;

#define M1 4294967087
#define M2 4294944443
#define A12 1403580
#define A21 527612
#define A13 810728
#define A23 1370589
#define SEED_MASK 0x1F
#define SEED_SHIFT 5

void mrg_check(void *vrs);
void mrg_init(void *vrs,const uint32_t seed);
uint32_t mrg_gen(void *vrs);
double mrg_unifgen(void *vrs);

#endif
