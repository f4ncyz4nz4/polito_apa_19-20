#include <stdio.h>
#include <stdlib.h>
typedef struct att{
    int s;
    int f;
    int d;
}att_t;
void leggiFile(FILE *fp,att_t *v,int N);
void BubbleSort(att_t *att,int N);
int valida(att_t a1,att_t a2);
void DisplaySol(att_t *att, int *P, int i);
int prog_dinamca(att_t *attivita,int *D,int *P,int N,int *last);
int main() {
    FILE *fp;
    att_t *attivita;
    int N,*D,*P,last=0;
    fp=fopen("att.txt","r");
    if(fp==NULL)
        return -2;
    fscanf(fp,"%d",&N);
    attivita = (att_t *)malloc(N* sizeof(att_t));
    D=(int*)calloc(N, sizeof(int));
    P=(int*)malloc(N* sizeof(int));
    leggiFile(fp,attivita,N);
    fclose(fp);
    BubbleSort(attivita,N);
    prog_dinamca(attivita,D,P,N,&last);
    DisplaySol(attivita,P,last);
    free(attivita);
    free(D);
    free(P);
    return 0;
}
int prog_dinamca(att_t *attivita,int *D,int *P,int N,int *last){
    int i,j;
    for(i=0;i<N;i++){
        P[i]=-1;
    }
    for(i=0;i<N;i++){
        for(j=0;j<i;j++){
            if((D[i]<(D[i-1]+attivita[j].d)) && valida(attivita[i-1],attivita[j]) ) {
                D[i] = (D[i-1] + attivita[j].d);
                P[i]=j;
                *last=i;
            }
        }
    }
    return 0;
}
void BubbleSort(att_t *att,int N){
    int i,j;
    att_t tmp;
    for(i=0;i<N;i++){
        for(j=0;j<N-1;j++){
            if(att[j].f>att[j+1].f){
                tmp.s=att[j+1].s;tmp.f=att[j+1].f;tmp.d=att[j+1].d;
                att[j+1].s=att[j].s;att[j+1].f=att[j].f;att[j+1].d=att[j].d;
                att[j].s=tmp.s;att[j].f=tmp.f;att[j].d=tmp.d;
            }
        }
    }
}
int valida(att_t a1,att_t a2){
    if (a1.s>=a2.f)
        return 1;
    return 0;
}
void DisplaySol(att_t *att, int *P, int i){
    if(P[i]==-1){
        printf("(%d,%d)\t",att[i].s,att[i].f);
        return;
    }
    DisplaySol(att,P,P[i]);
    printf("(%d,%d)\t",att[i].s,att[i].f);
}
void leggiFile(FILE *fp,att_t *v,int N){
    int i;
    for(i=0;i<N;i++){
        fscanf(fp,"%d %d",&(v[i].s),&(v[i].f));
        v[i].d=v[i].f-v[i].s;
    }
}
