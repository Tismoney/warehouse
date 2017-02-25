#ifndef TREE_CULC_H_INCLUDED
#define TREE_CULC_H_INCLUDED

typedef struct tree
{
    int prior;                                  ////Prioretet operation { 0 - number, 1 - '*' and '/'}
    char sign;
    int val;
    struct tree* left;
    struct tree* right;
} tree, *ptree;

ptree tree_add(ptree TREE, tree n);             //Function of addition element in tree
int tree_culc(ptree TREE);                      //Function of culculates elements in tree
void tree_print(ptree TREE, int tab);           //Function of show a tree
ptree tree_build(ptree TREE);                   //Function of build a tree


#endif // TREE_CULC_H_INCLUDED
