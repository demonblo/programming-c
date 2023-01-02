#include "header.h"

//Функция, создающая список и выделяющая под него память
list_t *allocate_list()
{
    list_t *lt = (list_t*)malloc(sizeof(list_t));
    lt->head = (element_t*)malloc(sizeof (element_t));
    lt->length = 0;

    return lt;
}

//Добавление элемента в список
element_t *list_push(list_t *lt, element_t *pointer, char *surname, int data, char *group, int size, int second_size)
{
    element_t *elem = (element_t*)malloc(sizeof(element_t));
    elem->surname = (char*)malloc(sizeof (char) * size);
    elem->group = (char*)malloc(sizeof (char) * second_size);
    char *first_pointer_surname = surname, *second_pointer_surname = elem->surname;
    char *first_pointer_group = group, *second_pointer_group = elem->group;
    int i;

    for (i = 0; i < size; i++, first_pointer_surname++, second_pointer_surname++)
        *second_pointer_surname = *first_pointer_surname;

    for (i = 0; i < second_size; first_pointer_group++, second_pointer_group++, i++)
        *second_pointer_group = *first_pointer_group;

    elem->size_of_surname = size;
    elem->size_of_group = second_size;
    elem->year = data;
    elem->next = NULL;
    pointer->next = elem;
    lt->length++;
    pointer = elem;

    return pointer;
}

//Считываем данные для элемента записи
element_t *input_info(list_t *main_list, element_t *pointer, FILE *fl)
{
    char *cur_group_b, *cur_group, *cur_group_e, symb;
    char *cur_surname_b, *cur_surname, *cur_surname_e;
    char surname_mass[50];
    char group_mass[10];
    int i, size, data;
    int second_size;

    i = 0;
    while (i < 50)
    {
        if (fscanf(fl, "%c", &symb) != 1)
        {
            if (main_list->length == 0)
                printf("Некорректный ввод!\n");
            return NULL;
        }
        if (symb == ' ' || symb == '\n')
        {
            if (i == 0 )
            {
                printf("Некорректный ввод!\n");
                return NULL;
            }
            break;
        }
        if ((symb > 'z') || (symb > 'Z' && symb < 'a') || (symb < 'A'))
        {
            printf("Некорректный ввод!\n");
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
    fscanf(fl, "%d", &data);
    fscanf(fl, "%c", &symb);
    //Считываем группу студента
    for (i = 0; i < 10; i++)
    {
        second_size = i;
        if (fscanf(fl, "%c", &symb) != 1)
        {
            printf("Некорректный ввод!\n");
            free(cur_surname_b);
            return NULL;
        }
        if (symb == ' ' || symb == '\n')
        {
            if (i == 0)
            {
                printf("Некорректный ввод!\n");
                free(cur_surname_b);
                return NULL;
            }
            break;
        }
        group_mass[i] = symb;
    }
    cur_group_b = (char*)malloc(sizeof (char) * second_size);
    cur_group = cur_group_b;
    cur_group_e = cur_group_b + second_size;

    for (i = 0; cur_group < cur_group_e; cur_group++, i++)
        *cur_group = group_mass[i];

    pointer = list_push(main_list, pointer, cur_surname_b, data, cur_group_b, size, second_size);
    free(cur_surname_b);
    free(cur_group_b);

    return pointer;
}

void output_info(element_t *pointer)
{
    char *point_group = pointer->group;
    char *point_surname = pointer->surname;

    for (int i = 0; i < pointer->size_of_surname; i++, point_surname++)
        printf("%c", *point_surname);
    printf("\n");
    printf("%d\n", pointer->year);
    for (int i = 0; i < pointer->size_of_group; i++, point_group++)
        printf("%c", *point_group);
    printf("\n");
}

//Выводим данные о списке
void output_list(list_t *main_list, element_t *pointer)
{
    int i = 0;
    pointer = main_list->head->next;
    while (i < main_list->length)
    {
        output_info(pointer);
        pointer = pointer->next;
        i++;
    }
}

void free_elem_of_list(element_t *pointer)
{
    free(pointer->group);
    free(pointer->surname);
}

void free_main_list(list_t *main_list)
{
    element_t *first_pointer, *second_pointer;
    int i;

    while (main_list->length > 1)
    {
        first_pointer = main_list->head->next;
        for (i = 1; i < main_list->length - 1; i++)
            first_pointer = first_pointer->next;

        second_pointer = first_pointer;
        first_pointer = first_pointer->next;
        free_elem_of_list(first_pointer);
        second_pointer->next = NULL;
        main_list->length--;
    }
    free_elem_of_list(main_list->head->next);
    free(main_list->head);
    free(main_list);
}

void remove_surnames(list_t *main_list)
{
    element_t *prev_pointer = main_list->head;
    element_t *pointer = main_list->head->next;
    element_t *second_pointer = pointer->next, *lol = pointer, *potential_next;
    int flag = 0;

    while (second_pointer != NULL)
    {
        potential_next = second_pointer->next;
        if (!strcmp(pointer->surname, second_pointer->surname))
        {
            flag = 1;
            if (pointer->next == second_pointer)
                pointer->next = second_pointer->next;
            else
                pointer->next = pointer->next;
            potential_next = second_pointer->next;
            free_elem_of_list(second_pointer);
            main_list->length -= 1;
        }
        if (!flag)
            lol = second_pointer;
        second_pointer = potential_next;
    }

    if (flag)
    {
        prev_pointer->next = pointer->next;
        free_elem_of_list(pointer);
        main_list->length--;
    }
}
