//
// Created by loren on 21/12/2019.
//

#include "inv.h"

int salvaInventario(FILE *inv_file,tabInv inv){
    int i;
    char buf[MAXC];
    fscanf(inv_file,"%d/*c",&(inv->maxInv));
    inv->vettInv = (link_inv)malloc((inv->maxInv)* sizeof(struct inv_t));
    for(i=0;i<inv->maxInv;i++) {
        fscanf(inv_file,"%s%*c",buf);
        inv->vettInv[i].nome=strdup(buf);
        fscanf(inv_file,"%s%*c",buf);
        inv->vettInv[i].tipo=strdup(buf);
        fscanf(inv_file, "%d %d %d %d %d %d", &(inv->vettInv[i].statp_mod.hp), &(inv->vettInv[i].statp_mod.mp),
               &(inv->vettInv[i].statp_mod.atk), &(inv->vettInv[i].statp_mod.def), &(inv->vettInv[i].statp_mod.mag),
               &(inv->vettInv[i].statp_mod.spr));
    }
    return 1;
}
int ricercaEquipaggiamento(char nome_equip[MAXC+1],tabInv inv){/*Ricerca equipaggiamento nel vettore equipaggiamentèi*/
    int i=0;
    for(i=0;i<inv->maxInv;i++){
        if(strcmp(nome_equip,inv->vettInv[i].nome)==0){
            return i;
        }
    }
    return -1;
}
void stampareEquipaggiamento(tabInv inv,int indice){
    printf("\tNome: %s\tTipo: %s\n",inv->vettInv[indice].nome,inv->vettInv[indice].tipo);
    printf("\tStats equip\n");
    printf("\thp:%d\t",inv->vettInv[indice].statp_mod.hp);
    printf("mp:%d\t",inv->vettInv[indice].statp_mod.mp);
    printf("atk:%d\t",inv->vettInv[indice].statp_mod.atk);
    printf("def:%d\t",inv->vettInv[indice].statp_mod.def);
    printf("mag:%d\t",inv->vettInv[indice].statp_mod.mag);
    printf("spr:%d\n",inv->vettInv[indice].statp_mod.spr);
}
