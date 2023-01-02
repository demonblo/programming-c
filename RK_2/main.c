#include "header.h"

int main(int argc, char **argv)
{
    list_t *main_list;
    element_t *pointer, *cur_pointer;
    char symb;
    FILE *fl = fopen(argv[1], "r");
    int size;
    //Проверки файла
    if (fl == NULL)
    {
        printf("Файл не существует!\n");
        return INPUT_ERROR;
    }
    else
    {
        fseek (fl, 0, SEEK_END);
        size = ftell(fl);
        if (0 == size)
        {
            printf("EMPTY FILE\n");
            return INPUT_ERROR;
        }
    }
    fseek (fl, 0, SEEK_SET);
    //Проверка командной строки
    if (argc != 2)
    {
        printf("Неверные параметры командной строки!\n");
        return INPUT_ERROR;
    }

    main_list = allocate_list();
    pointer = main_list->head;
    while (1)
    {
        cur_pointer = pointer;
        cur_pointer = input_info(main_list, pointer, fl);
        if (pointer == cur_pointer)
        {
            //printf("Конец ввода...\n");
            break;
        }
        else if (cur_pointer == NULL)
        {
            if (main_list->length >= 1)
            {
                printf("Конец считывания...\n");
                //Очищаем память
                //free_main_list(main_list);
                break;
            }
            else if (main_list->length == 0)
            {
                printf("Некорректный ввод!\n");
                free(main_list->head);
                free(main_list);
                printf("Конец считывания...\n");
                return INPUT_ERROR;
            }
        }
        pointer = cur_pointer;
        //удаляем переход на новую строку
        fscanf(fl, "%c", &symb);
    }
    printf("Первоначальный список:\n");
    output_list(main_list, pointer);
    printf("Список после удаления однофамильцев:\n");
    remove_surnames(main_list);
    output_list(main_list, pointer);
    free_main_list(main_list);

    return 0;
}
