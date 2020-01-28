//
// Created by loren on 05/01/2020.
//
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "STab.h"

struct symboltable {elab *a; int maxN; int N;};

ST STinit(int maxN) {
    ST st;
    st = malloc(sizeof (*st));
    if (st == NULL) {
        printf("Errore nell'allocazione di memoria\n");
        return NULL;
    }
    st->a=NULL;
    st->a = calloc(maxN, sizeof(elab));

    if (st->a == NULL) {
        printf("Errore nell'allocazione di memoria\n");
        free(st);
        return NULL;
    }
    st->maxN = maxN;
    st->N = 0;
    return st;
}

void STfree(ST st) {
    int i;
    if (st==NULL)
        return;
    for (i=0; i<st->N; i++)
        if ((st->a[i].nome) != NULL)
            free(st->a[i].nome);
    if ((st->a[i].sottorete) != NULL)
        free(st->a[i].sottorete);
    free(st->a);
    free(st);
}

int STsize(ST st) {
    return st->N;
}
void  STinsert(ST st, char *e1,char *s1, int i){
    if (i >= st->maxN) {
        st->a = realloc(st->a, (2*st->maxN)*sizeof(elab));
        if (st->a == NULL)
            return ;
        st->maxN = 2*st->maxN;
    }
    st->a[i].nome = strdup(e1);
    st->a[i].sottorete = strdup(s1);
    st->N++;
}

int   STsearch(ST st, char *str){
    int i;
    for (i = 0; i  < st->N; i++)
        if (st->a[i].nome!=NULL && strcmp(str, st->a[i].nome)==0)
            return i;
    return -1;
}

char *STsearchByIndex(ST st, int i){
    if (i < 0 || i >= st->N)
        return NULL;
    return (st->a[i].nome);
}