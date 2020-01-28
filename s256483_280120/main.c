#include <stdio.h>
#include "Graph.h"

int main() {
    FILE *fin;
    int k,j=2;
    Graph G;
    fin=fopen("Prova.txt","r");
    G=GRAPHload(fin);
    fclose(fin);
    printf("Inserire k\n");
    scanf("%d",&k);
    GRAPHkcore(G,k);
    printf("Inserire j\n");
    scanf("%d",&j);
    GRAPHconneted(j,G);
    return 0;
}
