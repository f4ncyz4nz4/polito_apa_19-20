#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char tipo;
    int quantita;
}Gemme;
int fZ(int ****mat,int z,int r,int t,int s,int pos);
int fR(int ****mat,int z,int r,int t,int s,int pos);
int fT(int ****mat,int z,int r,int t,int s,int pos);
int fS(int ****mat,int z,int r,int t,int s,int pos);
int**** Mat4Dim(int z,int r,int t,int s);
int Inizializza(FILE *fp,Gemme **gemme);
int Memoization(Gemme *gemme,int ****mat);
int main() {
    Gemme *gemme=NULL;
    int ****mat;
    int i,N,dim;
    FILE *fp;
    fp=fopen("hard_test_set.txt","r");
    fscanf(fp,"%d%*c",&N);
    for(i=0;i<N;i++) {
        dim=Inizializza(fp,&gemme);
        mat=Mat4Dim(gemme[0].quantita+1,gemme[1].quantita+1,gemme[2].quantita+1,gemme[3].quantita+1);
        printf("\nLunghezza massima:\t%d\n",dim);
        dim=Memoization(gemme,mat);
        printf("Collana di lunghezza massima possibile:\t%d\n",dim);
    }
    return 0;
}
int Memoization(Gemme *gemme,int ****mat){
    int max,i;
    int l[4];
    l[0]=fZ(mat,gemme[0].quantita-1,gemme[1].quantita,gemme[2].quantita,gemme[3].quantita,1);
    l[1]=fR(mat,gemme[0].quantita,gemme[1].quantita-1,gemme[2].quantita,gemme[3].quantita,1);
    l[2]=fT(mat,gemme[0].quantita,gemme[1].quantita,gemme[2].quantita-1,gemme[3].quantita,1);
    l[3]=fS(mat,gemme[0].quantita,gemme[1].quantita,gemme[2].quantita,gemme[3].quantita-1,1);
    max=l[0];
    for(i=0;i<4;i++){
        if(max<l[i])
            max=l[i];
    }
    return max;
}
int fZ(int ****mat,int z,int r,int t,int s,int pos){
    int l1=0,l2=0;
    if(z<1 && r<1)
        return pos;
    if (mat[z][r][t][s] != 0)
        return mat[z][r][t][s];
    if(r>0) {
        l1 = fR(mat, z, r - 1, t, s,pos+1);
    }
    if(z>0) {
        l2 = fZ(mat, z - 1, r, t, s,pos+1);
    }
    if(l1>l2){
        mat[z][r][t][s]=l1;
        return l1;
    } else {
        mat[z][r][t][s]=l2;
        return l2;
    }
}
int fR(int ****mat,int z,int r,int t,int s,int pos){
    int l1=0,l2=0;
    if(s<1 && t<1)
        return pos;
    if (mat[z][r][t][s] != 0)
        return mat[z][r][t][s];
    if(t>0){
        l1 = fT(mat, z, r , t-1, s,pos+1);
    }
    if(s>0) {
        l2 = fS(mat, z , r, t, s-1,pos+1);
    }
    if(l1>l2){
        mat[z][r][t][s]=l1;
        return l1;
    } else {
        mat[z][r][t][s]=l2;
        return l2;
    }
}
int fT(int ****mat,int z,int r,int t,int s,int pos) {
    int l1=0,l2=0;
    if(z<1 && r<1)
        return pos;
    if (mat[z][r][t][s] != 0)
        return mat[z][r][t][s];
    if(r>0) {
        l1 = fR(mat, z, r - 1, t, s,pos+1);
    }
    if(z>0) {
        l2 = fZ(mat, z - 1, r, t, s,pos+1);
    }
    if(l1>l2){
        mat[z][r][t][s]=l1;
        return l1;
    } else {
        mat[z][r][t][s]=l2;
        return l2;
    }
}
int fS(int ****mat,int z,int r,int t,int s,int pos){
    int l1=0,l2=0;
    if(s<1 && t<1)
        return pos;
    if (mat[z][r][t][s] != 0)
        return mat[z][r][t][s];
    if(t>0){
        l1 = fT(mat, z, r , t-1, s,pos+1);
    }
    if(s>0) {
        l2 = fS(mat, z , r, t, s-1,pos+1);
    }
    if(l1>l2){
        mat[z][r][t][s]=l1;
        return l1;
    } else {
        mat[z][r][t][s]=l2;
        return l2;
    }
}
int**** Mat4Dim(int z,int r,int t,int s){
    int i,j,k;
    int ****mat;
    mat=(int****)malloc(z*sizeof(int***));
    for(i=0;i<z;i++){
        mat[i]=(int***)malloc(r*sizeof(int**));
        for(j=0;j<r;j++){
            mat[i][j]=(int**)malloc(t*sizeof(int*));
            for(k=0;k<t;k++){
                mat[i][j][k]=(int*)calloc(s,sizeof(int));
            }
        }
    }
    return mat;
}
int Inizializza(FILE *fp,Gemme **gemme){
    int dim;
    *gemme=(Gemme*)malloc(4*sizeof(Gemme));
    (*gemme)[0].tipo='z';(*gemme)[1].tipo='r';(*gemme)[2].tipo='t';(*gemme)[3].tipo='s';
    fscanf(fp,"%d %d %d %d%*c",&((*gemme)[0].quantita),&((*gemme)[1].quantita),&((*gemme)[2].quantita),&((*gemme)[3].quantita));
    dim=(*gemme)[0].quantita+(*gemme)[1].quantita+(*gemme)[2].quantita+(*gemme)[3].quantita;
    return dim;
}
