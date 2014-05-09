// Copyright 2013-2014, Heckendorf

#include <time.h>
#include <unistd.h>
#include <math.h>
#include <stdlib.h>

#include "rand_mrg.h"

// ######## //
// MRG32k3a //
// ######## //

void mrg_check(void *vrs){
	mrg_state_t *rs=(mrg_state_t*)vrs;
	unsigned int seed;

	if (rs->initialized != 1)
	{
		seed = time(NULL) * getpid();
		mrg_init(rs,seed);
		rs->initialized = 1;
	}
}

void mrg_init(void *vrs, const uint32_t seed){
	mrg_state_t *rs=(mrg_state_t*)vrs;
	int i;
	uint32_t sp=seed;

	rs->initialized=1;
	//rs->x1n[0]=seed;
	//rs->x2n[0]=1;
	for(i=0;i<3;i++){
		rs->x1n[i]=sp&SEED_MASK;
		sp>>=SEED_SHIFT;
		rs->x2n[i]=sp&SEED_MASK;
		sp>>=SEED_SHIFT;
	}
	rs->x1n[0]|=sp<<SEED_SHIFT;

	if(!(rs->x1n[0] || rs->x1n[1] || rs->x1n[2]))
		rs->x1n[0]=1;
	if(!(rs->x2n[0] || rs->x2n[1] || rs->x2n[2]))
		rs->x2n[0]=1;
}

uint32_t mrg_gen(void *vrs){
	mrg_state_t *rs=(mrg_state_t*)vrs;
	int i;
	uint32_t n[3];

	n[0]=(               A12*rs->x1n[1]-A13*rs->x1n[0])%M1;
	n[1]=(A21*rs->x2n[2]-               A23*rs->x2n[0])%M2;
	n[2]=(n[0]+n[1])%M1;

	for(i=1;i<3;i++){
		rs->x1n[i-1]=rs->x1n[i];
		rs->x2n[i-1]=rs->x2n[i];
	}
	rs->x1n[2]=n[0];
	rs->x2n[2]=n[1];

	return n[2];
}

double mrg_unifgen(void *vrs){
	mrg_state_t *rs=(mrg_state_t*)vrs;
	return (double)mrg_gen(rs)/(double)M1;
}
