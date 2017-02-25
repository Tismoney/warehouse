#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>
#include <stdbool.h>
#include "tree_culc.h"

ptree tree_add(ptree TREE, tree n)
{
    if(n.prior == 0)                                                      //If addition is number
    {
        if(TREE == NULL)                                                  //If tree is empty
        {
            ptree new_node = (ptree) malloc (sizeof(tree));
            new_node->prior = n.prior;
            new_node->val = n.val;
            new_node->sign = '^';
            new_node->left = NULL;
            new_node->right = NULL;
            return new_node;
        }
        else
        {
            TREE->right = tree_add(TREE->right, n);
            return TREE;
        }

    }
    else                                                                   //If addition sign
    {
        if(TREE == NULL)
        {
            ptree new_node = (ptree) malloc (sizeof(tree));
            new_node->prior = n.prior;
            new_node->val = n.val;
            new_node->sign = n.sign;
            new_node->left = NULL;
            new_node->right = NULL;
            return new_node;
        }
        else
        {
            if(n.prior < TREE->prior)                                      //If prioretet of operation less
            {
                ptree new_node = (ptree) malloc (sizeof(tree));
                new_node->prior = n.prior;
                new_node->val = n.val;
                new_node->sign = n.sign;                                   //then right stuff a addition
                new_node->left = TREE->right;
                new_node->right = NULL;
                TREE->right = new_node;
                return TREE;
            }
            else                                                           //If prioretet of operation more
            {
                ptree new_node = (ptree) malloc (sizeof(tree));
                new_node->prior = n.prior;
                new_node->val = n.val;
                new_node->sign = n.sign;                                   //then go up
                new_node->left = TREE;
                new_node->right = NULL;
                return new_node;
            }
        }
    }
    return TREE;
};

int tree_culc(ptree TREE)
{
    if(TREE->prior == 0)
        return TREE->val;
    else
    {
        if(TREE->sign == '+')
            return tree_culc(TREE->left) + tree_culc(TREE->right);
        if(TREE->sign == '-')
            return tree_culc(TREE->left) - tree_culc(TREE->right);
        if(TREE->sign == '*')
            return tree_culc(TREE->left) * tree_culc(TREE->right);
        if(TREE->sign == '/')
            return tree_culc(TREE->left) / tree_culc(TREE->right);
    }
    return 0;
}

void tree_print(ptree TREE, int tab)
{
    if(TREE != NULL)
    {
        int i = 0;
        tree_print(TREE->left, tab + 1);
        for(i = 0; i < tab; i++) printf("  ");
        printf("prior=%d sign=%c val=%d\n", TREE->prior, TREE->sign, TREE->val);
        tree_print(TREE->right, tab + 1);
    }
}

ptree tree_build(ptree TREE)
{
    char ch;                                                                              //The current character read
    char chl = '*';                                                                       //The latter is considered a symbol
    int zn = 1;                                                                           //The variable to sign
    int x = 0;
    while(1)
    {
        scanf("%c", &ch);
        if(ch == '=')
        {
            tree new_node = {0, '^', zn * x};
            TREE = tree_add(TREE, new_node);
            x = 0;
            break;
        }
        if(isdigit(ch))
        {
            x = x * 10 + ((int)ch - 48);                                                  //Read numbers
        }
        else
        {

            if(ch == '*' || ch == '/')                                                    //Рang in a tree X, and after the sign
            {
                tree new_node = {0, '^', zn * x};
                TREE = tree_add(TREE, new_node);
                tree new_node1 = {1, ch, 0};
                TREE = tree_add(TREE, new_node1);
                x = 0;                                                                    //Reset Х and Zn
                zn = 1;
            }
            if(ch == '+')                                                                 //Similarly to other priorities
            {
                tree new_node = {0, '^', zn * x};
                TREE = tree_add(TREE, new_node);
                tree new_node1 = {2, ch, 0};
                TREE = tree_add(TREE, new_node1);
                x = 0;
                zn = 1;
            }
            if(ch == '-')                                                                 //Analysis on unary
            {
                if(chl >= '0' && chl <= '9')                                              //If the normal, by analogy
                {
                    tree new_node = {0, '^', zn * x};
                    TREE = tree_add(TREE, new_node);
                    tree new_node1 = {2, ch, 0};
                    TREE = tree_add(TREE, new_node1);
                    x = 0;
                    zn = 1;
                }
                else                                                                      //If the unary, change a sign
                {
                    zn = -1;
                }
            }
        }
        chl = ch;
    }
    //tree_print(TREE, 0);
    return TREE;
}
