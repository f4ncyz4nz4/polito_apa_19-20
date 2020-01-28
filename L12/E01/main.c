#include <stdio.h>
#include "Graph.h"

int main() {
    int fine=0,cmd,N,card;
    FILE *fp;
    char string[11];
    Graph G=NULL,DAG=NULL;
    Edge **EdgetoDAG,*edge=NULL;

    while(!fine) {
        printf("\nOperazioni\n");
        printf("===============\n");
        printf("0.Carica Grafo da file\n");
        printf("1.Individuazione degli archi minimi che renderebbero il grafo un DAG se rimossi\n");
        printf("2.Costruzione del DAG e distanza massima tra i nodi\n");
        printf("3.Fine\n");
        printf("Comando : ");
        if (scanf("%d", &cmd) <= 0) {
            printf("Solo interi!\n");
            return -1;
        }
        switch (cmd){
            case 0:
                printf("Inserire il nome del file\n");
                scanf("%s",string);
                fp=fopen(string,"r");
                G=GRAPHload(fp);
                break;
            case 1:
                GRAPHtoDAG(G,&card,&N,&edge);
                printf("%d insiemi di archi a cardinalità minima %d che rendono il grafo DAG\n",N,card);
                free(edge);
                break;
            case 2:
                EdgetoDAG=GRAPHtoDAG(G,&card,&N,&edge);
                DAG=GRAPHcreateDAG(G,EdgetoDAG,N,card,edge);
                free(edge);
                break;
            case 3:
                fine=1;
                break;
            default:printf("Comando inserito non valido\n");
        }
    }
    GRAPHfree(G);
    GRAPHfree(DAG);
    return 0;
}
