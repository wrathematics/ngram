/* Automatically generated. Do not edit by hand. */

#include <R.h>
#include <Rinternals.h>
#include <R_ext/Rdynload.h>
#include <stdlib.h>

extern SEXP R_ng_get_phrasetable(SEXP ng_ptr, SEXP ngsize_);
extern SEXP R_ngram_gen(SEXP ngl_ptr, SEXP genlen, SEXP seed);
extern SEXP R_ngram_get_seed();
extern SEXP R_ngram_wordcount(SEXP str, SEXP sep);
extern SEXP R_stringsummary(SEXP string, SEXP wordlen_max_, SEXP senlen_max_, SEXP syllen_max_);
extern SEXP R_ng_asweka(SEXP R_str, SEXP min_n_, SEXP max_n_, SEXP R_sep);
extern SEXP R_ng_corpus_order(SEXP ng_ptr, SEXP ngsize_);
extern SEXP R_ng_extract_ngrams(SEXP ng_ptr, SEXP ngsize_);
extern SEXP R_ng_extract_str(SEXP str_ptr, SEXP R_strlen);
extern SEXP R_ng_print(SEXP ng_ptr, SEXP ngsize_, SEXP truncated);
extern SEXP R_ng_process(SEXP R_str, SEXP R_str_len, SEXP n_, SEXP R_sep);

static const R_CallMethodDef CallEntries[] = {
  {"R_ng_get_phrasetable", (DL_FUNC) &R_ng_get_phrasetable, 2},
  {"R_ngram_gen", (DL_FUNC) &R_ngram_gen, 3},
  {"R_ngram_get_seed", (DL_FUNC) &R_ngram_get_seed, 0},
  {"R_ngram_wordcount", (DL_FUNC) &R_ngram_wordcount, 2},
  {"R_stringsummary", (DL_FUNC) &R_stringsummary, 4},
  {"R_ng_asweka", (DL_FUNC) &R_ng_asweka, 4},
  {"R_ng_corpus_order", (DL_FUNC) &R_ng_corpus_order, 2},
  {"R_ng_extract_ngrams", (DL_FUNC) &R_ng_extract_ngrams, 2},
  {"R_ng_extract_str", (DL_FUNC) &R_ng_extract_str, 2},
  {"R_ng_print", (DL_FUNC) &R_ng_print, 3},
  {"R_ng_process", (DL_FUNC) &R_ng_process, 4},
  {NULL, NULL, 0}
};

void R_init_ngram(DllInfo *dll)
{
  R_registerRoutines(dll, NULL, CallEntries, NULL, NULL);
  R_useDynamicSymbols(dll, FALSE);
}
