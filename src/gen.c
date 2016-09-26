/*  Copyright (c) 2014, Schmidt
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


#include "ngram.h"


SEXP R_ngram_gen(SEXP ngl_ptr, SEXP genlen, SEXP seed)
{
  rng_state_t rs;
  SEXP RET;
  ngramlist_t *ngl = (ngramlist_t *) getRptr(ngl_ptr);
  int retlen;
  char *ret;
  
  rng_prepare(&rs);
  rng_set_type(&rs, RNG_TYPE_MT);
  rng_init(&rs, INT(seed));
  
  retlen = ngram_gen(&rs, ngl, INT(genlen), &ret);
  
  rng_free(&rs);
  
  if (retlen < 0)
    error("allocation error");
  
  PROTECT(RET = allocVector(STRSXP, 1));
  SET_STRING_ELT(RET, 0, mkCharLen(ret, retlen));
  free(ret);
  
  UNPROTECT(1);
  return RET;
}
