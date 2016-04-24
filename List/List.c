#include "List.h"

ERRORS ERROR = 0;         //Перемеенная для отслеживания текущего положения элемента, чтобы корректно обрабатывать ошибки
int buff_int[100];        //Место под хранения элементов типа integer
char buff_char[100];      //Место под хранения элементов типа char
double buff_double[100];  //Место под хранения элементов типа double


plist list_ctor(void* ptr, char type)
    //Эта функция создает элемент списка, записывая в него данные ptr и type
{
    plist List = (plist) malloc (sizeof(list));
    List -> next = NULL;
    List -> prev = NULL;
    List -> pointer = ptr;
    List -> type = type;
    return List;
}


void list_dtor(plist List)
    //Эта функция удаляет все данные из списка и разрывает свзяь между элементами из списка
{
    plist tmp;
    CheckOk(List)
    while (ERROR == No_ERRORS || ERROR == You_work_with_last_element)
        //Переводим указатель на первый элемент
    {
        List = List -> prev;
        CheckOk(List);
    }
    while (ERROR == You_work_with_first_element)
        //Удаляем первый элемент и переводим указатель на следующий
    {
        tmp = List -> next;
        free(List);
        tmp -> prev = NULL;
        List = tmp;
        CheckOk(List);
    }
    if (ERROR == You_work_with_one_element)
        //При работе с единственным элементом просто его удаляем
        free(List);
}

plist list_next(plist List)
    //Эта функция переводит указатель на следующий элемент в списке, если это возможно.
    //Если фнкция работает с последним элементом, она вернет тот же указатель, а ERROR установит на "работу с последним элементом"
{
    CheckOk(List)
    if (ERROR == No_ERRORS || ERROR == You_work_with_first_element)
            List = List -> next;
    return List;
}
plist list_prev(plist List)
    //Эта функция переводит указатель на предыдуший элемент в списке, если это возможно.
    //Если фнкция работает с первым элементом, она вернет тот же указатель, а ERROR установит на "работу с первым элементом"
{
    CheckOk(List)
    if (ERROR == No_ERRORS || ERROR == You_work_with_last_element)
            List = List -> prev;
    return List;
}

int push_next(plist List, void* ptr, char type)
    //Эта функция добавляет в элемент списка с данными ptr после элемента List
    //Функция возращает 0 если удалось положить в список, и -1 если нет
{
    CheckOk(List)
    if (ERROR != You_work_with_NULL_element)
    {
        plist new_List = list_ctor(ptr, type);
        plist tmp = List -> next;
        List -> next = new_List;
        new_List -> prev = List;
        new_List -> next = tmp;
        if (tmp != NULL)
            tmp -> prev = new_List;
        return 0;
    }
    else
        return -1;
}

int push_prev(plist List, void* ptr, char type)
    //Эта функция добавляет в элемент списка с данными ptr до элемента List
    //Функция возращает 0, если удалось положить в список, и -1, если нет
{
    CheckOk(List)
    if (ERROR != You_work_with_NULL_element)
    {
        plist new_List = list_ctor(ptr, type);
        plist tmp = List -> prev;
        List -> prev = new_List;
        new_List -> next = List;
        new_List -> prev = tmp;
        if (tmp != NULL)
            tmp -> next = new_List;
        return 0;
    }
    else
        return -1;
}

plist pop_now(plist List)
    //Эта функция убирает из списка элемент List, и переводи указатель на предыдуший элемент
    //Если функция работает с первым элементом или с единственным, она устанавливает ERROR в соответсвующее положение и ничего не изменяет
{
    CheckOk(List)
    if (ERROR == No_ERRORS || ERROR == You_work_with_last_element)
    {
        List -> prev -> next = List -> next;
        if (List -> next != NULL)
            List -> next -> prev = List -> prev;
        plist tmp = List;
        List = List -> prev;
        free(tmp);
    }
    return List;
}

plist pop_next(plist List)
    //Эта функция убирает из списка следущий элемент после List
    //Если функция работает с последним элементом или с единсвтенным, она устанавливает ERROR в соответсвующее положение и ничего не изменяет
{
    CheckOk(List)
    if (ERROR == No_ERRORS || ERROR == You_work_with_first_element)
    {
        plist tmp = List -> next;
        List -> next = tmp -> next;
        if (tmp -> next)
            tmp -> next -> prev = List;
        free(tmp);
    }
    return List;
}

plist pop_prev(plist List)
    //Эта функция убирает из списка предыдущий элемент после List
    //Если функция работает с первым элементом или с единственным, она устанавливает ERROR нв соответсвующее положение и ничего не изменяет
{
    CheckOk(List)
    if (ERROR == No_ERRORS || ERROR == You_work_with_last_element)
    {
        plist tmp = List -> prev;
        List -> prev = tmp -> prev;
        if (tmp -> prev != NULL)
            tmp -> next = List;
        free(tmp);
    }
    return List;
}

void list_dump(plist List)
    //Эта функция печатает весь сущетсвующий список
    //Элемент, на котором вы находитесь в данным момент записывается в []
{
    CheckOk(List)
    if (ERROR != You_work_with_NULL_element)
    {
        int yet = 0; //Переменная, которая хранит номер элемента, указатель которого был передан
        int now = 0; //Переменная, которая хранит номер текущего элемента
        plist test = List;
        while(test -> prev != NULL)
        {
            test = test -> prev;
            yet++;
        }
        printf("    NULL <-> ");
        while(test != NULL)
        {
            switch(test -> type)
            {
                case 'd':
                    if (now == yet)
                        printf("[%d] <-> ", *(int*)(test -> pointer));
                    else 
                        printf("%d <-> ", *(int*)(test -> pointer));
                    break;
                case'c':
                    if (now == yet)
                        printf("[%c] <-> ", *(char*)(test -> pointer));
                    else 
                        printf("%c <-> ", *(char*)(test -> pointer));
                    break;
                case 'l':
                    if (now == yet)
                        printf("[%lg] <-> ", *(double*)(test -> pointer));
                    else 
                        printf("%lg <-> ", *(double*)(test -> pointer));
                    break;
            }
            test = test -> next;
            now++;
        }
        printf("NULL\n");
    }
}


void list_run(plist List)
    //Эта функция работает со списком в реальном времени
    //Существует набор команд, которые можно посмотреть при вводе h
{
    char to_do;          //Переменная для команд
    char tp;             //Переменная для типа вводимых данных
    int num_int = 0;     //Номер элемент из buff_int
    int num_double = 0;  //Номер элемент из buff_double
    int num_char = 0;    //Номер элемент из buff_char
    for(to_do = getchar(); to_do != 'q'; to_do = getchar())
    {
        if (to_do == 'g')
        {
            to_do = getchar();
            if (to_do == 'n')
                List = list_next(List);
            if (to_do == 'p')
                List = list_prev(List);
        }
        else if (to_do == 'p')
        {
            to_do = getchar();
            if (to_do == 'n')
            {
                getchar(); //Считываем пробел 
                tp = getchar();
                switch(tp)
                {
                    case 'd':
                        getchar(); 
                        scanf("%d", &buff_int[num_int]);
                        push_next(List, (void*)(buff_int + num_int), tp);
                        num_int++;
                        break;
                    case 'c':
                        getchar();
                        scanf("%c", &buff_char[num_char]);// buff_char[num_char] = skip();
                        push_next(List, ((void*)(buff_char + num_char)), tp);
                        num_char++;
                        break;
                    case 'l':
                        getchar();
                        scanf("%lg", &buff_double[num_double]);
                        push_next(List, ((void*)(buff_double + num_double)), tp);
                        num_double++;
                        break;
                }
            }
            if (to_do == 'p')
            {
                getchar(); //Считываем пробел
                tp = getchar();
                switch(tp)
                {
                    case 'd':
                        getchar();
                        scanf("%d", &buff_int[num_int]);
                        push_prev(List, (void*)(buff_int + num_int), tp);
                        num_int++;
                        break;
                    case 'c':
                        getchar();
                        scanf("%c", &buff_char[num_char]);
                        push_prev(List, ((void*)(buff_char + num_char)), tp);
                        num_char++;
                        break;
                    case 'l':
                        getchar();
                        scanf("%lg", &buff_double[num_double]);
                        push_prev(List, ((void*)(buff_double + num_double)), tp);
                        num_double++;
                        break;
                }
            }
        }
        else if (to_do == 'd')
        {
            to_do = getchar();
            if (to_do == 't')
                List = pop_now(List);
            if (to_do == 'n')
                List = pop_next(List);
            if (to_do == 'p')
                List = pop_prev(List);
        }
        else if (to_do == 's')
        {
            list_dump(List);
        }
        else if (to_do == 'e')
        {
            CheckOk(List)
            printf("    ERROR = %d\n", ERROR);
        }
        else if (to_do == 'h')
        {
            printf("Comands:\n");
            printf("    gn  Переводит указатель на следущий элемент\n");
            printf("    gp  Переводит указатель на предыдуший элемент\n");
            printf("    pn  <тип> <значение>  Кладет в список после текущим элементом\n");
            printf("    pp  <тип> <значение>  Кладет в список перед текущим элементом\n");
            printf("          d    integer\n");
            printf("          c    char\n");
            printf("          l    double\n");
            printf("    dt  Удаляет текущий элемент\n");
            printf("    dn  Удаляет следущий элемент\n");
            printf("    dp  Удаляет предыдуший элемент\n");
            printf("    e   Показывает значение ERROR\n");
            printf("    s   Печатает список полностью\n");
            printf("    q   Выходит из программы\n");
            printf("    h   Список всех команд\n");
        }
    }
}
