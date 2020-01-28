//
// Created by loren on 05/01/2020.
//

#ifndef E04_BELLO_GRAFONP_H
#define E04_BELLO_GRAFONP_H

#include "STab.h"

typedef struct edge { int v; int w; int wt; } Edge;

typedef struct graph *Graph;

Graph GRAPHinit(int V);
void  GRAPHfree(Graph G);
Graph GRAPHload(FILE *);
Graph GRAPHcreateLIST(Graph G);
int GRAPHcomplSgMAT(Graph G, char *str1, char *str2, char *str3);
int GRAPHcomplSgLIST(Graph G, char *str1, char *str2, char *str3);
void  GRAPHinsertE(Graph G, int id1, int id2, int wt);
void  GRAPHstore(Graph G, FILE *fout);

#endif //E04_BELLO_GRAFONP_H
