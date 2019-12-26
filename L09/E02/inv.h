#ifndef INV_H_DEFINED
#define INV_H_DEFINED

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define LEN 100
#define MIN_STAT 1

/* quasi ADT statistiche */
typedef struct stat_s {
  int hp, mp, atk, def, mag, spr;
} stat_t;

/* quasi ADT oggetto di inventario */
typedef struct inv_s {
  char nome[LEN];
  char tipo[LEN];
  stat_t stat;
} inv_t;

/* funzioni di input/output delle statistiche */
void stat_read(FILE *fp, stat_t *statp);
void stat_print(FILE *fp, stat_t *statp, int soglia);

/* funzioni di input/output di un oggetto dell'inventario */
void inv_read(FILE *fp, inv_t *invp);
void inv_print(FILE *fp, inv_t *invp);

/* ritorna il campo stat di un oggetto dell'inventario */
stat_t inv_getStat(inv_t *invp);
/* copia le statistiche */
void stat_copy(stat_t *s1,stat_t s2);
/* somma le statistiche */
void stat_sum(stat_t *s1,stat_t s2);

/* Si possono aggiungere altre funzioni se ritenute necessarie */

#endif
