#include <stdio.h>
#include <stdlib.h>
typedef struct{
    int u;
    int v;
}Archi;
int comb_semp(Archi* archi,int *sol,int pos,int N,int n,int E,int start,int count);
int vert_cover(Archi* archi,int *sol,int E,int n);
int main() {
    Archi *archi;
    int i,count=0,N,E,*sol;
    FILE *fp;
    fp=fopen("Grafo.txt","r");
    if(fp==NULL)
        return -1;
    fscanf(fp,"%d%d",&N,&E);
    archi=(Archi*)malloc(E* sizeof(Archi));
    sol=(int*)malloc(N* sizeof(int));
    for(i=0;i<N;i++)
        sol[i] = -1;
    for(i=0;i<E;i++)
        fscanf(fp,"%d%d",&(archi[i].u),&(archi[i].v));
    fclose(fp);
    for(i=1;i<=N;i++) {
        count=comb_semp(archi,sol, 0, N, i, E, 0, count);
    }
    free(sol);
    free(archi);
    printf("----->%d",count);
    return 0;
}
int comb_semp(Archi* archi,int*sol,int pos,int N,int n,int E,int start,int count){
    int i;
    if(vert_cover(archi,sol,E,n))
        if(pos>=n){
            for(i=0;i<n;i++)
                fprintf(stdout,"%d ",sol[i]);
            fprintf(stdout,"\n");
            return count+1;
        }
    for(i=start;i<N;i++){
        sol[pos]=i;
        count=comb_semp(archi,sol,pos+1,N,n,E,i+1,count);
    }
    return count;
}
int vert_cover(Archi* archi,int *sol,int E,int n){
    int i,j,*occ=NULL;
    occ=(int*)calloc(E, sizeof(int));
    //La soluzione è accettata se almeno uno dei nodi
    // per ogni arco appartiene al sottoinsieme W (soluzione)
    for(j=0;j<E;j++){
        for(i=0;i<n;i++){
            if((archi[j].u==sol[i]) || (archi[j].v==sol[i])){
                occ[j]=1;
            }
        }
    }
    for(i=0;i<E;i++) {
        if (occ[i]==0)
            return 0;
    }
    return 1;
}