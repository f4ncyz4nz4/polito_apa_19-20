#include <stdio.h>
#include <stdlib.h>
typedef struct {
    char tipo;
    int quantita;
}Gemme;
int check(char *sol, char ins, int pos);
int disp_rip(int pos, Gemme *gem, char *sol, char *best_sol,int dim,int *best_dim);
void Inizializza(FILE *fp,Gemme **gemme,char **sol,char **best_sol,int *dim,int *best_dim);
void Distruggi(Gemme **gemme,char **sol,char **best_sol,int *best_dim);
int main() {
    Gemme *gemme=NULL;
    int i,j,dim,best_dim,N;
    char *sol=NULL,*best_sol=NULL;
    FILE *fp;
    fp=fopen("e1_easy_test_set.txt","r");
    fscanf(fp,"%d%*c",&N);
    for(j=0;j<N;j++) {
        Inizializza(fp,&gemme,&sol,&best_sol,&dim,&best_dim);
        if(disp_rip(0, gemme, sol, best_sol, dim, &best_dim))
            printf("\nLunghezza MASSIMA = %d\n", best_dim);
        else
            printf("\nLunghezza trovata = %d\n", best_dim);
        for (i = 0; i < best_dim; i++) {
            printf("%c ", best_sol[i]);
        }
        Distruggi(&gemme,&sol,&best_sol,&best_dim);
    }
    fclose(fp);
    return 0;
}
int disp_rip(int pos, Gemme *gem, char *sol, char *best_sol,int dim,int *best_dim) {
    int i,j;
    if (pos > *best_dim) {
        for(j=0;j<pos;j++){
            best_sol[j]=sol[j];
        }
        *best_dim=pos;
    }
    if (pos >= dim)
        return 1;
    for (i = 0; i < 4; i++) {
        if(gem[i].quantita>0 && check(sol,gem[i].tipo,pos)){
            sol[pos] = gem[i].tipo;
            (gem[i].quantita)--;
            if(disp_rip(pos + 1, gem, sol, best_sol, dim, best_dim))
                return 1;
            (gem[i].quantita)++;
        }
    }
    return 0;
}
int check(char *sol, char ins, int pos){
    if(pos>0){
        if (sol[pos-1]== 'z') {
            if (ins == 'z' || ins == 'r')
                return 1;
            return 0;
        }
        if (sol[pos-1] == 's') {
            if (ins == 's' || ins == 't')
                return 1;
            return 0;
        }
        if (sol[pos-1] == 'r') {
            if (ins == 's' || ins == 't')
                return 1;
            return 0;
        }
        if (sol[pos-1] == 't') {
            if (ins == 'z' || ins == 'r')
                return 1;
            return 0;
        }
    }
    return 1;
}
void Inizializza(FILE *fp,Gemme **gemme,char **sol,char **best_sol,int *dim,int *best_dim){
    *gemme=(Gemme*)malloc(4*sizeof(Gemme));
    (*gemme)[0].tipo='z';(*gemme)[1].tipo='r';(*gemme)[2].tipo='t';(*gemme)[3].tipo='s';
    fscanf(fp,"%d %d %d %d%*c",&((*gemme)[0].quantita),&((*gemme)[1].quantita),&((*gemme)[2].quantita),&((*gemme)[3].quantita));
    *dim=(*gemme)[0].quantita+(*gemme)[1].quantita+(*gemme)[2].quantita+(*gemme)[3].quantita;
    *sol = malloc((*dim) * sizeof(char));
    *best_sol = malloc((*dim) * sizeof(char));
    *best_dim=0;
}
void Distruggi(Gemme **gemme,char **sol,char **best_sol,int *best_dim){
    free(*sol);
    free(*best_sol);
    free(*gemme);
    *best_dim=0;
}