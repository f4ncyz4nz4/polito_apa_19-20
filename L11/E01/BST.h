//
// Created by loren on 08/01/2020.
//

#ifndef E01_BST_H
#define E01_BST_H
#include <stdlib.h>
#include "data.h"

typedef struct binarysearchtree *BST;

BST BSTinit();
void BSTfree(BST bst);
Data BSTsearch(BST bst, float qg);
void BSTinsert_leafR(BST bst, float qg,Data d);
float BSTVisitMax(BST bst,Data i,Data f);
float BSTVisitMin(BST bst,Data i,Data f);
void BSTvisit(FILE *fout,BST bst);
void BSTbalance(BST bst);
int CamMM(BST bst,int s);

#endif //E01_BST_H
