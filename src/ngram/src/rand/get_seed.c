#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>

#include "platform.h"


#if OS_WINDOWS
#include <process.h>
#elif OS_NIX
#include <sys/types.h>
#include <unistd.h>
#endif


// Robert Jenkins' 96 bit Mix Function
uint32_t mix_96(uint32_t a, uint32_t b, uint32_t c)
{
  a=a-b;  a=a-c;  a=a^(c >> 13);
  b=b-c;  b=b-a;  b=b^(a << 8);
  c=c-a;  c=c-b;  c=c^(b >> 13);
  a=a-b;  a=a-c;  a=a^(c >> 12);
  b=b-c;  b=b-a;  b=b^(a << 16);
  c=c-a;  c=c-b;  c=c^(b >> 5);
  a=a-b;  a=a-c;  a=a^(c >> 3);
  b=b-c;  b=b-a;  b=b^(a << 10);
  c=c-a;  c=c-b;  c=c^(b >> 15);
  
  return c;
}



uint32_t ngram_get_seed()
{
  uint32_t pid;
  uint32_t ret;
  time_t t;
  
  #if OS_WINDOWS
  pid = _getpid();
  #elif OS_NIX
  pid = (uint32_t) getpid();
  #endif
  
  ret = mix_96(time(&t), pid, rand());
  
  return ret;
}





