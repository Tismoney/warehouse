#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>
#include <stdbool.h>
#include "tree_culc.h"


int main(void)
{
    ptree TREE = NULL;
    TREE = tree_build(TREE);                             //Enter the expression with a '=' in the end
    printf("Result: %d\n", tree_culc(TREE));
}
