#include "print.h"
#include "process.h"


#include "strings.h"


int main(){
	const char *str="asdf asdf asdf qwer asdf qwer qwer asdf";
	const int n=2;
	wordlist_t *wl;
	ngram_t *ng;
	int ngsize;
	int i;

	wl=lex(str,strlen(str));
	ng=process(wl,n,&ngsize);

	if(ng==NULL){
		printf("No ngrams\n");
	}
	else{
		for(i=0;i<ngsize;i++){
			print_ngram(ng+i);
		}
	}
	
/*	printf("%d\n", ngram_counts_total(ng, ngsize));*/

	free_wordlist(wl);

	return 0;
}
