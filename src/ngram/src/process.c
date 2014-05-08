#include <string.h>

#include "process.h"

static void *vptr;

static int cmp_ngram(const void *a, const void *b){
	ngram_t **na=(ngram_t**)a;
	ngram_t **nb=(ngram_t**)b;

	if((*na)->tok<(*nb)->tok)
		return -1;
	else if((*na)->tok>(*nb)->tok)
		return 1;
	else{
		if((*na)->nextword->word.word==NULL)
			return -1;
		else if((*nb)->nextword->word.word==NULL)
			return 1;
		else if((*na)->nextword->word.word->tok<(*nb)->nextword->word.word->tok)
			return -1;
		else if((*na)->nextword->word.word->tok>(*nb)->nextword->word.word->tok)
			return -1;
	}
	return 0;
}

ngram_t* process(wordlist_t *words, int n, int *size){
	int i,j,js,len,reti;
	wordlist_t *p,*q,*nw;
	ngram_t *ret,*tmp,**sorted;

	len=0;
	p=words;
	while(p){
		len++;
		p=p->next;
	}
	len-=n-1;

	if((ret=malloc(sizeof(*ret)*len))==NULL)
		exit(1);

	if((tmp=malloc(sizeof(*tmp)*len))==NULL)
		exit(1);

	if((sorted=malloc(sizeof(*sorted)*len))==NULL)
		exit(1);

	nw=words;
	for(i=1;i<len;i++){
		q=p=nw->next;
		tmp[i].tok=get_token(p,n);
		for(j=0;j<n;j++){
			add_node(tmp[i].words);
			tmp[i].words->word=q->word;
			q=q->next;
		}
		tmp[i].nextword=NULL;
		add_node(tmp[i].nextword);
		tmp[i].nextword->word.word=nw->word;
		tmp[i].nextword->word.count=0;

		sorted[i]=tmp+i;

		nw=nw->next;
	}

	q=p=words;
	tmp->tok=get_token(p,n);
	for(j=0;j<n;j++){
		add_node(tmp->words);
		tmp->words->word=q->word;
		q=q->next;
	}
	add_node(tmp->nextword);
	tmp->nextword->word.word=NULL;
	sorted[0]=tmp;

	qsort(sorted,len,sizeof(*sorted),cmp_ngram);

	reti=0;
	for(i=0;i<len;i=j){
		js=i;
		for(j=i+1;j<len && sorted[j]->tok==sorted[i]->tok;j++){
			/* This may be a problem if we start working with more than one string (multiple NULLs) */
			if(sorted[js]->nextword->word.word!=NULL && sorted[j]->nextword->word.word!=NULL && sorted[j]->nextword->word.word->tok==sorted[js]->nextword->word.word->tok)
				sorted[js]->nextword->word.count++;
			else{
				sorted[js]->nextword->word.count++;
				add_node(sorted[js]->nextword);
				sorted[js]->nextword->word.count=1;
				sorted[js]->nextword->word.word=sorted[j]->nextword->word.word;
			}
			free_list(sorted[j]->words);
			free_list(sorted[j]->nextword);
		}
		if(j==i+1)
			sorted[i]->nextword->word.count=1;
		ret[reti].words=sorted[i]->words;
		ret[reti].nextword=sorted[i]->nextword;
		reti++;
	}

	free(sorted);
	free(tmp);

	*size=reti;
	return ret;
}
