#include <iostream>
#include <cassert>
#include <cstring>
#include <cstdlib>
#include <cstdio>

using namespace std;
const int MAX_SIZE = 32;

class CStack
{
    private:
        int data_[MAX_SIZE];
        int size_;
        static int counter;
        int Ok();
    public:
        CStack();
        ~CStack();
        void Push(int val);
        int Pop();
        void Dump();
};

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
