//
// Created by loren on 21/12/2019.
//

#ifndef E03_INV_H
#define E03_INV_H

#define MAXC 50
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct stat_t{
    int hp;
    int mp;
    int atk;
    int def;
    int mag;
    int spr;
}stat;
typedef struct inv_t{
    char *nome;
    char *tipo;
    stat statp_mod;
}*link_inv;
typedef struct tabInv_t{/*Wrapper*/
    link_inv vettInv;
    int nInv;
    int maxInv;
}*tabInv;

int salvaInventario(FILE *inv_file,tabInv inv);
int ricercaEquipaggiamento(char nome_equip[MAXC+1],tabInv inv);
void stampareEquipaggiamento(tabInv inv,int indice);

#endif //E03_INV_H
