//
// Created by loren on 21/12/2019.
//

#ifndef E03_PG_H
#define E03_PG_H

#define COD 6
#include "inv.h"

typedef struct tabEquip_t{/*Wrapper*/
    int inUso;
    link_inv vettEq[8];
}tabEquip;
typedef struct pg_t{
    char *codice;
    char *nome;
    char *classe;
    tabEquip equip;/*(Puntatore) alla struct tabEquip_t*/
    stat statp;
}pg;
typedef struct nodoPg_t {
    pg datiPg;
    struct nodoPg_t *next;/*Puntantore a nodoPg_t*/
}*link_nodoPg ;
typedef struct tabPg_t{/*Wrapper*/
    link_nodoPg headPg;
    link_nodoPg tailPg;
    int nPg;
}*tabPg;

link_nodoPg ricercaPersonaggio(tabPg Pg,char codice_pg[COD+1]);
int ricercaEquipaggiamento_personaggio(char nome_equip[MAXC+1],tabInv inv);
link_nodoPg newNode(FILE *pg_file, link_nodoPg next);
tabPg listInsTail(FILE *fp,tabPg Pg);
tabPg listDelKey(tabPg Pg);
void ModificaEquip(tabPg Pg,tabInv invent);
void StampaPersonaggio(tabPg Pg,tabInv inv);
link_nodoPg calcolaStats(link_nodoPg head);
void Libera(link_nodoPg x);

#endif //E03_PG_H
