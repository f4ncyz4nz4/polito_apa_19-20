#include <stdio.h>
#define MAX 20

void AnalisiGiornata(int M[][MAX],int pos[],int righe,int colonne);

int main() {
    FILE *fp;
    int i=0,n=0,m=0,cnt=0,posizioni[MAX]={0},T[MAX][MAX];
    char carattere;

    /*Gestione File*/
    fp=fopen("Campionato.txt","r");
    if(fp==NULL) {
        printf("Errore apertura file\n");
        return -1;
    }
    /*Copio matrice*/
    while((fscanf(fp, "%d%c", &T[n][cnt],&carattere))!=EOF){
        if(carattere==' ')
            cnt++;
        else if(carattere=='\n'){
            m=cnt;
            cnt=0;
            n++;
        }
    }
    m++;
    n++;
    fclose(fp);

    /*Analizzo ogni giornata*/
    AnalisiGiornata(T,posizioni,n,m);
    for(i=0;i<m;i++)
        printf("%d\n",posizioni[i]);
    return 0;
}
void AnalisiGiornata(int M[][MAX],int pos[],int righe,int colonne){
    int i,j,k,flag=0,punti[MAX]={0};

    for(j=0;j < colonne;j++) {
        pos[j]=1;
        for (i = 0; i < righe; i++) {
            punti[i] = punti[i] + M[i][j];
            for (k = i - 1; k >=0; k--) {
                if (punti[i] <= punti[k]) {
                    flag=1;
                }
            }
            if (!flag && i!=0) {
                pos[j] = i + 1;
            }
            flag=0;
        }
    }
}