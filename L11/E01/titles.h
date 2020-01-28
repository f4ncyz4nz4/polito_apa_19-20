//
// Created by loren on 08/01/2020.
//

#ifndef E01_TITLES_H
#define E01_TITLES_H

#include "data.h"
#include "BST.h"

typedef struct titolo *Title;

Title Tload(FILE *fin,char *string,int N);
void Tfree(Title t);
Title Tmod(FILE *fin,Title t,int N);
void Tprint(FILE *fout, Title t);
void TsearchQ(FILE *fout, Title t);
void TsearchMaxMin(FILE *fout, Title t);
void TsearchB(Title t,int s);
char* GetName(Title t);

#endif //E01_TITLES_H
