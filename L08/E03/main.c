#include "inv.h"
#include "pg.h"

void LIBERATUTTI(tabPg Pg,tabInv inv);
typedef enum{
    cmd_pg_nuovo=1,cmd_inv_nuovo,cmd_pg_del,cmd_mod_equip,cmd_stampa,cmd_fine
}t_cmd;
int main() {
    FILE *inv_file=NULL,*pg_file=NULL;
    tabPg Pg;
    tabInv invent;
    int cmd_menu;
    Pg=(tabPg)malloc(sizeof(struct tabPg_t));
    invent=(tabInv)malloc(sizeof(struct tabInv_t));
    Pg->headPg=NULL;Pg->tailPg=NULL;Pg->nPg=0;
    invent->vettInv=NULL;invent->maxInv=0;invent->nInv=0;
    do {
        printf("(1)Aggiungi personaggi\n"
               "(2)Aggiungi equipaggiamenti\n"
               "(3)Elimina personaggio\n"
               "(4)Modifica equipaggiamento personaggio\n"
               "(5)Stampa personaggio\n"
               "(6)Fine\n");
        printf("Inserisci comando:");
        scanf("%d",&cmd_menu);
        switch (cmd_menu) {
            case cmd_pg_nuovo:
                pg_file = fopen("pg.txt","r");
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
                Pg=listDelKey(Pg);
                break;
            case cmd_mod_equip:
                ModificaEquip(Pg,invent);
                break;
            case cmd_stampa:
                StampaPersonaggio(Pg,invent);
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
    free(Pg);
}
