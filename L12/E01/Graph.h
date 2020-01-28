//
// Created by loren on 14/01/2020.
//

#ifndef E01_GRAPH_H
#define E01_GRAPH_H

#include "ST.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct edge { int v; int w; int wt; } Edge;

typedef struct graph *Graph;

Graph GRAPHinit(int V);
void  GRAPHfree(Graph G);
Graph GRAPHload(FILE *fin);
void  GRAPHstore(Graph G, FILE *fin);
void  GRAPHinsertE(Graph G, int id1, int id2, int wt);
Edge ** GRAPHtoDAG(Graph G,int *l,int *N,Edge **edge);
int* DAGrts(Graph D);
Graph GRAPHcreateDAG(Graph G,Edge **archi,int N,int card,Edge *edge);
int   GRAPHdfs(Graph G, int id);
void GRAPHmaxP(Graph D);
void  GRAPHedges(Graph G, Edge *a);

#endif //E01_GRAPH_H
