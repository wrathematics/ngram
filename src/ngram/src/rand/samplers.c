// Copyright 2014, Schmidt and Heckendorf

#include <time.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

#include "rand.h"


// sample from min/max
int sample(rng_state_t *rs, const int min, const int max)
{
  int ret;
  
  // Check that the RNG has been initialized; if not, start it
/*  rng_check(rs);*/
  
  ret = min + (int) ((double)(max-min + 1) * rng_extract(rs)*I32BIT);
  
  return ret;
}


