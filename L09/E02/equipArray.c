//
// Created by loren on 22/12/2019.
//

#include "equipArray.h"
struct equipArray_s{
    int inUso;
    int vettEq[8];
};

/* creatore e disruttore */
equipArray_t equipArray_init(){
    int i;
    equipArray_t equipArray;
    equipArray=(equipArray_t)malloc(sizeof(struct equipArray_s));
    equipArray->inUso=0;
    for(i=0;i<8;i++){
        equipArray->vettEq[i]=0;
    }
    return equipArray;
}
void equipArray_free(equipArray_t equipArray){
    free(equipArray);
}

/* quanti equipaggiamenti sono in uso */
int equipArray_inUse(equipArray_t equipArray){
    return equipArray->inUso;
}

/* scrittura su file */
void equipArray_print(FILE *fp, equipArray_t equipArray, invArray_t invArray){
    int i;
    printf("Equipaggiamento:\n");
    for(i=0;i<equipArray->inUso;i++) {
        invArray_printByIndex(fp,invArray,i);
    }
}
/* modifica equipaggiamento scegliendo un oggetto da inventario */
void equipArray_update(equipArray_t equipArray, invArray_t invArray){
    int i,cmd_equip,ind_equip;
    char nome_equip[50];
    printf("\nVuoi aggiungere(1) o togliere(2) un equipaggiamento: ");
    scanf("%d",&cmd_equip);
    if(cmd_equip==1) {
        printf("\nInserisci nome equipaggiamento da aggiungere: ");
        scanf("%s",nome_equip);
        (equipArray->vettEq[equipArray->inUso]) = invArray_searchByName(invArray,nome_equip);
        equipArray->inUso++;
    }
    else {
        printf("\nInserisci nome equipaggiamento da togliere: ");
        scanf("%s",nome_equip);
        ind_equip = invArray_searchByName(invArray,nome_equip);
        if(ind_equip==-1){
            printf("Oggetto non equipaggiato");
            return;
        } else {
            for (i = ind_equip; i < equipArray->inUso - 1; i++)
                (equipArray->vettEq[i]) = (equipArray->vettEq[i + 1]);
            equipArray->inUso--;
        }
    }
}
/* torna indice (nel vettore inventario) dell'oggetto in posizione index (0..EQUIP_SLOT-1) di equipArray */
int equipArray_getEquipByIndex(equipArray_t equipArray, int index){
    return equipArray->vettEq[index];
}
