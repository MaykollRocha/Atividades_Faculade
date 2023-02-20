#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "headtree.h"

//exercises

//return diference in betwen bigger and lower;
int biggerTree(Nodo *r,int bigger)
{
    if(r){
        if(bigger < r->data){
            bigger = r->data;
        }
        bigger = biggerTree(r->left,bigger);
        bigger = biggerTree(r->right,bigger);
    }
    return bigger;
}

int lowerTree(Nodo *r,int lower)
{
    if(r){
        if(lower > r->data){
            lower = r->data;
        }
        lower = lowerTree(r->left,lower);
        lower = lowerTree(r->right,lower);
    }
    return lower;
}

int diferenceBigLower(Nodo *r)
{
    return biggerTree(r,r->data) - lowerTree(r,r->data);
}

//seek father node
int fathernode(Nodo *r,int n)
{
    if(r){
        if(r->data == n){
            return 0;
        }

        if((r->right?(r->right->data == n):0) || (r->left?(r->left->data == n):0)){
            return r->data;
        }

        return 0 + fathernode(r->left,n) + fathernode(r->right,n);

    }
    return 0;
}

//same key and representation
int sameTrees(Nodo *r1,Nodo *r2)
{
    if(r1 && r2){
        if(r1->data == r2->data)
            return 1* sameTrees(r1->right,r2->right)* sameTrees(r1->left,r2->left);
        return 0;
    }
    return 1;
}

//simetric trees
int simetric(Nodo *r1,Nodo *r2)
{
    if(r1 && r2){
        if(r1->data == r2->data)
            return 1* simetric(r1->right,r2->left)* simetric(r1->left,r2->right);
        return 0;
    }
    return 1;
}
//finish exercices

//Main is contructor Tree automatic and check the exercices
int main(){
    Nodo *root = NULL;
    Nodo *Sroot = NULL;
    Nodo *rootO = NULL;
    srand(time(NULL));
    char n1;
    for (int i=0;i<10;i++){
        // It is used for enclosed letters second ASCII(65~98).
        //root = insertTree(root,(rand()%24+65),i);
        //rootO = searchTree(rootO,rand()%24+65);
        // use to number and edit percursion for %i not %c or a new
        n1 = rand()%100;
        printf("%i ",n1);
        root = insertTree(root,n1,i);
        Sroot = insertTree(Sroot,n1,i);
        rootO = searchTree(rootO,n1);
    }


    printf("\n--Tree-messy--\n");
    infixTree(root);
    printf("\nleft: ");
    infixTree(root->left);
    printf("\nright: ");
    infixTree(root->right);
    printf("\n Reverse tree");
    esrever(root);
    printf("\nleft: ");
    infixTree(root->left);
    printf("\nright: ");
    infixTree(root->right);
    printf("\n------------------\n--tree-orderly--");
    printf("\nInfix percussion: ");
    infixTree(rootO);
    printf("\nprefix percussion: ");
    prefixTree(rootO);
    printf("\nposfix percussion: ");
    postfixTree(rootO);
    printf("\nDescending order: ");
    ReinfixTree(rootO);
    printf("\nnested parentheses: ");
    nestedparentheses(rootO);
    printf("\n--------------------\n");

    //exercies
    printf("SearchTree Diference: %i", diferenceBigLower(rootO));
    printf("\nBinary Tree Diference: %i", diferenceBigLower(root));
    printf("\nHeight: %i", height(rootO));
    printf("\nNumber Nodes: %i", NumberNodes(rootO));
    printf("\nNumber leaves nodes: %i", leavesNodes(rootO));
    printf("\nNumber of nodes (nor leaves): %i", notleavesNodes(rootO));
    printf("\nThis a degenerate tree: %s", isdegeneratetree(rootO)?"True":"false");
    /*
    int seek;
    printf("\n Which node do you want the parent from?");
    scanf("%i",&seek);
    printf(" The parent of %i as %i",seek, fathernode(rootO,seek));
     */
    printf("\nIs a search tree? %s", ifsearchtree(rootO)?"Yes":"No" );
    printf("\nIs a search tree? %s", ifsearchtree(root)?"Yes":"No" );
    handbfbynode(rootO);
    handbfbynode(root);
    printf("\nIt's AVL? %s", itavl(rootO)?"Yes":"No");
    printf("\nit's same key and representation? %s", sameTrees(root,rootO)?"Yes":"No");
    printf("\nit's same key and representation? %s", sameTrees(root,root)?"Yes":"No");
    printf("\nit's simetric Trees? %s", simetric(root,Sroot)?"Yes":"No");
    printf("\nit's simetric Trees? %s\n", simetric(root,root)?"Yes":"No");
    printf("Key in nivel right-left: ");
    printLevelOrder(rootO);
    printf("\n");
    //Clear tree in dinamic location becase is alocate in your memory
    clear(root);
    clear(rootO);
    clear(Sroot);
    return 1;
}