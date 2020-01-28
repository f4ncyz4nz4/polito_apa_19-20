//
// Created by loren on 28/01/2020.
//

#ifndef PROVA280120_ST_H
#define PROVA280120_ST_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct symboltable *ST;

ST    STinit(int maxN);
void  STfree(ST st);
int   STsize(ST st);
void  STinsert(ST st, char *str, int i);
int   STsearch(ST st, char *str);
char *STsearchByIndex(ST st, int i);

#endif //PROVA280120_ST_H
