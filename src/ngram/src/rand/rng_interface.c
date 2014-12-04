/*  Copyright (c) 2013-2014, Heckendorf
    All rights reserved.
    
    Redistribution and use in source and binary forms, with or without
    modification, are permitted provided that the following conditions are met:
    
    1. Redistributions of source code must retain the above copyright notice,
    this list of conditions and the following disclaimer.
    
    2. Redistributions in binary form must reproduce the above copyright
    notice, this list of conditions and the following disclaimer in the
    documentation and/or other materials provided with the distribution.
    
    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
    "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
    TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
    PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
    CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
    EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
    PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
    PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
    LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
    NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
    SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/


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
