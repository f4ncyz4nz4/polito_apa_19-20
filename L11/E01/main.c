#include <stdio.h>
#include <stdlib.h>
#include "LTitles.h"

int main() {
    int fine,cmd,soglia;
    FILE *fp;
    char filenome[11],string[11];

    fine = 0;
    LTitle LT;
    LT=LTinit();
    while(!fine) {
        printf("\nOperazioni azionarie\n");
        printf("===============\n");
        printf("1.Acquisizione da file\n");
        printf("2.Ricerca di un titolo azionario\n");
        printf("3.Ricerca quotazione\n");
        printf("4.Ricerca quotazione min e max\n");
        printf("5.Bilanciamento BTS\n");
        printf("6.Fine\n");
        printf("Comando : ");
        if(scanf("%d",&cmd)<=0) {
            printf("Solo interi!\n");
            exit(0);
        }
        else {
            switch(cmd) {
                case 1:
                    printf("Inserire il nome del file\n");
                    scanf("%s",filenome);
                    fp=fopen(filenome,"r");
                    while (!feof(fp)) {
                        LT = LTGet(LT, fp);
                    }
                    break;
                case 2:
                    printf("Inserire il nome del titolo da cercare\n");
                    scanf("%s",string);
                    Tprint(stdout,LTSearchGet(LT,string));
                    break;
                case 3:
                    printf("Inserire il nome del titolo contenente la quotazione da cercare\n");
                    scanf("%s",string);
                    TsearchQ(stdout,LTSearchGet(LT,string));
                    break;
                case 4:
                    printf("Inserire il nome del titolo contenente i minimi e massimi cercati\n");
                    scanf("%s",string);
                    TsearchMaxMin(stdout,LTSearchGet(LT,string));
                    break;
                case 5:
                    printf("Inserire il nome del titolo il cui albero va bilanciato\n");
                    scanf("%s",string);
                    printf("Inserire la soglia\n");
                    scanf("%d",&soglia);
                    TsearchB(LTSearchGet(LT,string),soglia);
                    break;
                case 6:
                    fine = 1;
                    if(!LTempty(LT))
                        LTfree(LT);
                    break;
                default:    printf("Opzione non valida\n");
            }
        }
    }
    return 0;
}
