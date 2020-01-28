//
// Created by loren on 14/01/2020.
//

#ifndef E01_ST_H
#define E01_ST_H

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

#endif //E01_ST_H
