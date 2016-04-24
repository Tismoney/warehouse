#include "List.h"
#include <stdio.h>
#include <stdlib.h>


int main()
{
    int a = 0;
    plist List = list_ctor((void*)&a, 'd'); // Создаем список с нулевым элементом
    list_run(List);                         // Запускает работу с листом (при работе пропиши h)
    list_dtor(List);
    return 0;
}


