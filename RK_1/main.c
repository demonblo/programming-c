#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CHARS 100
#define STOP       -2

typedef struct info_s
{
    char *surname;
    int surname_size;
    char *name;
    int name_size;
    int number;
} info_t;

info_t *allocate_elem(info_t *pointer, char *cur_surname_b, int surname_size, char *cur_name_b, int name_size, int number)
{
    char *cur_surname = cur_surname_b;
    char *cur_name = cur_name_b;
    pointer = (info_t*)malloc(sizeof (info_t));
    char *surname = (char*)malloc(sizeof (char) * surname_size);
    char *name = (char*)malloc(sizeof (char) * name_size);
    char *target_surname = surname;
    char *target_name = name;
    int i;

    i = 0;
    while (i < surname_size)
    {
        *target_surname = *cur_surname;
        target_surname++;
        cur_surname++;
        i++;
    }

    i = 0;
    while (i < name_size)
    {
        *target_name = *cur_name;
        target_name++;
        cur_name++;
        i++;
    }
    pointer->surname = surname;
    pointer->surname_size = surname_size;
    pointer->name = name;
    pointer->name_size = name_size;
    pointer->number = number;

    return pointer;
}

info_t *input_info(info_t *pointer, FILE *fp)
{
    char *cur_surname_b, *cur_surname, *cur_surname_e, symb;
    char surname_mass[MAX_CHARS];
    char *cur_name_b, *cur_name, *cur_name_e;
    char name_mass[MAX_CHARS];
    int i, surname_size, name_size, number;

    i = 0;
    while (i < MAX_CHARS)
    {
        if (!fscanf(fp, "%c", &symb))
        {
            printf("Некорректный ввод!\n");
            return NULL;
        }
        if (symb == '\n')
        {
            if (i == 0)
                return pointer;
            break;
        }
        if ((symb > 'z') || (symb > 'Z' && symb < 'a') || (symb < 'A'))
        {
            printf("Некорректный ввод!\n");
            return NULL;
        }
        surname_mass[i] = symb;
        i++;
        surname_size = i;
    }

    cur_surname_b = (char*)malloc(sizeof (char) * surname_size);
    cur_surname_e = cur_surname_b + surname_size;
    cur_surname = cur_surname_b;

    for (i = 0; cur_surname < cur_surname_e; cur_surname++, i++)
        *cur_surname = surname_mass[i];

    i = 0;
    while (i < MAX_CHARS)
    {
        if (!fscanf(fp, "%c", &symb))
        {
            printf("Некорректный ввод!\n");
            return NULL;
        }
        if (symb == '\n')
        {
            if (i == 0)
                return NULL;
            break;
        }
        if ((symb > 'z') || (symb > 'Z' && symb < 'a') || (symb < 'A'))
        {
            printf("Некорректный ввод!\n");
            return NULL;
        }
        name_mass[i] = symb;
        i++;
        name_size = i;
    }

    cur_name_b = (char*)malloc(sizeof (char) * name_size);
    cur_name_e = cur_name_b + name_size;
    cur_name = cur_name_b;

    for (i = 0; cur_name < cur_name_e; cur_name++, i++)
        *cur_name = name_mass[i];
    i = 0;

    //Считываем эксперименты
    if (!fscanf(fp, "%d", &number))
    {
        printf("Некорректный ввод!\n");
        return NULL;
    }
    fgetc(fp);
    if (number < 0)
    {
        printf("Некорректный ввод!\n");
        return NULL;
    }
    pointer = allocate_elem(pointer, cur_surname_b, surname_size, cur_name_b, name_size, number);
    free(cur_surname_b);
    free(cur_name_b);

    return pointer;
}

void free_list(info_t *main_list, int length)
{
    info_t *pointer = main_list;
    int i;

    while (length > 1)
    {
        i = 1;
        while (i < length)
        {
            pointer++;
            i++;
        }
        free(pointer->surname);
        free(pointer->name);
        pointer = main_list;
        i++;
        length--;
    }
    free(pointer->surname);
    free(pointer->name);
    free(main_list);
}

int check_surname(info_t *pointer, char *sub_string, unsigned long length)
{
    char *surname = pointer->surname;
    char *symb = sub_string;
    unsigned long i = 0;

    if (pointer->surname_size < length)
        return 1;
    while (i < length)
    {
        if (*surname != *symb)
            return 1;
        surname++;
        symb++;
        i++;
    }

    return 0;
}

void output_element(info_t *pointer)
{
    char *surname = pointer->surname;
    char *name = pointer->name;
    int i;

    i = 0;
    while (i < pointer->surname_size)
    {
        printf("%c", *surname);
        surname++;
        i++;
    }
    printf(" ");

    i = 0;
    while (i < pointer->name_size)
    {
        printf("%c", *name);
        name++;
        i++;
    }
    printf(" ");

    printf("%d", pointer->number);
    printf("\n");
}

//ВАРИАНТ 4
int main(int argc, char **argv)
{
    info_t *main_list;
    info_t *pointer, *cur_pointer;
    char cur_kek[100];
    int size = 1;
    int counts_of_elements = 0;
    unsigned long length;
    int counter = 0;
    FILE * fp = fopen(argv[2], "r");

    while (fgets(cur_kek, 100, fp))
        counts_of_elements++;

    counts_of_elements /= 3;
    fclose(fp);
    fp = fopen(argv[2], "r");
    main_list = (info_t*)malloc(sizeof (info_t) * counts_of_elements);
    pointer = main_list;
    if (argc != 4)
    {
        printf("Некорректный ввод!\n");
        return -1;
    }
    while (1)
    {
        cur_pointer = pointer;
        cur_pointer = input_info(cur_pointer, fp);
        if (cur_pointer == pointer)
            break;
        else
            *pointer = *cur_pointer;
        pointer++;
    }
    size = counts_of_elements;

    pointer = main_list;
    int i = 0;
    length = strlen(argv[3]);

    printf("Пользователи с удовлетворяющими фамилиями:\n");
    while (i < size)
    {
        if (!check_surname(pointer, argv[3], length))
        {
            output_element(pointer);
            counter++;
        }
        pointer++;
        i++;
    }
    if (counter == 0)
        printf("Пользователей с удовлетворяющими фамилиями нет!\n");


    fclose(fp);
    free_list(main_list, size);

    return 0;
}
