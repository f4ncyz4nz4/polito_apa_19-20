//
// Created by loren on 21/12/2019.
//

#include "pg.h"

link_nodoPg ricercaPersonaggio(tabPg Pg,char *codice_pg){
    link_nodoPg x;
    for (x=Pg->headPg; x!=NULL; x=x->next) {
        if (strcmp(x->datiPg.codice,codice_pg)==0) {
            return x;
        }
    }
    return NULL;
}
int ricercaEquipaggiamento_personaggio(char nome_equip[MAXC+1],tabInv inv){/*Ricerca equipaggiamento già in dotazione ad un personaggio*/
    int i=0;
    for(i=0;i<inv->maxInv;i++){
        if(strcmp(nome_equip,inv->vettInv[i].nome)==0){
            return i;
        }
    }
    return -1;
}
link_nodoPg newNode(FILE *pg_file, link_nodoPg next) {
    char buf[MAXC];
    link_nodoPg x = malloc(sizeof *x);
    if (x==NULL)
        return NULL;
    else {
        fscanf(pg_file,"%s",buf);
        x->datiPg.codice=strdup(buf);
        fscanf(pg_file,"%s",buf);
        x->datiPg.nome=strdup(buf);
        fscanf(pg_file,"%s",buf);
        x->datiPg.classe=strdup(buf);
        fscanf(pg_file,"%d",&(x->datiPg.statp.hp));
        fscanf(pg_file,"%d",&(x->datiPg.statp.mp));
        fscanf(pg_file,"%d",&(x->datiPg.statp.atk));
        fscanf(pg_file,"%d",&(x->datiPg.statp.def));
        fscanf(pg_file,"%d",&(x->datiPg.statp.mag));
        fscanf(pg_file,"%d",&(x->datiPg.statp.spr));
        x->datiPg.equip.inUso=0;
        x->next=next;
    }
    return x;
}
tabPg listInsTail(FILE *fp,tabPg Pg) {
    if(Pg->headPg==NULL){
        Pg->headPg=newNode(fp,Pg->headPg);
        Pg->tailPg=Pg->headPg;
    } else
        Pg->headPg=newNode(fp,Pg->headPg);
    return Pg;
}
tabPg listDelKey(tabPg Pg) {
    char key_cod[COD+1];
    link_nodoPg x, p;
    printf("\nInserisci codice personaggio da eliminare: ");
    scanf("%s",key_cod);
    if (Pg->headPg == NULL)
        return NULL;
    for (x=Pg->headPg, p=NULL; x!=NULL; p=x, x=x->next) {
        if (strcmp(x->datiPg.codice,key_cod)==0) {
            if (x==Pg->headPg) {
                Pg->headPg = x->next;
                Libera(x);
                Pg->nPg--;
            }
            else if (x==Pg->tailPg){
                p->next=NULL;
                Pg->tailPg=p;
                Libera(x);
                Pg->nPg--;
            }
            else {
                p->next = x->next;
                Libera(x);
                Pg->nPg--;
            }
            return Pg;
        }
    }
    printf("Personaggio non trovato\n");
    return Pg;
}
void ModificaEquip(tabPg Pg,tabInv invent){
    int cmd_equip,i,indice_equip;
    char codice_pg[COD+1],nome_equip[MAXC+1];
    link_nodoPg tmp =NULL;
    printf("\nInserisci codice personaggio interessato: ");
    scanf("%s",codice_pg);
    tmp = ricercaPersonaggio(Pg,codice_pg);
    printf("\nVuoi aggiungere(1) o togliere(2) un equipaggiamento: ");
    scanf("%d",&cmd_equip);
    if(cmd_equip==1) {
        printf("\nInserisci nome equipaggiamento da aggiungere: ");
        scanf("%s",nome_equip);
        indice_equip = ricercaEquipaggiamento(nome_equip,invent);
        (tmp->datiPg.equip.vettEq[tmp->datiPg.equip.inUso++]) = &(invent->vettInv[indice_equip]);
    }
    else {
        printf("\nInserisci nome equipaggiamento da togliere: ");
        scanf("%s", nome_equip);
        indice_equip = ricercaEquipaggiamento_personaggio(nome_equip,invent);
        if(indice_equip==-1){
            printf("Oggetto non equipaggiato");
            return;
        }
        for(i=indice_equip;i<tmp->datiPg.equip.inUso-1;i++)
            (tmp->datiPg.equip.vettEq[i]) = (tmp->datiPg.equip.vettEq[i+1]);
        tmp->datiPg.equip.inUso--;
    }
}
void StampaPersonaggio(tabPg Pg,tabInv inv){
    char codice_pg[COD+1];
    int i;
    link_nodoPg x =NULL, tmp =NULL;
    printf("Inserisci codice del personaggio da stampare:\n");
    scanf("%s",codice_pg);
    x = ricercaPersonaggio(Pg,codice_pg);
    printf("Codice:\t%s\n",x->datiPg.codice);
    printf("Nome:\t%s\n",x->datiPg.nome);
    printf("Classe:\t%s\n",x->datiPg.classe);
    printf("Inventario:\n");
    for(i=0;i<x->datiPg.equip.inUso;i++) {
        stampareEquipaggiamento(inv,i);
    }
    tmp = calcolaStats(x);
    printf("Statistiche:\n");
    if(tmp->datiPg.statp.hp<1)
        printf("hp:1");
    else
        printf("hp:%d\t",tmp->datiPg.statp.hp);
    if(tmp->datiPg.statp.mp<1)
        printf("mp:1");
    else
        printf("mp:%d\t",tmp->datiPg.statp.mp);
    if(tmp->datiPg.statp.atk<1)
        printf("atk:1");
    else
        printf("atk:%d\t",tmp->datiPg.statp.atk);
    if(tmp->datiPg.statp.def<1)
        printf("def:1");
    else
        printf("def:%d\t",tmp->datiPg.statp.def);
    if(tmp->datiPg.statp.mag<1)
        printf("mag:1");
    else
        printf("mag:%d\t",tmp->datiPg.statp.mag);
    if(tmp->datiPg.statp.spr<1)
        printf("spr:1");
    else
        printf("spr:%d\n",tmp->datiPg.statp.spr);
    free(tmp);
}
link_nodoPg calcolaStats(link_nodoPg head){
    int i;
    link_nodoPg tmp =NULL;
    tmp=malloc(sizeof(link_nodoPg));
    tmp->datiPg.statp.hp = head->datiPg.statp.hp;
    tmp->datiPg.statp.mp = head->datiPg.statp.mp;
    tmp->datiPg.statp.atk = head->datiPg.statp.atk;
    tmp->datiPg.statp.def = head->datiPg.statp.def;
    tmp->datiPg.statp.mag = head->datiPg.statp.mag;
    tmp->datiPg.statp.spr = head->datiPg.statp.spr;
    for(i=0;i<head->datiPg.equip.inUso;i++){
        tmp->datiPg.statp.hp += head->datiPg.equip.vettEq[i]->statp_mod.hp;
        tmp->datiPg.statp.mp += head->datiPg.equip.vettEq[i]->statp_mod.mp;
        tmp->datiPg.statp.atk += head->datiPg.equip.vettEq[i]->statp_mod.atk;
        tmp->datiPg.statp.def += head->datiPg.equip.vettEq[i]->statp_mod.def;
        tmp->datiPg.statp.mag += head->datiPg.equip.vettEq[i]->statp_mod.mag;
        tmp->datiPg.statp.spr += head->datiPg.equip.vettEq[i]->statp_mod.spr;
    }
    return tmp;
}
void Libera(link_nodoPg x){
    free(x->datiPg.codice);
    free(x->datiPg.nome);
    free(x->datiPg.classe);
    free(x->datiPg.equip.vettEq);
    free(x);
}