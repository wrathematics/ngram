/*  Copyright (c) 2013, Heckendorf
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


#ifndef RAND_RNG_INTERFACE_H
#define RAND_RNG_INTERFACE_H

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
