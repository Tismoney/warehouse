#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>

typedef char elem_t;

typedef struct
{
    elem_t* name;
    int data;
    int size;
} stack;

int push(stack* st, elem_t a);
	//Function of added element

elem_t pop(stack* st);
	//Function of deleted element

void stack_resize(stack* st);
	//Function of changed size of the stack

void stack_ctor(stack* st, int n);
	//Function of made stack

void stack_dtor(stack* st);
	//Function of deleted all stack

int stack_ok(stack* st);
	//Function of check status of the stack

void stack_dump(stack* st);
	//Function of printed stack


#endif // STACK_H_INCLUDED
