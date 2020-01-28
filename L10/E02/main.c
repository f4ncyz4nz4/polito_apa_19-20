#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct{
    char nome[100];
    int tipo;
    int ing;
    int usc;
    int prec;
    int fin;
    float val;
    int diff;
}Elemento;

Elemento* ElementiInit(Elemento **sol,Elemento **best_sol,int *N,FILE *fp);
int disp_rip(Elemento *el,int N,int pos,int DD,int DP,Elemento *sol,Elemento *best_sol, float *best_punt,int diag,int d[],int best_d[],int fine);
int checkverso(Elemento *el,Elemento *sol,int pos,int ind);
int checkdiag(Elemento *sol,int pos,int diag);
int checkdiag2(Elemento el,int pos);
void assegna(Elemento *b,Elemento *a);
int pruning(Elemento *sol,Elemento a,int pos,int DD,int diag);
void assegnaTOT(Elemento *b,Elemento *a,int N);
float gencheck(Elemento *sol,int d[],int DP);
int main() {
    Elemento *elementi,*sol,*best_sol;
    FILE *fp;
    int N,i,DD=0,DP=0,d[3]={0},best_d[3]={0};
    float best_punt=0;
    fp=fopen("elementi.txt","r");
    elementi=ElementiInit(&sol,&best_sol,&N,fp);
    printf("Inserire la difficoltà massima di una diagonale:\n");
    scanf("%d",&DD);
    printf("Inserire la difficoltà massima di un programma:\n");
    scanf("%d",&DP);
    disp_rip(elementi,N,0,DD,DP,sol,best_sol,&best_punt,0,d,best_d,0);
    printf("PUNTEGGIO TOT MIGLIORE:\t%f\n",best_punt);
    printf("Diagonale 1---------------\n");
    for(i=0;i<best_d[0];i++){
        printf("%s   ",best_sol[i].nome);
    }
    printf("\n");
    printf("Diagonale 2---------------\n");
    for(i=5;i<best_d[1];i++){
        printf("%s   ",best_sol[i].nome);
    }
    printf("\n");
    printf("Diagonale 3---------------\n");
    for(i=10;i<best_d[2];i++){
        printf("%s   ",best_sol[i].nome);
    }
    free(elementi);
    free(sol);
    free(best_sol);
    return 0;
}
int disp_rip(Elemento *el,int N,int pos,int DD,int DP,Elemento *sol,Elemento *best_sol, float *best_punt,int diag,int d[],int best_d[],int fine){
    int i;
    float punti=0;
    if(fine){
        if((punti=gencheck(sol,d,DP))>(*best_punt)){
            assegnaTOT(best_sol,sol,pos);
            *best_punt=punti;
            best_d[0]=d[0];
            best_d[1]=d[1];
            best_d[2]=d[2];
        }
        return 0;
    }
    for (i = 0; i < N; i++) {
        if (checkverso(el, sol, pos, i) && pruning(sol, el[i], pos, DD,diag)) {
            assegna(&sol[pos], &el[i]);
            if (checkdiag(sol,pos,diag)) {
                disp_rip(el, N, pos + 1, DD, DP, sol, best_sol, best_punt, diag, d,best_d, 0);
            } else {
                if(checkdiag2(el[i],pos))
                    disp_rip(el, N, pos + 1, DD, DP, sol, best_sol, best_punt, diag, d,best_d, 0);
                if (diag==0) {
                    d[0] = pos + 1;
                    disp_rip(el, N, 5, DD, DP, sol, best_sol, best_punt, diag + 1, d, best_d, 0);
                }
                if(diag==1) {
                    d[1] = pos + 1;
                    disp_rip(el, N, 10, DD, DP, sol, best_sol, best_punt, diag + 1, d, best_d, 0);
                }
                if(diag==2){
                    d[2] = pos + 1;
                    disp_rip(el, N, 15, DD, DP, sol, best_sol, best_punt, diag+1 , d,best_d, 1);
                }
            }
        }
    }
    return 0;
}

float gencheck(Elemento *sol,int d[],int DP){
    int i;
    float punti=0,puntiU=0;
    int acrA=0,acrI=0,acrSeq=0,Dd=0,Dp=0;
    for(i=0;i<d[0];i++){
        if(i+1<d[0] && (sol[i].tipo==1 || sol[i].tipo==2) && (sol[i+1].tipo==1 || sol[i+1].tipo==2))
            acrSeq++;
        if(sol[i].tipo==1)
            acrI++;
        if(sol[i].tipo==2)
            acrA++;
        Dp+=sol[i].diff;
        punti+=sol[i].val;
    }
    for(i=5;i<d[1];i++){
        if(i+1<d[1] && (sol[i].tipo==1 || sol[i].tipo==2) && (sol[i+1].tipo==1 || sol[i+1].tipo==2))
            acrSeq++;
        if(sol[i].tipo==1)
            acrI++;
        if(sol[i].tipo==2)
            acrA++;
        Dp+=sol[i].diff;
        punti+=sol[i].val;
    }
    for(i=10;i<d[2];i++){
        if(i+1<d[2] && (sol[i].tipo==1 || sol[i].tipo==2) && (sol[i+1].tipo==1 || sol[i+1].tipo==2))
            acrSeq++;
        if(sol[i].tipo==1)
            acrI++;
        if(sol[i].tipo==2)
            acrA++;
        Dp+=sol[i].diff;
        puntiU+=sol[i].val;
    }
    if(Dp>DP)
        return 0;
    if(acrA && acrI && acrSeq) {
        if(sol[d[2]-1].fin==0 && sol[d[2]-1].diff>=8)
            puntiU=puntiU*1.5;
        punti=punti+puntiU;
        return punti;
    }
    return 0;
}
int pruning(Elemento *sol,Elemento a,int pos,int DD,int diag){
    int i,cnt=0,diff=0;
    if(diag==0){
        for(i = 0; i < pos; i++){
            diff+=sol[i].diff;
        }
    }
    if(diag==1){
        for(i = 5; i < pos; i++){
            diff+=sol[i].diff;
        }
    }
    if(diag==2){
        for(i = 10; i < pos; i++){
            diff+=sol[i].diff;
        }
    }
    if((diff+a.diff)>DD)
        return 0;
    if((pos+1)==5 || (pos+1)==10 || (pos+1)==15) {
        if(diag==0){
            for (i = 0; i < pos; i++) {
                if (sol[i].tipo != 0)
                    cnt++;
            }
        }
        if(diag==1){
            for (i = 5; i < pos; i++) {
                if (sol[i].tipo != 0)
                    cnt++;
            }
        }
        if(diag==2){
            for (i = 10; i < pos; i++) {
                if (sol[i].tipo != 0)
                    cnt++;
            }
        }
        if (cnt == 0 && a.tipo==0)
            return 0;
    }
    return 1;
}
void assegna(Elemento *b,Elemento *a){
    strcpy(b->nome,a->nome);
    b->tipo=a->tipo;
    b->ing=a->ing;
    b->usc=a->usc;
    b->prec=a->prec;
    b->fin=a->fin;
    b->val=a->val;
    b->diff=a->diff;
}
void assegnaTOT(Elemento *b,Elemento *a,int N){
    int i;
    for(i=0;i<N;i++){
        assegna(&b[i],&a[i]);
    }
}
int checkdiag2(Elemento el,int pos) {
    if (el.fin == 1)
        return 0;
    if (pos != 0) {
        if((pos+1)==5 || (pos+1)==10 || (pos+1)==15)
            return 0;
    }
    return 1;
}
int checkdiag(Elemento *sol,int pos,int diag){
    int i;
    if(diag==0){
        for(i=0;i<(pos+1);i++){
            if(sol[i].tipo==1 || sol[i].tipo==2)
                return 0;
        }
    }
    if(diag==1){
        for(i=5;i<(pos+1);i++){
            if(sol[i].tipo==1 || sol[i].tipo==2)
                return 0;
        }
    }
    if(diag==2){
        for(i=10;i<(pos+1);i++){
            if(sol[i].tipo==1 || sol[i].tipo==2)
                return 0;
        }
    }
    return 1;
}
int checkverso(Elemento *el,Elemento *sol,int pos,int ind){
    if(pos==0 || pos==5 || pos==10 || pos==15){
        if(el[ind].ing==1 && el[ind].prec==0)
            return 1;
    }
    if(pos>0) {
        if (el[ind].ing == sol[pos - 1].usc)
            return 1;
    }
    return 0;
}
Elemento* ElementiInit(Elemento **sol,Elemento **best_sol,int *N,FILE *fp){
    Elemento* el;
    int i;
    *sol=(Elemento*)malloc((15)* sizeof(Elemento));
    *best_sol=(Elemento*)malloc((15)* sizeof(Elemento));
    fscanf(fp,"%d%*c",N);
    el=(Elemento*)malloc((*N)* sizeof(Elemento));
    for(i=0;i<*N;i++) {
        fscanf(fp, "%s",el[i].nome);
        fscanf(fp,"%d %d %d %d %d %f %d%*c",&el[i].tipo,&el[i].ing,&el[i].usc,&el[i].prec,&el[i].fin,&el[i].val,&el[i].diff);
    }
    return el;
}
