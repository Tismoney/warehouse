#include <stdio.h>
#include <stdlib.h>

typedef int elem_t;

typedef struct
{
    elem_t* name;
    int data;
    int size;
} stack;

	//Function of changed size of the stack
void stack_resize(stack* st)
{
    st -> size = 2*st -> size;
    st -> name = (elem_t*) realloc (st -> name, 2*(st -> size));
    if (st -> name == NULL)
    	printf("Cannot alocated memory\n");
}

	//Function of check status of the stack
	//return 
int stack_ok(stack* st)
{
    return !((st == NULL) || (st -> name == NULL) || (st -> data < 0) || (st -> size <= 0));
}

	//Function of added element
int push(stack* st, elem_t a)
{
    if (stack_ok(st))
    {
        if (st -> data  == st -> size)
            stack_resize(st);
        st -> name[st -> data] = a;
        st -> data++ ;
        return 0;
    }
    else
    {
        printf("You will not work with incorrect stack\n");
        return 0;
    }
}

	//Function of deleted element
elem_t pop(stack* st)
{
    if (st -> data == 0)
        printf("Underflow stack\n");
    else
        st -> data--;
    return st -> name[st -> data];
}

	//Function of made stack
void stack_ctor(stack* st, int n)
{
    st -> name = (elem_t*) calloc (n, sizeof(elem_t));
    st -> size = n;
    st -> data = 0;
}

	//Function of deleted all stack
void stack_dtor(stack* st)
{
    int i = 0;
    if(stack_ok(st))
        for(i = 0; i < st -> data; i++)
           st -> name[i] = 0xBAD;
    else
        exit(0);
    free(st -> name);
    st -> name = NULL;
    st -> size = 0;
    st -> data = -1;
}

	//Function of printed stack
void stack_dump(stack* st)
{
    if (stack_ok(st))
    {
        int i = st -> data;
        (st -> data) --;
        for (; (st -> data) >= 0 ; (st -> data)--)
            printf("a[%d] = %d\n", st -> data , st -> name[st -> data]);
        st -> data = i;
        printf("\n");
    }
    else
      printf("You will not work with incorrect stack\n");
}
