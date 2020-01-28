//
// Created by loren on 05/01/2020.
//

#ifndef E04_BELLO_STAB_H
#define E04_BELLO_STAB_H

typedef struct symboltable *ST;
typedef struct{
    char *nome;
    char *sottorete;
}elab;
ST    STinit(int maxN);
void  STfree(ST st);
int   STsize(ST st);
void  STinsert(ST st, char *e1,char *s1, int i);
int   STsearch(ST st, char *str);
char *STsearchByIndex(ST st, int i);

#endif //E04_BELLO_STAB_H
