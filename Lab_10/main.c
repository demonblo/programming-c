#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"

#define OK                        0
#define EMPTY                    -1
#define NOT_FOUND                -2
#define LENGTH_ERRORR            -3
#define INPUT_ERROR              -4

int main()
{
    list_t *main_list;
    info_t *pointer, *cur_pointer;

    main_list = allocate_list();
    pointer = main_list->head;
    /*printf("Вводите записи в формате:\n");
    printf("1)Дата в виде DD.MM.YYYY\n");
    printf("2)Фамилия Латинскими заглавными и прописными\n");
    printf("3)Количество измерений и их значения\n");
    printf("Пример:\n");
    printf("02.02.1993 Bloknin 3 3.2 4 -2\n");
    printf("Окончанием ввода служит дата 00.00.0000\n");*/
    while (1)
    {
        cur_pointer = pointer;
        cur_pointer = input_info(main_list, pointer);
        if (pointer == cur_pointer)
        {
            //printf("Конец ввода...\n");
            break;
        }
        else if (cur_pointer == NULL)
        {
            printf("Конец ввода...\n");
            //Очищаем память
            free_main_list(main_list);
            return INPUT_ERROR;
        }
        pointer = cur_pointer;
        if (getchar() != '\n')
        {
            printf("Некорректный ввод!\n");
            printf("Конец ввода...\n");
            //Очищаем память
            free_main_list(main_list);
            return INPUT_ERROR;
        }
    }

    if (main_list->size == 0)
    {
        //Очищаем память
        free(main_list->head);
        free(main_list);
        return INPUT_ERROR;
    }
    //printf("Таблица после ввода:\n");
    //output_list(main_list, pointer);
    //Удаляем элементы до тех пор (если необходимо) пока первый элемент не будет удовлетворять условию
    //Эксперимент позже 1 февраля 1993 года
    pointer = main_list->head->next;
    if (main_list->size == 1 && check_date_for_late(pointer->date))
    {
        free_elem_of_list(pointer);
        free(main_list->head);
        free(main_list);
        return EMPTY;
    }
    else if (main_list->size == 1 && !(check_date_for_late(pointer->date)))
    {
        output_list_in_file(main_list, pointer);
        //Очищаем память
        free_elem_of_list(pointer);
        free(main_list->head);
        free(main_list);
        return OK;
    }
    while (check_date_for_late(pointer->date) && main_list->size > 1)
    {
        special_switch(main_list);
        pointer = main_list->head->next;
    }
    if (main_list->size == 0)
    {
        printf("Список пуст!\n");
        free(main_list->head);
        free(main_list);
        return EMPTY;
    }
    getchar();
    pointer = main_list->head->next;
    //Удаляем все эксперименты который были сделаны не позже 1 февраля 1993 года
    if (main_list->size == 2 || main_list->size > 4)
        remove_old_readings(main_list);
    if (main_list->size == 3)
        remove_old_readings_for_three(main_list);
    if (main_list->size == 4)
        remove_old_readings_for_four(main_list);
    if (main_list->size == 1 && check_date_for_late(pointer->date))
    {
        printf("Список пуст!\n");
        free_elem_of_list(pointer);
        free(main_list->head);
        free(main_list);
        return EMPTY;
    }
    if (main_list->size == 1 && !(check_date_for_late(pointer->date)))
    {
        printf("Остался один элемент:\n");
        output_list(main_list, pointer);
        printf("Сортировка не требуется.\n");
        output_list_in_file(main_list, pointer);
        //Очищаем память
        free_elem_of_list(pointer);
        free(main_list->head);
        free(main_list);
        return OK;
    }
    //printf("Таблица после удаления:\n");
    //output_list(main_list, pointer);
    //Сортировка
    //printf("Введите ключ сортировки (DATE/TECHNICIAN/DATA):");
    if (sort_by_key(main_list))
    {
        free_main_list(main_list);
        return INPUT_ERROR;
    }
    //printf("Таблица после сортировки:\n");
    //output_list(main_list, pointer);
    //Выводим результат в файл result.txt
    output_list_in_file(main_list, pointer);
    //Очищаем память
    free_main_list(main_list);

    return OK;
}

