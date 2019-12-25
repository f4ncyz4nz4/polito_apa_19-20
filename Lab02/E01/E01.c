#include <stdio.h>
#define MAX 50
typedef struct{
    int x;
    int y;
    int b;
    int h;
    int A;
}Quadrati;
void AnalizzaMatrice(int M[][MAX],int x, int y,int mr,int mc, Quadrati q[]);
int main() {
    FILE *fp;
    int i,j,righe,colonne,M[MAX][MAX];
    Quadrati q[3];
    /*Utilizzo una struct per semplificarmi poi l'output.
     * In particolare il primo per la maggior Base, il secondo
     * per la maggior Altezza ed infine il terzo per l'Area*/
    /*Gestione File*/
    fp=fopen("Mappa.txt","r");
    if(fp==NULL) {
        printf("Errore apertura file\n");
        return -1;
    }
    /*Copio matrice e chiudo file*/
    fscanf(fp,"%d %d",&righe,&colonne);
    for(i=0;i<righe;i++){
        for(j=0;j<colonne;j++){
            fscanf(fp,"%d",&M[i][j]);
        }
    }
    fclose(fp);
    for(i=0;i<3;i++){
        q[i].x=0;q[i].y=0;q[i].b=0;q[i].h=0;q[i].A=0;
    }
    /*Inizializzo tutto nella struct a 0*/
    for(i=0;i<righe;i++){
        for(j=0;j<colonne;j++){
            if(M[i][j]==1){
                /*Ogni volta che trovo un 1 passo alla funzione
                 * le coordinate, la matrice, e la struct*/
                AnalizzaMatrice(M,j,i,righe,colonne,q);
            }
        }
    }
    printf("Max Base: estr. sup. SX=<%d,%d> b=%d, h=%d, Area=%d\n",q[0].x,q[0].y,q[0].b,q[0].h,q[0].A);
    printf("Max Altezza: estr. sup. SX=<%d,%d> b=%d, h=%d, Area=%d\n",q[1].x,q[1].y,q[1].b,q[1].h,q[1].A);
    printf("Max Area: estr. sup. SX=<%d,%d> b=%d, h=%d, Area=%d\n",q[2].x,q[2].y,q[2].b,q[2].h,q[2].A);
    return 0;
}

void AnalizzaMatrice(int M[][MAX],int x, int y,int mr,int mc, Quadrati q[]){
    int i,j,A,h,b=0;

    j=x;
    i=y;
    while(M[i][j]==1 && i<mr){
        while(M[i][j]==1 && j<mc){
            M[i][j]=0;
            /* Una volta trovato il rettangolo ne trasformo tutti
             * i suoi membri in 0 di modo che non vengano analizzati
             * ulteriormente*/
            j++;
        }
        i++;
        b=j-x;
        j=x;
    }
    h=i-y;
    A=b*h;
    if(b>q[0].b){
        q[0].x=x+1;
        q[0].y=y+1;
        q[0].b=b;
        q[0].h=h;
        q[0].A=A;
    }
    if(h>q[1].h){
        q[1].x=x+1;
        q[1].y=y+1;
        q[1].b=b;
        q[1].h=h;
        q[1].A=A;
    }
    if(A>q[2].A){
        q[2].x=x+1;
        q[2].y=y+1;
        q[2].b=b;
        q[2].h=h;
        q[2].A=A;
    }
}
