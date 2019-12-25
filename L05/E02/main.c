#include <stdio.h>
#include <stdlib.h>
int **malloc2dR(int nr,int nc,FILE* fp);
void ***malloc2dP(int nr,int nc,FILE* fp,int ***m);
void separa(int **mat, int nr, int nc, int **b, int **n, int size[]);
void StampaeLibera(int *b, int *n,int size[]);
int main() {
    int size[2],nr, nc, **mat, *bianchi=NULL, *neri=NULL;
    FILE* fp;
    fp=fopen("mat.txt","r");
    if(fp==NULL)
        return -1;
    fscanf(fp,"%d%d",&nr,&nc);
    mat=malloc2dR(nr,nc,fp);
    fclose(fp);
    separa(mat,nr,nc,&bianchi,&neri,size);
    StampaeLibera(bianchi,neri,size);
    return 0;
}
int** malloc2dR(int nr,int nc,FILE* fp){
    int **m,i,j;
    m=(int**)malloc(nr*sizeof(int*));
    for(i=0;i<nr;i++)
        m[i]=(int*)malloc(nc* sizeof(int));
    for(i=0;i<nr;i++){
        for(j=0;j<nc;j++)
            fscanf(fp,"%d",&m[i][j]);
    }
    return m;
}
void*** malloc2dP(int nr,int nc,FILE* fp,int ***m){
    int i,j;
    *m=(int**)malloc(nr*sizeof(int*));
    for(i=0;i<nr;i++)
        (*m)[i]=(int*)malloc(nc* sizeof(int));
    for(i=0;i<nr;i++){
        for(j=0;j<nc;j++)
            fscanf(fp,"%d",&(*m)[i][j]);
    }
}
void separa(int **mat, int nr, int nc, int **b, int **n,int size[]){
    int i,j,bianco=1,Nb=1,Nn=1,kb=0,kn=0;
    *b=(int*)malloc(sizeof(int));
    *n=(int*)malloc(sizeof(int));
    for(i=0;i<nr;i++){
        for(j=0;j<nc;j++){
            if(bianco){
                if(kb==Nb){
                    Nb=Nb*2;
                    *b=(int*)realloc(*b,Nb* sizeof(int));
                }
                (*b)[kb++]=mat[i][j];
            }
            if(!bianco){
                if(kn==Nn){
                    Nn=Nn*2;
                    *n=(int*)realloc(*n,Nn* sizeof(int));
                }
                (*n)[kn++]=mat[i][j];
            }
            if(bianco)
                bianco=0;
            else
                bianco=1;
        }
    }
    //Valori utili per la funzione StampaeLibera()
    size[0]=kb;size[1]=kn;
}
void StampaeLibera(int *b, int *n, int size[]){
    int i=0;
    printf("Bianchi:\n");
    for(i=0;i<size[0];i++)
        printf("%d ",b[i]);
    printf("\n");
    printf("Neri:\n");
    for(i=0;i<size[1];i++)
        printf("%d ",n[i]);
    printf("\n");
    free(b);
    free(n);
}