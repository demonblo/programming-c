#ifndef HEADER_H
#define HEADER_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#endif // HEADER_H

//Структура одного элемента связного списка
typedef struct info_s
{
    struct info_s *next;
    char *date;
    char *surname;
    int size_of_surname;
    double reading;
    int count_of_readings;
} info_t;

//Структура самого списка
typedef struct list_s
{
    int size;
    info_t *head;
} list_t;

//Функция, создающая список и выделяющая под него память
list_t *allocate_list(void);
//Функция дополнения следующего элемента в список
info_t *list_push(list_t *lt, info_t *pointer, double data, char *date, char *surname, int size, int count);
//Проверяем, является ли введенная дата, призанком окончания ввода
int check_date(char *cur_date);
//Проверяем, дата рыньше 1 февраля 1993 (функция возвращает 1) или позже (функция возвращает 0)
int check_date_for_late(char *cur_date);
//Проверяем дату на корректность
int check_date_for_correct(char *cur_date);
//Считываем данные для элемента записи
info_t *input_info(list_t *main_list, info_t *pointer);
//Выводим данные об элементе
void output_info(info_t *pointer);
//Выводим данные о списке
void output_list(list_t *main_list, info_t *pointer);
//Выводим данные об элементе в файл
void output_info_in_file(info_t *pointer, FILE *fp);
//Выводим данные о списке в файл
void output_list_in_file(list_t *main_list, info_t *pointer);
//Освобождаем память из под элемента списка
void free_elem_of_list(info_t *pointer);
//Меняем местами два последующих элемента списка
void switch_places_of_next_elements(info_t *pointer);
//Удаляем первый элемент списка до тех пор, пок он не будет удовылетворять условиям
void special_switch(list_t *main_list);
//Удаляем записи которые были сделаны не позже 1 февраля 1993 года
//Не трогай
void remove_old_readings(list_t *main_list);
void remove_old_readings_for_three(list_t *main_list);
void remove_old_readings_for_four(list_t *main_list);
//Сравнение DATA
int compare_data(info_t *first, info_t *second);
//Сравнение 2 дат, ф-ия возвращяет 1 если первая дата должна стоять в отсортированном списке выше и 0 если наоборот
int compare_date(info_t *first_date, info_t *second_date);
//Сравнение 2 фамилий, ф-ия возвращяет 1 если первая фамилия должна стоять в отсортированном списке выше и 0 если наоборот
int compare_surnames(info_t *first_date, info_t *second_date);
//Сортировка списка
void insert_sort(list_t *main_list, int (*compare)(info_t *first, info_t *second));
//Сортировка списка по ключу
int sort_by_key(list_t *main_list);
//Освобождаем память из под списка
void free_main_list(list_t *main_list);
