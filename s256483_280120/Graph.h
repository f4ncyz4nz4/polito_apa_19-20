//
// Created by loren on 28/01/2020.
//

#ifndef PROVA280120_GRAPH_H
#define PROVA280120_GRAPH_H

#include "ST.h"

typedef struct edge { int v; int w; int wt; } Edge;

typedef struct graph *Graph;

Graph GRAPHinit(int V);
void  GRAPHfree(Graph G);
Graph GRAPHload(FILE *fin);
void  GRAPHinsertE(Graph G, int id1, int id2, int wt);
int   GRAPHgetIndex(Graph G, char *label);
void  GRAPHstore(Graph G, FILE *fout);
void  GRAPHedges(Graph G, Edge *a);
int GRAPHcc(Graph G);

void GRAPHkcore(Graph G,int k);
void GRAPHconneted(int j,Graph G);
int GRAPHconnR(Graph G, int j,int N, Edge *edge,int *sol,int start,int pos);

#endif //PROVA280120_GRAPH_H
