#ifndef HEADTREE_H
#define HEADTREE_H
typedef struct _nodo
{
    char data;
    struct _nodo *left;
    struct _nodo *right;
    int h;
    int fb;
}Nodo;

//Insertion and clear tree
void clear(Nodo *r)
{
    if(r){
        clear(r->left);
        clear(r->right);
        free(r);
    }
}
//Randon inserction
Nodo *insertTree(Nodo *r,char data,int size)
{

    if(!r){

        Nodo *aux = (Nodo *) malloc(sizeof (Nodo));
        aux->data = data;
        aux->left = NULL;
        aux->right = NULL;
        aux->fb = 0;
        aux->h=0;
        return aux;
    }else{
        if(r->data == data)
            return r;

        if(size%2){
            r->left = insertTree(r->left,data,size-1);
        }else{
            r->right = insertTree(r->right,data,size-2);
        }
    }

    return r;
}

// Insertion is bigger in right smaller in left
Nodo *searchTree(Nodo *r,char data)
{
    if(!r){
        Nodo *aux = (Nodo *) malloc(sizeof (Nodo));
        aux->data = data;
        aux->left = NULL;
        aux->right = NULL;
        return aux;
    }else{
        if(data < r->data){
            r->left = searchTree(r->left,data);
        }else if (data > r->data){
            r->right = searchTree(r->right,data);
        }
    }

    return r;
}
//fish insecions

// Percurssion prefix(r,left,right)/infix(left,root,right)/postfix(left,right,root)
void infixTree(Nodo *r)
{
    if(r){
        infixTree(r->left);
        printf("%i ",r->data);
        infixTree(r->right);
    }
}

void prefixTree(Nodo *r)
{
    if(r){
        printf("%i ",r->data);
        prefixTree(r->left);
        prefixTree(r->right);
    }
}

void postfixTree(Nodo *r)
{
    if(r){

        postfixTree(r->left);
        postfixTree(r->right);
        printf("%i ",r->data);
    }
}

void ReinfixTree(Nodo *r)
{
    if(r){
        ReinfixTree(r->right);
        printf("%i ",r->data);
        ReinfixTree(r->left);
    }
}

void nestedparentheses(Nodo *r)
{
    if(r)
    {
        printf("%i",r->data);
        if(r->left || r->right)
        {
            printf("(");
            nestedparentheses(r->left);
            if(r->right)
                printf(",");
            nestedparentheses(r->right);
            printf(")");
        }
    }
}

//all percussions

//Key-independent standard functions

//height the tree(binary or screat)
int height(Nodo *r)
{
    if(!r)
        return -1;
    int hl,hr;
    hl = height(r->left);
    hr = height(r->right);
    return hl>hr?1+hl:hr+1;
}

//Number of nodes em Tree
int NumberNodes(Nodo *r)
{
    if(r){
        return 1 + NumberNodes(r->left) + NumberNodes(r->right);
    }
    return 0;
}

//leaves nodes em Tree
int leavesNodes(Nodo *r)
{
    if(r){
        if(!(r->right || r->left)){
            return 1;
        }else{
            return leavesNodes(r->right) + leavesNodes(r->left);
        }
    }
    return 0;
}

//not leaves nodes em Tree
int notleavesNodes(Nodo *r)
{
    if(r){
        if(!(r->right || r->left)){
            return 0;
        }else{
            return 1 + notleavesNodes(r->right) + notleavesNodes(r->left);
        }
    }
    return 0;
}

// this a degenerate tree
int isdegeneratetree(Nodo *r)
{
    if(r){
        if(r->left && r->right)
            return 0;

        if(!(r->right || r->left))
            return 1;

        return isdegeneratetree(r->left)* isdegeneratetree(r->right);
    }
    return 1;
}

// if a search tree
int ifsearchtree(Nodo *r)
{
    if(r){
        if((r->left?(r->left->data < r->data):1) && (r->right?(r->right->data > r->data):1))
            return 1*ifsearchtree(r->right)* ifsearchtree(r->left);
        else
            return 0;
    }
    return 1;
}

// add height and balancing factor by node
void handbfbynode(Nodo *r)
{
    if(r){
        r->h = height(r);
        r->fb = height(r->right) - height(r->left);
        handbfbynode(r->left);
        handbfbynode(r->right);
    }
}

void prinfhandfbbynode(Nodo *r)
{
    if(r){
        printf("\n%i height: %i balancing factor: %i",r->data,r->h,r->fb);
        prinfhandfbbynode(r->left);
        prinfhandfbbynode(r->right);
    }
}

//it's an AVL?
int itavl(Nodo *r)
{
    if(r)
    {
        if(abs(r->fb) < 2)
            return 1* itavl(r->left)* itavl(r->right);
        return 0;
    }
    return 1;
}

//reverse left right side
void esrever(Nodo *r)
{
    if(r)
    {
        Nodo *aux=(Nodo *) malloc(sizeof (Nodo));
        aux = r->right;
        r->right = r->left;
        r->left = aux;
        esrever(r->left);
        esrever(r->right);
    }
    return;
}

//in nivel printf
void printLevel(Nodo *r, int l) {
    if (r) {
        if (l == r->h)
            printf("%i ", r->data);
        printLevel(r->right, l);
        printLevel(r->left, l);
    }

}

void printLevelOrder(Nodo *r)
{
    int h = height(r);
    for (int i = h; i >= 0 ; i--) {
        printLevel(r, i);
    }
}


// finish comun functions.
#endif