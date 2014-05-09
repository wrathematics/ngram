// Copyright 2013-2014, Heckendorf

#include <stdlib.h>
#include <string.h>

#include "rng_interface.h"
#include "mt/rand_mt.h"
#include "mrg/rand_mrg.h"

static const struct rng_funcs funclist[]={
	{NULL,NULL,NULL},
	{mt_init_gen, mt_check, mt_extract},
	{mrg_init, mrg_check, mrg_gen}
};

static size_t state_size(const int type){
	if(type==RNG_TYPE_MT){
		return sizeof(mt_state_t);
	}
	else if(type==RNG_TYPE_MRG){
		return sizeof(mrg_state_t);
	}
	else{
		/* error */
		return 0;
	}
}

static void* create_state(const int type){
	size_t statesize;

	statesize=state_size(type);

	if(statesize)
		return malloc(statesize);
	else /* error */
		return NULL;
}

void rng_set_type(rng_state_t *rs, int type){
	if(type<=RNG_TYPE_INVALID || type>=RNG_TYPE_UNKNOWN)
		type=RNG_TYPE_INVALID+1; // Is MT safer?

	if(rs->type!=type){
		rs->type=type;
		if(rs->state){
			free(rs->state);
		}
		rs->state=create_state(type);
		/* TODO: Check if it was able to allocate */
	}
	else if(rs->state==NULL){
		rs->state=create_state(type);
	}

	memset(rs->state,0,state_size(type));
	memcpy(&rs->f,funclist+type,sizeof(rs->f));
}

void rng_prepare(rng_state_t *rs){
	memset(rs,0,sizeof(*rs));
	rs->type=RNG_TYPE_INVALID;
}

void rng_check(rng_state_t *rs){
	rs->f.check(rs->state);
}

void rng_init(rng_state_t *rs, const uint32_t seed){
	rs->f.init(rs->state,seed);
}

uint32_t rng_extract(rng_state_t *rs){
	return rs->f.extract(rs->state);
}

void rng_free(rng_state_t *rs){
	if(rs->state)
		free(rs->state);
}
