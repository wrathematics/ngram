#ifndef __STATPACK_RAND_H
#define __STATPACK_RAND_H

#include "rng_interface.h"

#define I32BIT 2.328306437080797e-10
#define MT_SIZE 624


int sample(rng_state_t *rs, const int min, const int max);


#endif
