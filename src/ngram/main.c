#include "src/print.h"
#include "src/process.h"


int main(){
	const char *str="tofu eats beans eats beans tofu eats rice nice";
	const int n=2;
	wordlist_t *wl;
	ngram_t *ng;
	int ngsize;
	int i;
	double *x;
	x = malloc(268435451 * sizeof(double));

	wl=lex(str,strlen(str));
	ng=process(wl,n,&ngsize);

  
	for(i=0;i<ngsize;i++){
		print_ngram(ng+i);
	}
	
/*	printf("%d\n", ngram_counts_total(ng, ngsize));*/

  free(x);
	free_wordlist(wl);

	return 0;
}
