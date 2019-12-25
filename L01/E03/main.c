#include <stdio.h>
#include <string.h>
#include <math.h>
#define MAX 30
#define LETT 10
int EseguiMossa(int rig,int col,int M[][MAX]);

int main() {
    int i,j,stop=0,M[MAX][MAX],r,c;
    FILE* fp;

    fp=fopen("Rotazione.txt","r");
    if(fp==NULL){
        printf("Errore nell'apertura del file delle matrici");
        return -1;
    }
    fscanf(fp,"%d %d",&r,&c);
    for(i=0;i<r;i++){
        for(j=0;j<c;j++){
            fscanf(fp,"%d",&M[i][j]);
        }
    }
    while(stop==0){
        stop=EseguiMossa(r,c,M);
    }
    for(i=0;i<r;i++){
        for(j=0;j<c;j++){
            fprintf(stdout,"%d",M[i][j]);
            fprintf(stdout," ");
        }
        fprintf(stdout,"\n");
    }
    return 0;
}

int EseguiMossa(int rig,int col, int M[][MAX]){
    int i,j=0,h=0,limite,trovato,k,vett[(int)fmax(col,rig)],info[5]={0},ind,pos;
    char sel[LETT+1],dir[LETT+1];

    fprintf(stdout,"Comandi:\n");
    fscanf(stdin,"%s", sel);
    if(strstr(sel,"stop"))
        return 1;
    fscanf(stdin,"%d %s %d", &ind, dir,&pos);

    if(strstr(sel,"riga")) {
        info[1] = 1;
        j=ind-1;
        limite=col;
    }
    else {
        info[0] = 1;
        h=ind-1;
        limite=rig;
    }
    pos=pos%limite;
    if((strstr(dir,"sinistra")) ||(strstr(dir,"su"))) {
        pos=fabs((float)(limite-pos)); /*Casto solo per poter utilizzare fabs*/
    }
    for(i=0;i<limite;i++,j=j+info[0],h=h+info[1]){
        vett[i]=M[j][h];
    }
    for(;i>0;i--,j=j-info[0],h=h-info[1]);
    for (i = 0; i < limite; i++, j = j + info[0], h = h + info[1]) {
        trovato = 0;
        for (k = 0; k < limite && trovato == 0; k++) {
            if (i == ((k + pos) % limite)) {
                trovato = 1;
                M[j][h] = vett[k];
            }
        }
    }
    return 0;
}