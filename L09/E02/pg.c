//
// Created by loren on 22/12/2019.
//

#include "pg.h"

/* lettura e scrittura su file */
int pg_read(FILE *fp, pg_t *pgp) {
    fscanf(fp, "%s", pgp->cod);
    fscanf(fp, "%s", pgp->nome);
    fscanf(fp, "%s", pgp->classe);
    stat_read(fp,&(pgp->b_stat));
    stat_copy(&(pgp->eq_stat),pgp->b_stat);
    pgp->equip=equipArray_init();
    return 9;
}

/* non essendo struct dinamica, pulisce chiamando il distruttire di equipArray */
void pg_clean(pg_t *pgp){
    equipArray_free(pgp->equip);
}

void pg_print(FILE *fp, pg_t *pgp, invArray_t invArray){
    fprintf(fp,"Codice:\t%s\n",pgp->cod);
    fprintf(fp,"Nome:\t%s\n",pgp->nome);
    fprintf(fp,"Classe:\t%s\n",pgp->classe);
    equipArray_print(fp,pgp->equip,invArray);
    calcolaStats(pgp,invArray);
    fprintf(fp,"Statistiche senza equipaggiamento:\n");
    stat_print(fp,&(pgp->b_stat),1);
    fprintf(fp,"Statistiche con equipaggiamento:\n");
    stat_print(fp,&(pgp->eq_stat),1);
}
/* modifica personaggio aggiungendo/togliendo un equipaggiamento selezionato da inventario:
di fatto e' sufficiente chiamare l'opportuna funzione dal modulo equipArray */
void pg_updateEquip(pg_t *pgp, invArray_t invArray){
    equipArray_update(pgp->equip,invArray);
}

/* calcola le statistiche */
void calcolaStats(pg_t *pgp, invArray_t invArray){
    int i;
    stat_copy(&(pgp->eq_stat),pgp->b_stat);
    for(i=0;i<equipArray_inUse(pgp->equip);i++){
        stat_sum(&(pgp->eq_stat),inv_getStat(invArray_getByIndex(invArray,equipArray_getEquipByIndex(pgp->equip,i))));
    }
}
