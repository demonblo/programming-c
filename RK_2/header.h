#ifndef HEADER_H
#define HEADER_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define INPUT_ERROR   -1

#endif // HEADER_H

//Структура элемента списка
typedef struct element_s
{
    struct element_s *next;
    char *surname;
    int year;
    char *group;
    int size_of_surname;
    int size_of_group;
} element_t;

//Структура списка
typedef struct list_s
{
    element_t *head;
    int length;
} list_t;

list_t *allocate_list(void);
element_t *list_push(list_t *lt, element_t *pointer, char *surname, int data, char *group, int size, int second_size);
element_t *input_info(list_t *main_list, element_t *pointer, FILE *fl);
void output_info(element_t *pointer);
void output_list(list_t *main_list, element_t *pointer);
void free_elem_of_list(element_t *pointer);
void free_main_list(list_t *main_list);
void remove_surnames(list_t *main_list);
