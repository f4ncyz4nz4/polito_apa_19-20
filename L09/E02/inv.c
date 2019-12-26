//
// Created by loren on 22/12/2019.
//

#include "inv.h"

/* funzioni di input/output delle statistiche */
void stat_read(FILE *fp, stat_t *statp){
    fscanf(fp, "%d", &(statp->hp));
    fscanf(fp, "%d", &(statp->mp));
    fscanf(fp, "%d", &(statp->atk));
    fscanf(fp, "%d", &(statp->def));
    fscanf(fp, "%d", &(statp->mag));
    fscanf(fp, "%d", &(statp->spr));
}
void stat_print(FILE *fp, stat_t *statp, int soglia){
    if(statp->hp<soglia)
        fprintf(fp,"\thp:%d",soglia);
    else
        fprintf(fp,"\thp:%d\t",statp->hp);
    if(statp->mp<soglia)
        fprintf(fp,"\tmp:%d",soglia);
    else
        fprintf(fp,"\tmp:%d\t",statp->mp);
    if(statp->atk<soglia)
        fprintf(fp,"\tatk:%d",soglia);
    else
        fprintf(fp,"\tatk:%d\t",statp->atk);
    if(statp->def<soglia)
        fprintf(fp,"\tdef:%d",soglia);
    else
        fprintf(fp,"\tdef:%d\t",statp->def);
    if(statp->mag<soglia)
        fprintf(fp,"\tmag:%d",soglia);
    else
        fprintf(fp,"\tmag:%d\t",statp->mag);
    if(statp->spr<soglia)
        fprintf(fp,"\tspr:%d",soglia);
    else
        fprintf(fp,"\tspr:%d\n",statp->spr);
}

/* funzioni di input/output di un oggetto dell'inventario */
void inv_read(FILE *fp, inv_t *invp){
    fscanf(fp,"%s",invp->nome);
    fscanf(fp,"%s",invp->tipo);
    fscanf(fp,"%d",&(invp->stat.hp));
    fscanf(fp,"%d",&(invp->stat.mp));
    fscanf(fp,"%d",&(invp->stat.atk));
    fscanf(fp,"%d",&(invp->stat.def));
    fscanf(fp,"%d",&(invp->stat.mag));
    fscanf(fp,"%d",&(invp->stat.spr));
}
void inv_print(FILE *fp, inv_t *invp){
    fprintf(fp,"\tNome: %s\tTipo: %s\n",invp->nome,invp->tipo);
    fprintf(fp,"\tStatistiche:\n");
    stat_print(fp,&(invp->stat),-100000);
}

/* ritorna il campo stat di un oggetto dell'inventario */
stat_t inv_getStat(inv_t *invp){
    return invp->stat;
}
/* copia le statistiche */
void stat_copy(stat_t *s1,stat_t s2){
    s1->hp=s2.hp;
    s1->mp=s2.mp;
    s1->atk=s2.atk;
    s1->def=s2.def;
    s1->mag=s2.mag;
    s1->spr=s2.spr;
}
/* somma le statistiche */
void stat_sum(stat_t *s1,stat_t s2){
    s1->hp+=s2.hp;
    s1->mp+=s2.mp;
    s1->atk+=s2.atk;
    s1->def+=s2.def;
    s1->mag+=s2.mag;
    s1->spr+=s2.spr;
}
