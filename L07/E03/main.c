#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXC 50
#define COD 6
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
typedef struct tabInv_t{/*Wrapper*/
    link_inv vettInv;
    int nInv;
    int maxInv;
}*tabInv;
int salvaInventario(FILE *inv_file,tabInv inv);
link_nodoPg ricercaPersonaggio(tabPg Pg,char codice_pg[COD+1]);
int ricercaEquipaggiamento(char nome_equip[MAXC+1],tabInv inv);
int ricercaEquipaggiamento_personaggio(char nome_equip[MAXC+1],tabInv inv);
link_nodoPg newNode(FILE *pg_file, link_nodoPg next);
tabPg listInsTail(FILE *fp,tabPg Pg);
tabPg listDelKey(tabPg Pg, char *key_cod);
void Libera(link_nodoPg x);
void LIBERATUTTI(tabPg Pg,tabInv inv);
typedef enum{
    cmd_pg_nuovo=1,cmd_inv_nuovo,cmd_pg_del,cmd_mod_equip,cmd_calcola_stat,cmd_fine
}t_cmd;
int main() {
    FILE *inv_file=NULL,*pg_file=NULL;
    tabPg Pg;
    tabInv invent;
    link_nodoPg tmp =NULL;
    char codice_pg[COD+1],nome_equip[MAXC+1];
    int cmd_menu,cmd_equip,indice_equip;
    int i;
    Pg=(tabPg)malloc(sizeof(struct tabPg_t));
    invent=(tabInv)malloc(sizeof(struct tabInv_t));
    Pg->headPg=NULL;Pg->tailPg=NULL;Pg->nPg=0;
    invent->vettInv=NULL;invent->maxInv=0;invent->nInv=0;
    do {
        printf("(1)Aggiungi personaggi\n"
               "(2)Aggiungi equipaggiamenti\n"
               "(3)Elimina personaggio\n"
               "(4)Modifica equipaggiamento personaggio\n"
               "(5)Calcola statistiche personaggio\n"
               "(6)Fine\n");
        printf("Inserisci comando:");
        scanf("%d",&cmd_menu);
        switch (cmd_menu) {
            case cmd_pg_nuovo:
                pg_file = fopen("pg.txt","r");
                if(pg_file==NULL)
                    return -1;
                while (!feof(pg_file)){
                    listInsTail(pg_file,Pg);
                }
                fclose(pg_file);
                break;
            case cmd_inv_nuovo:
                inv_file=fopen("inventario.txt","r");
                salvaInventario(inv_file,invent);
                fclose(inv_file);
                break;
            case cmd_pg_del:
                printf("\nInserisci codice personaggio da eliminare: ");
                scanf("%s",codice_pg);
                Pg=listDelKey(Pg,codice_pg);
                break;
            case cmd_mod_equip:
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
                        break;
                    }
                    for(i=indice_equip;i<tmp->datiPg.equip.inUso-1;i++)
                        (tmp->datiPg.equip.vettEq[i]) = (tmp->datiPg.equip.vettEq[i+1]);
                    tmp->datiPg.equip.inUso--;
                }
                break;
            case cmd_calcola_stat:
                printf("\nInserisci codice del personaggio di cui vuoi calcolare le statistiche: ");
                scanf("%s",codice_pg);
                tmp = ricercaPersonaggio(Pg,codice_pg);
                for(i=0;i<tmp->datiPg.equip.inUso;i++){
                    tmp->datiPg.statp.hp += tmp->datiPg.equip.vettEq[i]->statp_mod.hp;
                    tmp->datiPg.statp.mp += tmp->datiPg.equip.vettEq[i]->statp_mod.mp;
                    tmp->datiPg.statp.atk += tmp->datiPg.equip.vettEq[i]->statp_mod.atk;
                    tmp->datiPg.statp.def += tmp->datiPg.equip.vettEq[i]->statp_mod.def;
                    tmp->datiPg.statp.mag += tmp->datiPg.equip.vettEq[i]->statp_mod.mag;
                    tmp->datiPg.statp.spr += tmp->datiPg.equip.vettEq[i]->statp_mod.spr;
                }
                printf("Statistiche di %s:\n",tmp->datiPg.codice);

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
                break;
            case cmd_fine:
                printf("\nFINE PROGRAMMA\n");
                return 0;
            default:
                printf("\nCOMANDO NON VALIDO,RIPROVARE\n");
                break;
        }
    }
    while(cmd_menu!=cmd_fine);
    LIBERATUTTI(Pg,invent);
    return 0;
}
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
link_nodoPg ricercaPersonaggio(tabPg Pg,char *codice_pg){
    link_nodoPg x;
    for (x=Pg->headPg; x!=NULL; x=x->next) {
        if (strcmp(x->datiPg.codice,codice_pg)==0) {
            return x;
        }
    }
    return NULL;
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
tabPg listDelKey(tabPg Pg, char *key_cod) {
    link_nodoPg x, p;
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
void Libera(link_nodoPg x){
    free(x->datiPg.codice);
    free(x->datiPg.nome);
    free(x->datiPg.classe);
    free(x->datiPg.equip.vettEq);
    free(x);
}
void LIBERATUTTI(tabPg Pg,tabInv inv){
    int i;
    link_nodoPg x,p;
    //Eliminazione inv
    for(i=0;i<inv->maxInv;i++){
        free(inv->vettInv[i].nome);
        free(inv->vettInv[i].tipo);
    }
    free(inv->vettInv);
    free(inv);
    //Eliminazione PG
    for (p=NULL,x=Pg->headPg; x!=NULL;p=x,x=x->next){
        if(p!=NULL){
            Libera(p);
        }
    }
    Libera(p);
}
