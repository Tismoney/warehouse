#include <iostream>
#include <cassert>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include "cstack.h"

using namespace std;

int CStack::counter = 0;

CStack::CStack():
    data_{},
    size_(0)
    {
        ++counter;
        if(counter > 3)
            {
                cout << "You have already made 5 stacks.\nAre you sure want to make more?\nEnter password.. ";
                char* password = new char[100];
                cin >> password;
                if(strcmp("Angel1963\0", password))
                    {
                        cout << "You enter incoorect password";
                        exit(-1);
                    }
            }

    }

CStack::~CStack()
{
    int i;
    for(i = 0; i < size_; i++)
        data_[i] = 0x0BAD;
    size_ = -1;
    counter--;
}

int CStack::Ok()
{
    if(size_ >= 0 && size_ <= MAX_SIZE)
        return 1;
    else
        return 0;
}

void CStack::Dump()
{
    if(Ok() == 0)
         cout << "Stack is incoorect";
    else
    {
        int i;
        for(i = 0; i < size_; i++)
            cout << data_[i] << " ";
        cout << endl;
    }
}

void CStack::Push(int val)
{
    if(Ok() == 0)
         cout << "Stack is incoorect";
    else
    {
        data_[size_] = val;
        size_++;
    }
}

int CStack::Pop()
{
    if(Ok() == 0)
    {
         cout << "Stack is incoorect";
         return 0x0BAD;
    }
    else
    {
        int tmp = data_[size_ - 1];
        data_[--size_] = 0x0BAD;
        return tmp;
    }
}