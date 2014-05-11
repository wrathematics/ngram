// Copyright 2013-2014, Schmidt and Heckendorf

#include <time.h>
#include <math.h>
#include <stdlib.h>

#include "../rand.h"
#include "rand_mt.h"

// ###################### //
// Mersenne Twister 19937 //
// ###################### //

void mt_init(void *vrs, const uint32_t seed)
{
  mt_state_t *rs=(mt_state_t*)vrs;
  
  mt_init_gen(rs,seed);
  rs->initialized = 1;
  rs->index = 0;
}

void mt_check(void *vrs)
{
	mt_state_t *rs=(mt_state_t*)vrs;
  unsigned int seed;
  
  if (rs->initialized != 1)
  {
    seed = (unsigned int) time(NULL);
    mt_init_gen(rs,seed);
    rs->initialized = 1;
  }
}

void mt_init_gen(void *vrs, const uint32_t seed)
{
  mt_state_t *rs=(mt_state_t*)vrs;
  int i;
  uint32_t *MT=rs->MT;
  
  MT[0]=seed;
  
  for(i=1;i<MT_SIZE;i++)
    MT[i]=0xFFFFFFFF&(0x6C078965 * (MT[i-1] ^ ((MT[i-1])>>30)) + i);
}

void mt_gen(void *vrs)
{
  mt_state_t *rs=(mt_state_t*)vrs;
  int i;
  uint32_t y;
  uint32_t *MT=rs->MT;
  
  for(i=0;i<MT_SIZE;i++)
  {
    y=(MT[i]&0x80000000) + (MT[(i+1)%MT_SIZE] & 0x7FFFFFFF);
    MT[i]=MT[(i+397)%MT_SIZE] ^ (y>>1);
    
    if(y%2!=0)
      MT[i]^=0x9908B0DF;
  }
}

uint32_t mt_extract(void *vrs)
{
  mt_state_t *rs=(mt_state_t*)vrs;
  uint32_t y;
  
  if(rs->index==0)
    mt_gen(rs);
  
  y=rs->MT[rs->index];
  y^=y>>11;
  y^=(y<<7)&0x9D2C5680;
  y^=(y<<15)&0xEFC60000;
  y^=y>>18;
  
  rs->index=(rs->index+1)%MT_SIZE;
  
  return y;
}

