#ifndef CSTACK_H
#define CSTACK_H

const int MAX_SIZE = 32;


class CStack
{
    private:
        int* data_;
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

#endif 