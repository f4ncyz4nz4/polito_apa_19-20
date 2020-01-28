//
// Created by loren on 08/01/2020.
//

#ifndef E01_LTITLES_H
#define E01_LTITLES_H

#include "titles.h"

typedef struct list *LTitle;

LTitle LTinit();
void LTfree(LTitle LT);
LTitle LTGet(LTitle LT,FILE *fin);
LTitle LTMod(FILE *fin,LTitle LT, char *string,int N);
LTitle LTInsOrd (LTitle LT,FILE *fin,char *s,int N);
int LTSearch(LTitle LT, char *k);
Title LTSearchGet(LTitle LT, char *k);
int LTempty(LTitle LT);

#endif //E01_LTITLES_H
