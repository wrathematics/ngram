#include "lex.h"
#include "process.h"
#include <stdio.h>
#include <string.h>

static void *vptr;

void print_word(word_t *word){
	int i;

	if(word==NULL){
		printf("NULL ");
		return;
	}

	for(i=0;i<word->len;i++)
		putchar(word->s[i]);
	putchar(' ');
}

void print_ngram(ngram_t *ng){
	wordlist_t *wl=ng->words;
	nextwordlist_t *nwl=ng->nextword;

	while(wl){
		print_word(wl->word);
		wl=wl->next;
	}
	putchar('\n');

	while(nwl){
		print_word(nwl->word.word);
		printf("{%d} | ",nwl->word.count);
		nwl=nwl->next;
	}
	putchar('\n');
	putchar('\n');

	free_list(ng->words);
	free_list(ng->nextword);
}

int main(){
	//const char *str="a bird is a dog man, a bird";
	//const int n=1;
	const char *str="tofu eats beans tofu eats rice nice";
	const int n=2;
	wordlist_t *wl;
	ngram_t *ng;
	int ngsize;
	int i;


	wl=lex(str,strlen(str));
	ng=process(wl,n,&ngsize);

	for(i=0;i<ngsize;i++){
		print_ngram(ng+i);
	}

	free_wordlist(wl);

	return 0;
}
