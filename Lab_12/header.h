#ifndef HEADER_H
#define HEADER_H
#include <stdio.h>
#include <stdlib.h>
#define INPUT_ERROR   -1

#endif // HEADER_H

//Структура элемента списка
typedef struct element_s
{
    struct element_s *next;
    int simple_number;
    int power_of_simple_number;
} element_t;

//Структура списка
typedef struct list_s
{
    element_t *head;
    int length;
} list_t;

//Выделение памяти под число
list_t *allocate_list(void);
//Перевод числа из int в связный список
void input_number(list_t *first_number, long int first_int_number);
//Вывод числа
void output_list(list_t *list);
//Совобождение памяти из под списка
void free_list(list_t *list);
//Проверка числа на то, является ли оно простым или нет
int check_for_simpliness(int number);
//Ищем степень просто в числа в заданном числе
int power_of_simpliness(long int number, int i);
//Возведение числа в квадрат
void square_number(list_t *list);
//Умножение двух чисел
void numbers_multiplication(list_t *first_number, list_t *second_number);
//Деление без остатка
int number_division(list_t *first_number, list_t *second_number);
