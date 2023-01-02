#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"

#define OK                        0
#define EMPTY                    -1
#define NOT_FOUND                -2
#define LENGTH_ERRORR            -3
#define INPUT_ERROR              -4

//Функция, создающая список и выделяющая под него память
list_t *allocate_list()
{
    list_t *lt = (list_t*)malloc(sizeof(list_t));
    lt->head = (info_t*)malloc(sizeof (info_t));
    lt->size = 0;

    return lt;
}

//Функция дополнения следующего элемента в список
info_t *list_push(list_t *lt, info_t *pointer, double data, char *date, char *surname, int size, int count)
{
    info_t *elem = (info_t*)malloc(sizeof(info_t));
    elem->date = (char*)malloc(sizeof (char) * 10);
    elem->surname = (char*)malloc(sizeof (char) * size);
    elem->size_of_surname = size;
    char *first_pointer_date = date, *second_pointer_date = elem->date;
    char *first_pointer_surname = surname, *second_pointer_surname = elem->surname;
    int i;

    for (i = 0; i < 10; i++)
    {
        *second_pointer_date = *first_pointer_date;
        first_pointer_date++;
        second_pointer_date++;
    }

    for (i = 0; i < size; i++, first_pointer_surname++, second_pointer_surname++)
        *second_pointer_surname = *first_pointer_surname;

    //Добавляем данные элемента
    elem->reading = data;
    elem->count_of_readings = count;
    //Так как элемент добавляется в конец, указываем следующим элементом адрес tail(NULL)
    elem->next = NULL;
    //делаем так, чобы предыдущий элемент указывал на этот элемент
    pointer->next = elem;
    //Увеличиваем размер листа
    lt->size++;
    //Двигаем "каретку"
    pointer = elem;

    return pointer;
}

//Проверяем, является ли введенная дата, призанком окончания ввода
int check_date(char *cur_date)
{
    int flag = 0, i;

    for (i = 0; i < 10; cur_date++, i++)
    {
        if ((i == 0 || i == 1 || i == 3 ||
            i == 4 || i == 6 || i == 7 ||
            i == 8 || i == 9) && *cur_date == '0')
            flag = 1;
        else if ((i == 0 || i == 1 || i == 3 ||
            i == 4 || i == 6 || i == 7 ||
            i == 8 || i == 9) && *cur_date != '0')
        {
            flag = 0;
            break;
        }
    }

    return flag;
}

//Проверяем, дата рыньше 1 февраля 1993 (функция возвращает 1) или позже (функция возвращает 0)
int check_date_for_late(char *cur_date)
{
    int day = 0, month = 0, year = 0;
    int flag = 0, i;

    for (i = 0; i < 10; cur_date++, i++)
    {
        if (i == 0)
            day += ((int)*cur_date - 48) * 10;
        if (i == 1)
            day += (int)*cur_date - 48;
        if (i == 3)
            month += ((int)*cur_date - 48) * 10;
        if (i == 4)
            month += (int)*cur_date - 48;
        if (i == 6)
            year += ((int)*cur_date - 48) * 1000;
        if (i == 7)
            year += ((int)*cur_date - 48) * 100;
        if (i == 8)
            year += ((int)*cur_date - 48) * 10;
        if (i == 9)
            year += (int)*cur_date - 48;
    }

    if ((year == 1993 && month == 2 && day == 1)
        || (year == 1993 && month < 2)
        || (year < 1993))
        flag = 1;

    return flag;
}

//Проверяем дату на корректность
int check_date_for_correct(char *cur_date)
{
    int day = 0, month = 0, year = 0;
    int flag = 0, i;

    for (i = 0; i < 10; cur_date++, i++)
    {
        if (i == 0)
            day += ((int)*cur_date - 48) * 10;
        if (i == 1)
            day += (int)*cur_date - 48;
        if (i == 3)
            month += ((int)*cur_date - 48) * 10;
        if (i == 4)
            month += (int)*cur_date - 48;
        if (i == 6)
            year += ((int)*cur_date - 48) * 1000;
        if (i == 7)
            year += ((int)*cur_date - 48) * 100;
        if (i == 8)
            year += ((int)*cur_date - 48) * 10;
        if (i == 9)
            year += (int)*cur_date - 48;
    }

    if (day > 31 || day < 1 || month > 12 || month < 1 || year < 1)
        flag = 1;
    if (day > 30 && (month == 4 || month == 6 || month == 9 ||
        month == 11))
        flag = 1;
    if (month == 2)
    {
        if (year % 4 == 0 && day > 29)
            flag = 1;
        if (year % 4 != 0 && day > 28)
            flag = 1;
    }

    return flag;
}

//Считываем данные для элемента записи
info_t *input_info(list_t *main_list, info_t *pointer)
{
    char *cur_date_b, *cur_date, *cur_date_e, symb;
    char *cur_surname_b, *cur_surname, *cur_surname_e;
    char surname_mass[256];
    char error_check;
    int count_of_readings;
    double reading, sum_reading = 0;

    int i, size;

    cur_date_b = (char*)malloc(sizeof (char) * 10);
    cur_date = cur_date_b;
    cur_date_e = cur_date_b + 10;
    //Считываем дату эксперимента
    for (i = 0; cur_date < cur_date_e; cur_date++, i++)
    {
        if (!scanf("%c", &symb))
        {
            printf("Некорректный ввод!\n");
            free(cur_date_b);
            return NULL;
        }
        if ((symb > '9' && symb != '.') || (symb < '0' && symb != '.'))
        {
            printf("Некорректный ввод!\n");
            free(cur_date_b);
            return NULL;
        }
        if ((i == 2 || i == 5) && (symb != '.'))
        {
            printf("Некорректный ввод!\n");
            free(cur_date_b);
            return NULL;
        }
        if ((i != 2 && i != 5) && (symb == '.'))
        {
            printf("Некорректный ввод!\n");
            free(cur_date_b);
            return NULL;
        }
        *cur_date = symb;
    }

    //Проверка на конец ввода
    cur_date = cur_date_b;
    if (check_date(cur_date))
    {
        free(cur_date_b);
        return pointer;
    }
    getchar();//Удаляем пробел/переход на новую строку
    //Считываем фамилию
    cur_date = cur_date_b;
    if (check_date_for_correct(cur_date))
    {
        printf("Некорректный ввод!\n");
        free(cur_date_b);
        return NULL;
    }
    i = 0;
    while (i < 256)
    {
        if (!scanf("%c", &symb))
        {
            printf("Некорректный ввод!\n");
            free(cur_date_b);
            return NULL;
        }
        if (symb == ' ' || symb == '\n')
        {
            if (i == 0)
            {
                printf("Некорректный ввод!\n");
                free(cur_date_b);
                return NULL;
            }
            break;
        }
        if ((symb > 'z') || (symb > 'Z' && symb < 'a') || (symb < 'A'))
        {
            printf("Некорректный ввод!\n");
            free(cur_date_b);
            return NULL;
        }
        surname_mass[i] = symb;
        i++;
        size = i;
    }

    cur_surname_b = (char*)malloc(sizeof (char) * size);
    cur_surname_e = cur_surname_b + size;
    cur_surname = cur_surname_b;

    for (i = 0; cur_surname < cur_surname_e; cur_surname++, i++)
        *cur_surname = surname_mass[i];

    //Считываем эксперименты
    if (!scanf("%d", &count_of_readings))
    {
        printf("Некорректный ввод!\n");
        free(cur_date_b);
        free(cur_surname_b);
        return NULL;
    }
    if (count_of_readings <= 0)
    {
        printf("Некорректный ввод!\n");
        free(cur_date_b);
        free(cur_surname_b);
        return NULL;
    }
    scanf("%c", &error_check);
    if (error_check != ' ' && error_check != '\n')
    {
        printf("Некорректный ввод!\n");
        free(cur_date_b);
        free(cur_surname_b);
        return NULL;
    }
    for (i = 0; i < count_of_readings; i++)
    {
        if (!scanf("%lf", &reading))
        {
            printf("Некорректный ввод!\n");
            free(cur_date_b);
            free(cur_surname_b);
            return NULL;
        }
        sum_reading += reading;
    }

    sum_reading /= count_of_readings;
    pointer = list_push(main_list, pointer, sum_reading, cur_date_b, cur_surname_b, size, count_of_readings);
    free(cur_date_b);
    free(cur_surname_b);

    return pointer;
}

//Выводим данные об элементе
void output_info(info_t *pointer)
{
    char *point_date = pointer->date;
    char *point_surname = pointer->surname;

    for (int i = 0; i < 10; i++, point_date++)
        printf("%c", *point_date);

    printf(" ");
    for (int i = 0; i < pointer->size_of_surname; i++, point_surname++)
    {
        printf("%c", *point_surname);
    }

    printf(" ");
    printf("%d ", pointer->count_of_readings);
    printf("%lf", pointer->reading);
    printf("\n");
}

//Выводим данные о списке
void output_list(list_t *main_list, info_t *pointer)
{
    pointer = main_list->head->next;
    while (pointer != NULL)
    {
        output_info(pointer);
        pointer = pointer->next;
    }
}

//Выводим данные об элементе в файл
void output_info_in_file(info_t *pointer, FILE *fp)
{
    char *point_date = pointer->date;
    char *point_surname = pointer->surname;

    for (int i = 0; i < 10; i++, point_date++)
        fprintf(fp, "%c", *point_date);

    fprintf(fp, "\n");
    for (int i = 0; i < pointer->size_of_surname; i++, point_surname++)
    {
        fprintf(fp, "%c", *point_surname);
    }

    fprintf(fp, "\n%d ", pointer->count_of_readings);
    fprintf(fp, "%lf", pointer->reading);
    fprintf(fp, "\n");
}

//Выводим данные о списке в файл
void output_list_in_file(list_t *main_list, info_t *pointer)
{
    FILE *fp = fopen("result.txt", "w");
    pointer = main_list->head->next;
    while (pointer != NULL)
    {
        output_info_in_file(pointer, fp);
        pointer = pointer->next;
    }
    fclose(fp);
}

//Освобождаем память из под элемента списка
void free_elem_of_list(info_t *pointer)
{
    free(pointer->date);
    free(pointer->surname);
    free(pointer);
}

//Меняем местами два последующих элемента списка
void switch_places_of_next_elements(info_t *pointer)
{
    info_t *first_cur_pointer, *second_cur_pointer;

    first_cur_pointer = pointer->next;
    pointer->next = first_cur_pointer->next;
    second_cur_pointer = pointer->next;
    first_cur_pointer->next = second_cur_pointer->next;
    second_cur_pointer->next = first_cur_pointer;
}

//Удаляем первый элемент списка до тех пор, пок он не будет удовылетворять условиям
void special_switch(list_t *main_list)
{
    info_t *first_cur_pointer, *second_cur_pointer, *pointer;
    int i = 1;

    pointer = main_list->head;
    first_cur_pointer = pointer->next;
    pointer->next = first_cur_pointer->next;
    second_cur_pointer = pointer->next;
    first_cur_pointer->next = second_cur_pointer->next;
    second_cur_pointer->next = first_cur_pointer;
    pointer = main_list->head->next;
    while (i < main_list->size - 1)
    {
        switch_places_of_next_elements(pointer);
        pointer = pointer->next;
        i++;
    }

    first_cur_pointer = pointer;
    pointer = pointer->next;
    free_elem_of_list(pointer);
    first_cur_pointer->next = NULL;
    main_list->size--;
}

//Удаляем записи которые были сделаны не позже 1 февраля 1993 года
//Не трогай
void remove_old_readings(list_t *main_list)
{
    info_t *first_pointer = main_list->head->next;
    info_t *pointer_for_delete, *second_pointer = first_pointer;
    int i = 2, j, counter_of_removes = 0, flag = 1;

    //Определяем количество элементов которые необходимо удалить и убираем их в конец
    while (i < main_list->size - 2)
    {
        if (check_date_for_late(first_pointer->next->date))
        {
            j = i;
            pointer_for_delete = first_pointer;
            while (j < main_list->size)
            {
                switch_places_of_next_elements(pointer_for_delete);
                pointer_for_delete = pointer_for_delete->next;
                j++;
            }
            counter_of_removes++;
            flag = 0;
        }
        if (flag == 1)
        {
            first_pointer = first_pointer->next;
            i++;
        }
        else
            flag = 1;
    }

    //Удаляем элементы с конца
    while (counter_of_removes > 0)
    {
        //Доходим до последнего элемента
        first_pointer = main_list->head->next;
        for (i = 1; i < main_list->size - 1; i++)
            first_pointer = first_pointer->next;

        //Делаем предпоследний элемент последним, а тот, который раньше был последним, удаляем
        second_pointer = first_pointer;
        first_pointer = first_pointer->next;
        free_elem_of_list(first_pointer);
        second_pointer->next = NULL;
        main_list->size--;
        counter_of_removes--;
    }

    //Если последний элемент остался неправильным
    first_pointer = main_list->head->next;
    for (i = 1; i < main_list->size - 1; i++)
        first_pointer = first_pointer->next;

    second_pointer = first_pointer;
    first_pointer = first_pointer->next;
    if (check_date_for_late(first_pointer->date))
    {
        free_elem_of_list(first_pointer);
        second_pointer->next = NULL;
        main_list->size--;
        counter_of_removes--;
    }
}

//Удаляем записи которые были сделаны не позже 1 февраля 1993 года
//Не трогай
void remove_old_readings_for_three(list_t *main_list)
{
    info_t *first_pointer = main_list->head->next;
    info_t *second_pointer = first_pointer->next, *cur_pointer;
    int counter_of_removes = 0, i;

    if (check_date_for_late(second_pointer->date))
    {
        cur_pointer = second_pointer->next;
        first_pointer->next = second_pointer->next;
        second_pointer->next = cur_pointer->next;
        cur_pointer->next = second_pointer;
        counter_of_removes++;
    }

    //Удаляем элементы с конца
    while (counter_of_removes > 0)
    {
        //Доходим до последнего элемента
        first_pointer = main_list->head->next;
        for (i = 1; i < main_list->size - 1; i++)
            first_pointer = first_pointer->next;

        //Делаем предпоследний элемент последним, а тот, который раньше был последним, удаляем
        second_pointer = first_pointer;
        first_pointer = first_pointer->next;
        free_elem_of_list(first_pointer);
        second_pointer->next = NULL;
        main_list->size--;
        counter_of_removes--;
    }

    //Если последний элемент остался неправильным
    first_pointer = main_list->head->next;
    for (i = 1; i < main_list->size - 1; i++)
        first_pointer = first_pointer->next;

    second_pointer = first_pointer;
    first_pointer = first_pointer->next;
    if (check_date_for_late(first_pointer->date))
    {
        free_elem_of_list(first_pointer);
        second_pointer->next = NULL;
        main_list->size--;
        counter_of_removes--;
    }
}

//Удаляем записи которые были сделаны не позже 1 февраля 1993 года
//Не трогай
void remove_old_readings_for_four(list_t *main_list)
{
    info_t *first_pointer = main_list->head->next;
    info_t *second_pointer = first_pointer->next, *cur_pointer;
    int counter_of_removes = 0, i;

    if (check_date_for_late(second_pointer->date))
    {
        cur_pointer = second_pointer->next;
        first_pointer->next = second_pointer->next;
        second_pointer->next = cur_pointer->next;
        cur_pointer->next = second_pointer;
        counter_of_removes++;
        //повторяем
        first_pointer = first_pointer->next;
        second_pointer = first_pointer->next;
        cur_pointer = second_pointer->next;
        first_pointer->next = second_pointer->next;
        second_pointer->next = cur_pointer->next;
        cur_pointer->next = second_pointer;
    }
    first_pointer = main_list->head->next;
    second_pointer = first_pointer->next;
    if (counter_of_removes == 1)
    {
        if (check_date_for_late(second_pointer->date))
        {
            cur_pointer = second_pointer->next;
            first_pointer->next = second_pointer->next;
            second_pointer->next = cur_pointer->next;
            cur_pointer->next = second_pointer;
            counter_of_removes++;
        }
    }
    else if (counter_of_removes == 0)
    {
        first_pointer = first_pointer->next;
        second_pointer = first_pointer->next;
        if (check_date_for_late(second_pointer->date))
        {
            cur_pointer = second_pointer->next;
            first_pointer->next = second_pointer->next;
            second_pointer->next = cur_pointer->next;
            cur_pointer->next = second_pointer;
            counter_of_removes++;
        }
    }

    //Удаляем элементы с конца
    while (counter_of_removes > 0)
    {
        //Доходим до последнего элемента
        first_pointer = main_list->head->next;
        for (i = 1; i < main_list->size - 1; i++)
            first_pointer = first_pointer->next;

        //Делаем предпоследний элемент последним, а тот, который раньше был последним, удаляем
        second_pointer = first_pointer;
        first_pointer = first_pointer->next;
        free_elem_of_list(first_pointer);
        second_pointer->next = NULL;
        main_list->size--;
        counter_of_removes--;
    }

    //Если последний элемент остался неправильным
    first_pointer = main_list->head->next;
    for (i = 1; i < main_list->size - 1; i++)
        first_pointer = first_pointer->next;

    second_pointer = first_pointer;
    first_pointer = first_pointer->next;
    if (check_date_for_late(first_pointer->date))
    {
        free_elem_of_list(first_pointer);
        second_pointer->next = NULL;
        main_list->size--;
        counter_of_removes--;
    }
}

//Сравнение DATA
int compare_data(info_t *first, info_t *second)
{
    if (second->reading > first->reading)
        return 1;
    else
        return 0;
}

//Сравнение 2 дат, ф-ия возвращяет 1 если первая дата должна стоять в отсортированном списке выше и 0 если наоборот
int compare_date(info_t *first, info_t *second)
{
    char *first_date = first->date, *second_date = second->date;
    char *cur_date;
    int first_days = 0, first_months = 0, first_years = 0;
    int second_days = 0, second_months = 0, second_years = 0;
    int i = 0, j = 0;

    cur_date = first_date;
    while (i < 10)
    {
        if (i == 0)
            first_days += *cur_date * 10;
        if (i == 1)
            first_days += *cur_date;
        if (i == 3)
            first_months += *cur_date * 10;
        if (i == 4)
            first_months += *cur_date;
        if (i == 6)
            first_years += *cur_date * 1000;
        if (i == 7)
            first_years += *cur_date * 100;
        if (i == 8)
            first_years += *cur_date * 10;
        if (i == 9)
            first_years += *cur_date;
        i++;
        cur_date++;
    }

    cur_date = second_date;
    while (j < 10)
    {
        if (j == 0)
            second_days += *cur_date * 10;
        if (j == 1)
            second_days += *cur_date;
        if (j == 3)
            second_months += *cur_date * 10;
        if (j == 4)
            second_months += *cur_date;
        if (j == 6)
            second_years += *cur_date * 1000;
        if (j == 7)
            second_years += *cur_date * 100;
        if (j == 8)
            second_years += *cur_date * 10;
        if (j == 9)
            second_years += *cur_date;
        j++;
        cur_date++;
    }

    if (second_years > first_years)
        return 1;
    else if (second_years == first_years)
    {
        if (second_months > first_months)
            return 1;
        else if (second_months == first_months)
        {
            if (second_days > first_days)
                return 1;
            else
                return 0;
        }
        else if (second_months < first_months)
            return 0;
    }
    else if (second_years < first_years)
        return 0;

    return 0;
}

//Сравнение 2 фамилий, ф-ия возвращяет 1 если первая фамилия должна стоять в отсортированном списке выше и 0 если наоборот
int compare_surnames(info_t *first, info_t *second)
{
    char *first_surname = first->surname, *second_surname = second->surname;
    char *first_pointer = first_surname, *second_pointer = second_surname;

    while ((((*first_pointer <= 'z') && (*first_pointer >= 'a')) || ((*first_pointer <= 'Z') && (*first_pointer >= 'A')))
        && (((*second_pointer <= 'z') && (*second_pointer >= 'a')) || ((*second_pointer <= 'Z') && (*second_pointer >= 'A'))))
    {
        if (*first_pointer < *second_pointer)
            return 1;
        else if (*first_pointer > *second_pointer)
            return 0;
        else
        {
            first_pointer++;
            second_pointer++;
        }
    }
    if (!(((*first_pointer <= 'z') && (*first_pointer >= 'a')) || ((*first_pointer <= 'Z') && (*first_pointer >= 'A')))
        && (((*second_pointer <= 'z') && (*second_pointer >= 'a')) || ((*second_pointer <= 'Z') && (*second_pointer >= 'A'))))
        return 1;
    else
        return 0;
}

//Сортировка списка
void insert_sort(list_t *main_list, int (*compare)(info_t *first, info_t *second))
{
    info_t *first_pointer = main_list->head->next, *second_pointer = first_pointer;
    info_t *min_pointer = first_pointer, *cur_pointer_one, *cur_pointer_two, *pointer = main_list->head;

    while (first_pointer->next != NULL)
    {
        while (second_pointer->next != NULL)
        {
            if (compare(second_pointer->next, min_pointer))
            {
                cur_pointer_two = second_pointer;
                min_pointer = second_pointer->next;
            }
            second_pointer = second_pointer->next;
        }
        //Если следующий элемент меньше нынешнего
        if (first_pointer->next == min_pointer)
        {
            if (first_pointer != min_pointer)
            {
                pointer->next = min_pointer;
                cur_pointer_one = min_pointer->next;
                min_pointer->next = first_pointer;
                first_pointer->next = cur_pointer_one;
            }
        }
        else
        {
            //Если меньший элемент не находится сразу за нынешним
            if (first_pointer != min_pointer)
            {
                pointer->next = min_pointer;
                cur_pointer_one = min_pointer->next;
                min_pointer->next = first_pointer->next;
                first_pointer->next = cur_pointer_one;
                cur_pointer_two->next = first_pointer;
            }
        }
        pointer = min_pointer;
        first_pointer = min_pointer->next;
        second_pointer = first_pointer;
        min_pointer = first_pointer;
    }
}

//Сортировка списка по ключу
int sort_by_key(list_t *main_list)
{
    char *key, *key_pointer, symb, counter;

    //Ввод ключа
    if (!scanf("%c", &symb))
    {
        printf("Некорректный ввод!\n");
        return INPUT_ERROR;
    }
    if (symb == 'D')
    {
        counter = 2;
        key = (char*)malloc(sizeof (char) * 4);
        key_pointer = key;
        while (symb != ' ' && symb != '\n')
        {
            if (!scanf("%c", &symb))
            {
                printf("Некорректный ввод!\n");
                free(key);
                return INPUT_ERROR;
            }
            if (symb == ' ' || symb == '\n')
                break;
            if (counter == 2 && symb != 'A')
            {
                printf("Некорректный ввод!\n");
                free(key);
                return INPUT_ERROR;
            }
            if (counter == 3 && symb != 'T')
            {
                printf("Некорректный ввод!\n");
                free(key);
                return INPUT_ERROR;
            }
            *key_pointer = symb;
            key_pointer++;
            counter++;
        }
        if (counter != 5)
        {
            printf("Некорректный вводlol!\n");
            free(key);
            return INPUT_ERROR;
        }
        key_pointer--;
        if (*key_pointer == 'A')
            insert_sort(main_list, compare_data);
        else if (*key_pointer == 'E')
            insert_sort(main_list, compare_date);
        else
        {
            printf("Некорректный ввод!\n");
            free(key);
            return INPUT_ERROR;
        }
        free(key);
    }
    else if (symb == 'T')
    {
        counter = 1;
        key = (char*)malloc(sizeof (char) * 10);
        key_pointer = key;
        while (symb != ' ' && symb != '\n')
        {
            if (!scanf("%c", &symb))
            {
                printf("Некорректный ввод!\n");
                free(key);
                return INPUT_ERROR;
            }
            counter++;
            if (symb == ' ' || symb == '\n')
                break;
            if (counter == 2 && symb != 'E')
            {
                printf("Некорректный ввод!\n");
                free(key);
                return INPUT_ERROR;
            }
            if (counter == 3 && symb != 'C')
            {
                printf("Некорректный ввод!\n");
                free(key);
                return INPUT_ERROR;
            }
            if (counter == 4 && symb != 'H')
            {
                printf("Некорректный ввод!\n");
                free(key);
                return INPUT_ERROR;
            }
            if (counter == 5 && symb != 'N')
            {
                printf("Некорректный ввод!\n");
                free(key);
                return INPUT_ERROR;
            }
            if (counter == 6 && symb != 'I')
            {
                printf("Некорректный ввод!\n");
                free(key);
                return INPUT_ERROR;
            }
            if (counter == 7 && symb != 'C')
            {
                printf("Некорректный ввод!\n");
                free(key);
                return INPUT_ERROR;
            }
            if (counter == 8 && symb != 'I')
            {
                printf("Некорректный ввод!\n");
                free(key);
                return INPUT_ERROR;
            }
            if (counter == 9 && symb != 'A')
            {
                printf("Некорректный ввод!\n");
                free(key);
                return INPUT_ERROR;
            }
            if (counter == 10 && symb != 'N')
            {
                printf("Некорректный ввод!\n");
                free(key);
                return INPUT_ERROR;
            }
            *key_pointer = symb;
            key_pointer++;
        }
        if (counter != 11)
        {
            printf("Некорректный ввод!\n");
            free(key);
            return INPUT_ERROR;
        }
        insert_sort(main_list, compare_surnames);
        free(key);
    }
    else
    {
        printf("Некорректный ввод!\n");
        return INPUT_ERROR;
    }

    return 0;
}

//Освобождаем память из под списка
void free_main_list(list_t *main_list)
{
    info_t *first_pointer, *second_pointer;
    int i;

    while (main_list->size > 1)
    {
        first_pointer = main_list->head->next;
        for (i = 1; i < main_list->size - 1; i++)
            first_pointer = first_pointer->next;

        second_pointer = first_pointer;
        first_pointer = first_pointer->next;
        free_elem_of_list(first_pointer);
        second_pointer->next = NULL;
        main_list->size--;
    }
    free_elem_of_list(main_list->head->next);
    free(main_list->head);
    free(main_list);
}
