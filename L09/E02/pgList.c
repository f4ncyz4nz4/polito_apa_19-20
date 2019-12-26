//
// Created by loren on 21/12/2019.
//

#include "pgList.h"
typedef struct node *link;
struct node{
    pg_t pg;
    link next;
};
struct pgList_s{
    link headPg;
    link tailPg;
    int nPg;
};
/* creatore e distruttore */
pgList_t pgList_init(){
    pgList_t pgList;
    pgList=(pgList_t)malloc(sizeof(struct pgList_s));
    pgList->headPg=NULL;
    pgList->tailPg=NULL;
    pgList->nPg=0;
    return pgList;
}
void pgList_free(pgList_t pgList){
    link x,p;
    for (p=NULL,x=pgList->headPg; x!=NULL;p=x,x=x->next){
        if(p!=NULL){
            pg_clean(&(p->pg));
            free(p);
        }
    }
    pg_clean(&(p->pg));
    free(p);
    free(pgList);
}

/* lettura e scrittura su file */
void pgList_read(FILE *fp, pgList_t pgList){
    pg_t pg;
    while(!feof(fp)){
        pg_read(fp,&(pg));
        pgList_insert(pgList,pg);
    }
    pgList->nPg--;
}
void pgList_print(FILE *fp, pgList_t pgList, invArray_t invArray){
    link x;
    fprintf(fp,"%d PERSONAGGI:\n",pgList->nPg);
    for (x=pgList->headPg; x!=NULL; x=x->next){
        pg_print(fp,&(x->pg),invArray);
    }
}

/* inserimento di un nuovo personaggio */
void pgList_insert(pgList_t pgList, pg_t pg){
    link x = malloc(sizeof(struct node));
    if(pgList->headPg==NULL){
        x->pg=pg;
        x->next=pgList->headPg;
        pgList->headPg=x;
        pgList->tailPg=pgList->headPg;
        pgList->nPg++;
    } else {
        x->pg = pg;
        x->next = pgList->headPg;
        pgList->headPg = x;
        pgList->nPg++;
    }
}
/* cancellazione con rimozione */
void pgList_remove(pgList_t pgList, char* cod){
    link x, p;
    if (pgList->headPg == NULL)
        return;
    for (x=pgList->headPg, p=NULL; x!=NULL; p=x, x=x->next) {
        if (strcmp(x->pg.cod,cod)==0){
            if (x==pgList->headPg) {
                pgList->headPg = x->next;
                pg_clean(&(x->pg));
                free(x);
                pgList->nPg--;
            }
            else if (x==pgList->tailPg){
                p->next=NULL;
                pgList->tailPg=p;
                pg_clean(&(x->pg));
                free(x);
                pgList->nPg--;
            }
            else {
                p->next = x->next;
                pg_clean(&(x->pg));
                free(x);
                pgList->nPg--;
            }
        }
    }
}
/* ricerca per codice, ritornando il puntatore */
pg_t *pgList_searchByCode(pgList_t pgList, char* cod){
    link x;
    if (pgList->headPg == NULL)
        return NULL;
    for (x=pgList->headPg; x!=NULL; x=x->next) {
        if (strcmp(x->pg.cod,cod)==0){
            return &(x->pg);
        }
    }
    return NULL;
}
