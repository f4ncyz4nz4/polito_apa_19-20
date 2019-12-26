#include <stdio.h>
#include <stdlib.h>
typedef struct att{
    int s;
    int f;
}att_t;

void attSel(int N,att_t *v);
void leggiFile(FILE *fp,att_t *v,int N);
int powerset(int pos, att_t *v, int *sol,int *best_sol,int N,int *tempo_b);
int valida(int *sol,att_t *v,att_t curr,int pos);
int calcolaTempo(int *sol,att_t *v,int N);

int main() {
    FILE *fp;
    att_t *v=NULL;
    int N;

    fp=fopen("att.txt","r");
    if(fp==NULL)
        return -1;
    fscanf(fp,"%d",&N);
    v = (att_t *)malloc(N* sizeof(att_t));
    leggiFile(fp,v,N);
    attSel(N,v);
    fclose(fp);
    free(v);
    return 0;
}
void attSel(int N,att_t *v){
    int *sol=NULL,tempo_migliore,tempo_b=-1,*best_sol=NULL,i;

    sol=(int *)malloc(N*sizeof(int));
    best_sol=(int *)malloc(N*sizeof(int));

    tempo_migliore = powerset(0,v,sol,best_sol,N,&tempo_b);
    printf("Sottoinsieme di attività: (");
    for(i=0;i<N;i++)if(best_sol[i]==1)printf("(%d %d)",v[i].s,v[i].f);printf(")");
    printf("\nDurata: %d",tempo_migliore);

    free(sol);
    free(best_sol);
}
int powerset(int pos, att_t *v, int *sol,int *best_sol,int N,int *tempo_b) {
    int tempo, i;
    if (pos >= N) {
        tempo = calcolaTempo(sol, v, N);
        if (tempo > *tempo_b) {
            *tempo_b = tempo;/*tempo_b deve essere nota a tutti gli stack!*/
            for (i = 0; i < N; i++) {/*Salvo il sottoinsieme di attività*/
                best_sol[i] = sol[i];
            }
        }
        return *tempo_b;
    }
    sol[pos] = 0;
    *tempo_b = powerset(pos + 1, v, sol, best_sol, N, tempo_b);
    if (valida(sol, v, v[pos], pos)) {/*Prendo quell'elemento solo se non si va a sovrapporre: è una forma di pruning*/
        sol[pos] = 1;
        *tempo_b = powerset(pos + 1, v, sol, best_sol, N, tempo_b);
    }
    return *tempo_b;
}
int calcolaTempo(int *sol,att_t *v,int N){
    int i,tempo=0;
    for(i=0;i<N;i++){
        if(sol[i]==1)
            tempo+=(v[i].f-v[i].s);
    }
    return tempo;
}
int valida(int *sol,att_t *v,att_t curr,int pos){
    int i;
    for(i=0;i<pos;i++){
        if(sol[i]==1) {
            if ((curr.s<v[i].f)&&(v[i].s<curr.f)) return 0;
        }
    }
    return 1;
}
void leggiFile(FILE *fp,att_t *v,int N){
    int i;
    for(i=0;i<N;i++){
        fscanf(fp,"%d %d",&(v[i].s),&(v[i].f));
    }
}
