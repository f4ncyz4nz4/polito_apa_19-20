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

Elemento* ElementiInit(Elemento **sol,int **mark,int *N,FILE *fp);
float disp_rip(Elemento *el,int *mark,int N,int pos,int DD,int DP,Elemento *sol,int diag,int d[]);
int checkdiag(Elemento el,int pos,int diag,int DP,int Dp);
void assegna(Elemento *b,Elemento *a);
int pruning(Elemento *sol,Elemento a,int pos,int DD,int DP,int diag);
void OrdinaRatio(Elemento *el,int N);
float calcPunti(Elemento *sol,int diag,int d[]);
int check(Elemento *el,Elemento *sol,int ind,int pos);

int main() {
    Elemento *elementi,*sol;
    FILE *fp;
    int N,i,DD,DP,d[3]={0},*mark;
    float punt=0;
    fp=fopen("elementi.txt","r");
    elementi=ElementiInit(&sol,&mark,&N,fp);
    printf("Inserire la difficoltà massima di una diagonale:\n");
    scanf("%d",&DD);
    printf("Inserire la difficoltà massima di un programma:\n");
    scanf("%d",&DP);
    OrdinaRatio(elementi,N);
    /*for(i=0;i<N;i++)
        printf("%s\n",elementi[i].nome);*/
    punt=disp_rip(elementi,mark,N,0,DD,DP,sol,0,d);
    printf("PUNTEGGIO TOT MIGLIORE:\t%f\n",punt);
    printf("Diagonale 1---------------\n");
    for(i=0;i<d[0];i++){
        printf("%s   ",sol[i].nome);
    }
    printf("\n");
    printf("Diagonale 2---------------\n");
    for(i=5;i<d[1];i++){
        printf("%s   ",sol[i].nome);
    }
    printf("\n");
    printf("Diagonale 3---------------\n");
    for(i=10;i<d[2];i++){
        printf("%s   ",sol[i].nome);
    }
    free(elementi);
    free(sol);
    return 0;
}
float disp_rip(Elemento *el,int *mark,int N,int pos,int DD,int DP,Elemento *sol,int diag,int d[]){
    int i,j,fine=0,trovato=0,Dp=0,Dd=0;
    float punti=0;
    while (!fine){
        for(i=0;i<N && !trovato;i++) {
            if (check(el,sol,i,pos) && pruning(sol,el[i],pos,DD,DP,diag) && mark[i]==0) {
                trovato = 1;
                mark[i]=1;
                assegna(&(sol[pos++]), &(el[i]));
                Dd += el[i].diff;
                Dp += el[i].diff;
            }
        }
        if(checkdiag(el[i],pos,diag,DP,Dp) || i==N){
            if(diag==0) {
                d[0] = pos;
                punti+=calcPunti(sol,0,d);
                pos=5;
            }
            else if(diag==1) {
                d[1] = pos;
                punti+=calcPunti(sol,1,d);
                pos=10;
            }
            else if (diag==2) {
                d[2] = pos;
                punti+=calcPunti(sol,2,d);
                fine=1;
            }
            diag++;
            Dp=0;
            Dd=0;
            for(j=0;j<N;j++)
                mark[j]=0;
        }
        trovato=0;
    }
    return punti;
}
int checkdiag(Elemento el,int pos,int diag,int DP,int Dp) {
    if (el.fin == 1)
        return 1;
    if (pos != 0) {
        if((pos)==5 || (pos)==10)
            return 1;
    }
    if(diag==0){
        if((float)Dp>=((float)(DP*0.32)))
            return 1;
    }
    if(diag==1){
        if((float)Dp>=((float)(DP*0.34)))
            return 1;
    }
    if(diag==2){
        if((float)Dp>=((float)(DP*0.34)))
            return 1;
    }
    return 0;
}
int pruning(Elemento *sol,Elemento a,int pos,int DD,int DP,int diag){
    int i,diff=0;
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
    if(diag==0){
        if((float)(diff+a.diff)>((float)(DP*0.32)))
            return 0;
        if(DP*0.32>=10)
            if(a.tipo!=0 && a.usc!=0)
                return 0;
    }
    if(diag==1){
        if((float)(diff+a.diff)>((float)(DP*0.34)))
            return 0;
        if(DP*0.34>=10)
            if(a.tipo!=0 && a.usc!=0)
                return 0;
    }
    if(diag==2){
        if((float)(diff+a.diff)>((float)(DP*0.34)))
            return 0;
        if(pos==10)
            if(a.tipo!=0 && a.usc!=0)
                return 0;
    }
    return 1;
}
int check(Elemento *el,Elemento *sol,int ind,int pos){
    if(pos==0 || pos==5 || pos==10){
        if(el[ind].ing==1 && el[ind].prec==0)
            return 1;
    }
    if(pos>0) {
        if (el[ind].ing == sol[pos - 1].usc)
            return 1;
    }
    return 0;
}
float calcPunti(Elemento *sol,int diag,int d[]){
    int i,flag=0;
    float p=0;
    if(diag==0){
        for(i = 0; i < d[0]; i++){
            p+=sol[i].val;
        }
    }
    if(diag==1){
        for(i = 5; i < d[1]; i++){
            p+=sol[i].val;
        }
    }
    if(diag==2){
        for(i = 10; i < d[2]; i++){
            p+=sol[i].val;
            if(sol[i].fin==1 && sol[i].diff>=8)
                flag=1;
        }
        if(flag)
            p=(float)(p*1.5);
    }
    return p;
}
void OrdinaRatio(Elemento *el,int N){
    int i,j;
    Elemento tmp;
    for(i=0;i<N;i++){
        for(j=0;j+1<N-i;j++){
            if((el[j].val/(float)el[j].diff)<(el[j+1].val/(float) el[j+1].diff)){
                tmp=el[j+1];
                el[j+1]=el[j];
                el[j]=tmp;
            }
        }
    }
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
Elemento* ElementiInit(Elemento **sol,int **mark,int *N,FILE *fp){
    Elemento* el;
    int i;
    *sol=(Elemento*)malloc((15)* sizeof(Elemento));
    fscanf(fp,"%d%*c",N);
    el=(Elemento*)malloc((*N)* sizeof(Elemento));
    *mark=(int*)calloc((*N) , sizeof(int));
    for(i=0;i<*N;i++) {
        fscanf(fp, "%s",el[i].nome);
        fscanf(fp,"%d %d %d %d %d %f %d%*c",&el[i].tipo,&el[i].ing,&el[i].usc,&el[i].prec,&el[i].fin,&el[i].val,&el[i].diff);
    }
    return el;
}
