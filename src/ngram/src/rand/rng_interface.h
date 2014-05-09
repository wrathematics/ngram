#ifndef SHUFFLER_RNG_INTERFACE_H
#define SHUFFLER_RNG_INTERFACE_H

#include <stdint.h>

enum rng_type{
	RNG_TYPE_INVALID=0,
	RNG_TYPE_MT,
	RNG_TYPE_MRG,
	RNG_TYPE_UNKNOWN
};

struct rng_state_s;

typedef void (*rng_init_f)(void*,const uint32_t);
typedef void (*rng_check_f)(void*);
typedef uint32_t (*rng_extract_f)(void*);

struct rng_funcs{
	rng_init_f init;
	rng_check_f check;
	rng_extract_f extract;
};

typedef struct rng_state_s{
	void *state;
	int type;
	struct rng_funcs f;
}rng_state_t;

void rng_prepare(rng_state_t *rs);
void rng_set_type(rng_state_t *, int type);
void rng_check(rng_state_t *);
void rng_init(rng_state_t *, const uint32_t seed);
uint32_t rng_extract(rng_state_t *);
void rng_free(rng_state_t *rs);

#endif
