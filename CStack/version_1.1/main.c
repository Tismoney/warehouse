#include <iostream>
#include <cassert>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include "cstack.h"


int main()
{
    CStack MyStack, MyStack1;

    MyStack.Push(10);
    MyStack.Dump();
    MyStack.Push(15);
    MyStack.Dump();
    MyStack.Pop();
    MyStack.Dump();
    return 0;
}
