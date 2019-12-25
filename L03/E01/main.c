#include <stdio.h>
#include <stdlib.h>
#include <windef.h>
#define MAX 50
void leggiMatrice(int M[][MAX],int* r,int*c);
int riconosciRegione(int M[][MAX],int nr,int nc,int r,int c,int *b,int *h);
int main() {
    int i,j,righe,colonne,M[MAX][MAX],base=0,altezza;
    leggiMatrice(M,&righe,&colonne);
    for(i=0;i<righe;i++){
        for(j=0;j<colonne;j++){
            if (riconosciRegione(M,righe,colonne,i,j,&base,&altezza)){
                printf("Rettangolo con estremo in (%d,%d), base=%d e altezza=%d\n",j,i,base,altezza);
                /*Nel "printf" j e i sono invertiti per rispettare la conversione cartesiana*/
            }
        }
    }
    return 0;
}
void leggiMatrice(int M[][MAX],int* r,int*c){
    int i=0,j=0;
    FILE *fp;
    char car;
    fp=fopen("Mappe.txt","r");
    if(fp==NULL) {
        printf("Errore apertura file\n");
        exit(-1);
    }
    while((fscanf(fp,"%d%c",&M[i][j],&car)!=EOF) && i<MAX && j<MAX){
        if(car==' ')
            j++;
        if(car=='\n'){
            i++;
            *c=j+1;
            j=0;
        }
    }
    *r=i+1;
    /*Sommo 1 ad r e c perchè gli indici i e j partono da 0*/
    fclose(fp);
}
int riconosciRegione(int M[][MAX],int nr,int nc,int r,int c,int *b,int *h){
    int x,y;
    if(M[r][c]==1){
        *b=0;*h=0;
        x=c;y=r;
        /*Memorizzo l'origine di partenza (x,y) perchè lo utilizzerò
         * dopo per trovare base ed altezza*/
        while(r<nr && r>=0 && (M[r][c]==1)) {
            while (c < nc && c >= 0 && (M[r][c] == 1)) {
                M[r][c] = 0;
                c++;
            }
            r++;
            (*b)=c-x;
            c=x;
        }
        (*h)=r-y;
        return TRUE;
    } else
        return FALSE;
}