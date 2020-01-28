#include <stdio.h>
#include <stdlib.h>
#include "GrafoNP.h"
#define MAXC 11

int main(void) {
    int i, cont, sel,List=0;
    char name[MAXC], label1[MAXC], label2[MAXC], label3[MAXC];
    Graph G=NULL;
    FILE *fin, *fout;

    cont = 1;
    while(cont) {
        printf("\nOperazioni su un grafo pesato non orientato\n");
        printf("===============\n");
        printf("1.Carica grafo da file\n");
        printf("2.Stampa il grafico\n");
        printf("3.Generare la Lista di adiacenza\n");
        printf("4.Verifica sottografo completo\n");
        printf("5.Fine\n");
        printf("Comando : ");
        if(scanf("%d",&i)<=0) {
            printf("Solo interi!\n");
            exit(0);
        }
        else {
            switch(i) {
                case 1:
                    printf("Nome file:");
                    scanf("%s", name);
                    fin = fopen(name, "r");
                    if (fin == NULL)
                        exit(-1);
                    G = GRAPHload(fin);
                    fclose(fin);
                    break;
                case 2:
                    printf("File (0) o schermo (1)?\n");
                    scanf("%d", &sel);
                    if (sel==0) {
                        printf("Nome file:");
                        scanf("%s", name);
                        fout = fopen(name, "w");
                        if (fout == NULL)
                            exit(-1);
                        GRAPHstore(G, fout);
                        fclose(fout);
                    }
                    else
                        GRAPHstore(G,stdout);
                    break;
                case 3:
                    if(!List) {
                        G = GRAPHcreateLIST(G);
                        List=1;
                    }
                    break;
                case 4:
                    printf("Utilizzare Matrice di adiacenza (0) o Lista di adiacenza(1)?\n");
                    scanf("%d", &sel);
                    printf("Inserire i nomi dei vertici\n");
                    scanf("%s %s %s",label1,label2,label3);
                    if (sel==0) {
                        if(GRAPHcomplSgMAT(G,label1,label2,label3))
                            printf("Sottografo COMPLETO\n");
                        else
                            printf("Sottografo NON COMPLETO\n");
                    }
                    else {
                        if (GRAPHcomplSgLIST(G, label1, label2, label3))
                            printf("Sottografo COMPLETO\n");
                        else
                            printf("Sottografo NON COMPLETO\n");
                    }
                    break;
                case 5:
                    cont = 0;
                    break;
                default:    printf("Opzione non valida\n");
            }
        }
    }
    GRAPHfree(G);
    return 0;
}
