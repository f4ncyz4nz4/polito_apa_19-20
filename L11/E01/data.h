//
// Created by loren on 09/01/2020.
//

#ifndef E01_DATA_H
#define E01_DATA_H

#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    int aa;
    int mm;
    int gg;
    int h;
    int min;
}Data;

Data dataload(FILE *fin);
void datafree(Data d);
int DataCmp(Data a,Data b);
Data Datascan(FILE *fin);
void Dataprint(FILE *fout,Data a);
Data DataNULL();
Data DataMax();
Data DataMin();

#endif //E01_DATA_H
