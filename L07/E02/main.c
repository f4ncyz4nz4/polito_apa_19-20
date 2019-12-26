#include <stdio.h>
#include <stdlib.h>
typedef struct {
    char tipo;
    int quantita;
    int val;
}Gemme;
int check(char *sol, char ins, int pos,int max_rip);
int disp_rip(int pos,int *dim, Gemme *gem, char *sol, char *best_sol,int *valore,int *best_val,int max_rip,int val_MAX);
void Inizializza(FILE *fp,Gemme **gemme,char **sol,char **best_sol,int *val_MAX,int *best_val,int *max_rip);
void Distruggi(Gemme **gemme,char **sol,char **best_sol,int *val,int *dim);
int ZaffiriVSSmeraldi(char *sol,int pos);
int main() {
    Gemme *gemme=NULL;
    int i,j,valore=0,best_val=0,max_rip,N,val_MAX,dim=0;
    char *sol=NULL,*best_sol=NULL;
    FILE *fp;
    fp=fopen("e2_test_set.txt","r");
    fscanf(fp,"%d%*c",&N);
    for(j=0;j<N;j++) {
        Inizializza(fp,&gemme,&sol,&best_sol,&val_MAX,&best_val,&max_rip);
        disp_rip(0,&dim, gemme, sol, best_sol, &valore, &best_val,max_rip,val_MAX);
            printf("\nVALORE = %d\n", best_val);
        for (i = 0; i < dim; i++) {
            printf("%c ", best_sol[i]);
        }
        Distruggi(&gemme,&sol,&best_sol,&valore,&dim);
    }
    fclose(fp);
    return 0;
}
int disp_rip(int pos,int *dim, Gemme *gem, char *sol, char *best_sol,int *valore,int *best_val,int max_rip,int val_MAX){
    int i,j,fine=0;
    if (*valore > *best_val) {
        if(ZaffiriVSSmeraldi(sol,pos)) {
            for (j = 0; j < pos; j++) {
                best_sol[j] = sol[j];
            }
            *best_val = *valore;
            *dim = pos;
        }
    }
    if (*valore >= val_MAX)
        return 1;
    for (i = 0; i < 4 && !fine; i++) {
        if(gem[i].quantita>0 && check(sol,gem[i].tipo,pos,max_rip)){
            sol[pos] = gem[i].tipo;
            (gem[i].quantita)--;
            *valore+=gem[i].val;
            if(disp_rip(pos + 1,dim, gem, sol, best_sol, valore, best_val,max_rip,val_MAX))
                fine=1;
            (gem[i].quantita)++;
            *valore-=gem[i].val;
        }
    }
    if(fine)
        return 1;
    return 0;
}
int check(char *sol, char ins, int pos,int max_rip){
    int i;
    if(pos>0){
        if (sol[pos-1]== 'z') {
            if (ins != 'z' && ins != 'r')
                return 0;
        }
        if (sol[pos-1] == 's') {
            if (ins != 's' && ins != 't')
                return 0;
        }
        if (sol[pos-1] == 'r') {
            if (ins != 's' && ins != 't')
                return 0;
        }
        if (sol[pos-1] == 't') {
            if (ins != 'z' && ins != 'r')
                return 0;
        }
        if(pos>max_rip){
            for(i=0;i<max_rip;i++){
                if(sol[pos-i]!=ins)
                    return 1;
            }
            return 0;
        }
    }
    return 1;
}
void Inizializza(FILE *fp,Gemme **gemme,char **sol,char **best_sol,int *val_MAX,int *best_val,int *max_rip){
    int dim;
    *gemme=(Gemme*)malloc(4*sizeof(Gemme));
    (*gemme)[0].tipo='z';(*gemme)[1].tipo='r';(*gemme)[2].tipo='t';(*gemme)[3].tipo='s';
    fscanf(fp,"%d %d %d %d%*c",&((*gemme)[0].quantita),&((*gemme)[1].quantita),&((*gemme)[2].quantita),&((*gemme)[3].quantita));
    fscanf(fp,"%d %d %d %d%*c",&((*gemme)[0].val),&((*gemme)[1].val),&((*gemme)[2].val),&((*gemme)[3].val));
    fscanf(fp,"%d%*c",max_rip);
    dim=(*gemme)[0].quantita+(*gemme)[1].quantita+(*gemme)[2].quantita+(*gemme)[3].quantita;
    *sol = malloc(dim * sizeof(char));
    *best_sol = malloc(dim * sizeof(char));
    *best_val=0;
    *val_MAX=((*gemme)[0].quantita * (*gemme)[0].val)+((*gemme)[1].quantita * (*gemme)[1].val)+((*gemme)[2].quantita * (*gemme)[2].val)+((*gemme)[3].quantita * (*gemme)[3].val);
}
int ZaffiriVSSmeraldi(char *sol,int pos){
    int i,s=0,z=0;
    for(i=0;i<pos;i++){
        if(sol[i]=='z')
            z++;
        else if (sol[i]=='s')
            s++;
    }
    if(z<=s)
        return 1;
    return 0;
}
void Distruggi(Gemme **gemme,char **sol,char **best_sol,int *val,int *dim){
    free(*sol);
    free(*best_sol);
    free(*gemme);
    *val=0;
    *dim=0;
}