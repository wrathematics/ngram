/*  Copyright (c) 2022, Heckendorf
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


#include "hash.h"
#include "lex.h"
#include "common_defs.h"

static void *vptr;

enum find_return_types{
	TAB_FIRST=0,
	TAB_NEXT,
	TAB_MEM
};

#define add_hash_char(x,y) do \
							{y += x;\
							 y += (y<<10);\
							 y ^= (y>>6);}while(0)

#define hash_finalize(y) do \
						 {y += (y<<3);\
						  y ^= (y>>11);\
						  y += (y<<15);}while(0)

tok_t get_token(wordlist_t *word, const int num){
	tok_t ret;
	int i,j;

	ret=0;
	for(i=0;i<num;i++){
		for(j=0;j<word->word->len;j++){
			add_hash_char(word->word->s[j],ret);
		}
		word=word->next;
	}
	hash_finalize(ret);

	return ret;
}

/* Get the hash for a string, assuming NULL word sep. */
tok_t get_token_str(const char *s, const int num){
	int i;
	tok_t ret=0;

	for(i=num-1;i>=0;i--){
		add_hash_char(s[i],ret);
	}
	hash_finalize(ret);

	return ret;
}


int init_hashtable(struct hashtable *tab, int initial_size){
	ZEROINIT_MEM(tab->tab,initial_size);
	tab->size = initial_size;
	tab->n_vals = tab->filled= 0;

	return 0;

memerr:
	return 1;
}

static int grow_hashtab(struct hashtable *htab){
	var_t **temp = htab->tab;
	int i,j;
	uint32_t k;
	int new_size = 2*(htab->size);

	ZEROINIT_MEM(htab->tab,new_size);

	for(i=0;i<htab->size;i++){
		if(temp[i]==NULL)
			continue;
		
		k = temp[i]->rawhash;

		for(j=k%new_size;htab->tab[j]!=NULL;j=(j+1+k)%new_size);
		htab->tab[j] = temp[i];
	}
	free(temp);

	htab->size = new_size;

	return 0;
memerr:
	return 1;
}

static int find_hashtab_index(tok_t k, struct hashtable *htab){
	int i;
	int index;
	int ret = -1;

	return k%htab->size;

	for(i=0;i<htab->size;i++){
		index = (i+k)%htab->size;
		if(htab->tab[index]==NULL){
			if(ret<0)
				ret = index;
			break;
		}

		if(htab->tab[index]->rawhash==k)
			return index;
	}

	return ret;
}

static val_list_t** find_hashtab_item(tok_t k, void *value, struct hashtable *htab, int *type, int (*eqfn)(void*, void*)){
	int index;
	val_list_t *vp;

	index = find_hashtab_index(k,htab);
	if(htab->tab[index]==NULL){ // first entry in the slot
		INIT_MEM(htab->tab[index],1);
		htab->tab[index]->rawhash = k;
		htab->tab[index]->vlist = NULL;
		goto first;
	}

	if(htab->tab[index]->vlist!=NULL){
		vp = htab->tab[index]->vlist;
		if(eqfn(value,vp->value)){
			goto first;
		}

		while(vp->next && !eqfn(value,vp->next->value))
			vp = vp->next;
		//if(vp->next == NULL) // not found
		//	goto first;
		*type = TAB_NEXT;
		return &vp->next;
	}

first:
	*type = TAB_FIRST;
	return &htab->tab[index]->vlist;
memerr:
	*type = TAB_MEM;
	return NULL;
}

#define rtype_ptr(rtype,vp) (rtype==TAB_FIRST?*vp:(*vp)->next)
#define rtype_value(rtype,vp) (rtype_ptr(rtype,vp))->value
int update_hashtable_value(tok_t k, void *value, struct hashtable *htab, int (*eqfn)(void*, void*), int (*updatefn)(void**, void*)){
	val_list_t **vp;
	int rtype;
/*
	if(htab->filled>(htab->size/32)) // TODO: configurable val and fix grow (unlist and update)
		if(grow_hashtab(htab))
			goto memerr;
*/

	vp = find_hashtab_item(k, value, htab, &rtype, eqfn);
	if(vp == NULL)
		goto memerr;

	if(*vp && updatefn){ // update previously seen value
		if(updatefn(&((*vp)->value),value))
			goto memerr;
	} else { // no updates; insert new
		add_node_ref(vp);
		(*vp)->value = value;
		htab->filled++;
		htab->n_vals++;
	}

	return 0;

memerr:
	return 1;
}

int get_hashtable_index(const tok_t k, struct hashtable *htab){
	int index;

	index = find_hashtab_index(k,htab);
	if(htab->tab[index]==NULL){
		return -1;
	}
	return index;
}

int ngram_update(void **d, void *s){
	ngram_t **dst = (ngram_t **)d;
	ngram_t *src = (ngram_t*)s;
#ifdef NEXTWORDS
	nextwordlist_t *nwp = (*dst)->nextword;
#endif

	(*dst)->count++;
	src->count = 0; // indicate that we didn't need this ngram

#ifdef NEXTWORDS
	while(nwp){
		if(nwp->word.word == src->nextword->word.word ||
		  (nwp->word.word!=NULL && src->nextword->word.word!=NULL &&
		   word_eq(nwp->word.word, src->nextword->word.word))){
			nwp->word.count++;
			return 0;
		}
		nwp = nwp->next;
	}

	add_node((*dst)->nextword);
	nwp = (*dst)->nextword;
	nwp->word.word = src->nextword->word.word;
	nwp->word.count = 1;
#endif

	return 0;

#ifdef NEXTWORDS
memerr:
	return 1;
#endif
}

int update_hashtable_value_ngram(ngram_t *ng, struct hashtable *htab){
	return update_hashtable_value(ng->tok, ng, htab, ngram_eq, ngram_update);
}

ngram_t* get_hashtable_value_ngram(ngram_t *ng, struct hashtable *htab){
	int rtype;
	val_list_t **p;

	p = find_hashtab_item(ng->tok, ng, htab, &rtype, ngram_eq);
	if(p && *p)
		return (*p)->value;

	return NULL;
}

void free_hashtable_data(struct hashtable *htab, void (*freedata)(void*)){
	val_list_t *ptr,*tmp;
	int i;
	for(i=0;i<htab->size;i++){
		if(htab->tab[i]){
			ptr = htab->tab[i]->vlist;
			while(ptr){
				tmp = ptr->next;
				freedata(ptr->value);
				free(ptr);
				ptr = tmp;
			}
			free(htab->tab[i]);
		}
		htab->tab[i]=NULL;
	}
	htab->size = 0;
	free(htab->tab);
}

int word_cmp(word_t *a, word_t *b){
	if(a==b)
		return 0;
	if(a==NULL)
		return -1;
	if(b==NULL)
		return 1;
	if(a->tok != b->tok)
		return a->tok - b->tok;
	if(a->len != b->len)
		return a->len - b->len;

	return strncmp(a->s,b->s,b->len);
}

int word_eq(word_t *a, word_t *b){
	if(a->tok != b->tok || a->len != b->len)
		return 0;

	return !strncmp(a->s,b->s,b->len); // is there a faster way?
}

int ngram_eq(void *a, void *b){
	ngram_t *na = (ngram_t*)a;
	ngram_t *nb = (ngram_t*)b;
	wordlist_t *ap = na->words;
	wordlist_t *bp = nb->words;

	if(na->tok != nb->tok)
		return 0;

	while(ap && bp){
		if(!word_eq(ap->word, bp->word))
			return 0;
		ap = ap->next;
		bp = bp->next;
	}
	return 1;
}
