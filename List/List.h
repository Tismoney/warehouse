#ifndef LIST_H
#define LIST_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CheckNull(Lst) ERROR = (!Lst) ? You_work_with_NULL_element : ERROR;
#define CheckLast(Lst) ERROR = (!Lst -> next) ? You_work_with_last_element : ERROR;
#define CheckFirst(Lst) ERROR = (!Lst -> prev) ? You_work_with_first_element : ERROR;
#define CheckOne(Lst) ERROR = ((ERROR != 4) && (!Lst -> next) && (!Lst -> prev)) ? You_work_with_one_element : ERROR;
#define CheckNorm(Lst) ERROR = ((!Lst) || (!Lst -> next) || (!Lst -> prev)) ? ERROR : No_ERRORS;
#define CheckOk(Lst) CheckNull(Lst) CheckLast(Lst) CheckFirst(Lst) CheckOne(Lst) CheckNorm(Lst) 

typedef enum ERRORS
{
    No_ERRORS ,
    You_work_with_first_element,
    You_work_with_last_element,
    You_work_with_NULL_element,
    You_work_with_one_element
} ERRORS;

typedef struct list_
{
    void* pointer;
    char type;
    struct list_* next;
    struct list_* prev;
}list, *plist;

plist list_ctor(void* ptr, char type);
    //Эта функция создает элемент списка, записывая в него данные ptr и type
void list_dtor(plist List);
    //Эта функция удаляет все данные из списка и разрывает свзяь между элементами из списка

plist list_next(plist List);
    //Эта функция переводит указатель на следующий элемент в списке, если это возможно.
    //Если фнкция работает с последним элементом, она вернет тот же указатель, а ERROR установит на "работу с последним элементом"
plist list_prev(plist List);
    //Эта функция переводит указатель на предыдуший элемент в списке, если это возможно.
    //Если фнкция работает с первым элементом, она вернет тот же указатель, а ERROR установит на "работу с первым элементом"

int push_next(plist List, void* ptr, char type);
    //Эта функция добавляет в элемент списка с данными ptr после элемента List
    //Функция возращает 0 если удалось положить в список, и -1 если нет
int push_prev(plist List, void* ptr, char type);
    //Эта функция добавляет в элемент списка с данными ptr до элемента List
    //Функция возращает 0, если удалось положить в список, и -1, если нет

plist pop_now(plist List);
    //Эта функция убирает из списка элемент List, и переводи указатель на предыдуший элемент
    //Если функция работает с первым элементом или с единственным, она устанавливает ERROR в соответсвующее положение и ничего не изменяет
plist pop_next(plist List);
    //Эта функция убирает из списка следущий элемент после List
    //Если функция работает с последним элементом или с единсвтенным, она устанавливает ERROR в соответсвующее положение и ничего не изменяет
plist pop_prev(plist List);
    //Эта функция убирает из списка предыдущий элемент после List
    //Если функция работает с первым элементом или с единственным, она устанавливает ERROR нв соответсвующее положение и ничего не изменяет

void list_void(plist List);
    //Эта функция печатает весь сущетсвующий список
    //Элемент, на котором вы находитесь в данным момент записывается в []

void list_run(plist List);
    //Эта функция работает со списком в реальном времени
    //Существует набор команд, которые можно посмотреть при вводе h
#endif
