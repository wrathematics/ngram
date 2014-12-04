#ifndef NGRAM_SUMMARY_H
#define NGRAM_SUMMARY_H


typedef struct ngsummary_t {
  int longest;
  int longest_nch;
  int shortest;
  int shortest_nch;
  int *commonest;
  int num_commonest;
} ngsummary_t;

void ngram_summary(ngramlist_t *ngl, int num_commonest);
void ngram_summary_ptrs(const int n, const ngram_t *ng, const int ngsize, ngsummary_t *ngsummary);


#endif
