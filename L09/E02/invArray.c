//
// Created by loren on 22/12/2019.
//

#include "invArray.h"
struct invArray_s{
    inv_t *vettInv;
    int nInv;
    int maxInv;
};

/* creatore e disruttore */
invArray_t invArray_init(){
    invArray_t invArray;
    invArray=(invArray_t)malloc(sizeof(struct invArray_s));
    invArray->vettInv=NULL;
    invArray->maxInv=0;
    invArray->nInv=0;
    return invArray;
}
void invArray_free(invArray_t invArray){
    int i;
    for(i=0;i<invArray->maxInv;i++){
        free(invArray->vettInv[i].nome);
        free(invArray->vettInv[i].tipo);
    }
    free(invArray->vettInv);
    free(invArray);
}

/* lettura e scrittura su file */
void invArray_read(FILE *fp, invArray_t invArray){
    int i;
    fscanf(fp,"%d/*c",&(invArray->maxInv));
    invArray->vettInv = (inv_t*)malloc((invArray->maxInv)* sizeof(inv_t));
    for(i=0;i<invArray->maxInv;i++){
        inv_read(fp,&(invArray->vettInv[i]));
    }
}
void invArray_print(FILE *fp, invArray_t invArray){
    int i;
    for(i=0;i<invArray->maxInv;i++){
        inv_print(fp,&(invArray->vettInv[i]));
    }
}
/* stampa un unico oggetto selezionato da indice (nel vettore) */
void invArray_printByIndex(FILE *fp, invArray_t invArray, int index){
    inv_print(fp,&(invArray->vettInv[index]));
}
/* ritorna puntatore a oggetto selezionato da indice (nel vettore) */
inv_t *invArray_getByIndex(invArray_t invArray, int index){
    return &(invArray->vettInv[index]);
}
/* ritorna indice (nel vettore) a oggetto selezionato da nome */
int invArray_searchByName(invArray_t invArray, char *name){
    int i;
    for(i=0;i<invArray->maxInv;i++){
        if(strcmp(invArray->vettInv[i].nome,name)==0){
            return i;
        }
    }
    return -1;
}
