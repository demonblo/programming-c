#include "header.h"

list_t *allocate_list()
{
    list_t *list = (list_t*)malloc(sizeof (list_t));

    list->head = NULL;
    list->length = 0;

    return list;
}

void input_number(list_t *first_number, long int first_int_number)
{
    element_t *pointer = first_number->head, *pointer_for_malloc = NULL;
    int power;
    long int first_proizv = 1;

    for (int i = 2; i <= first_int_number; i++)
    {
        if (check_for_simpliness(i))
        {
            power = power_of_simpliness(first_int_number, i);
            pointer_for_malloc = (element_t*)malloc(sizeof (element_t));
            if (first_number->length < 1)
            {
                first_number->head = pointer_for_malloc;
                first_number->head->simple_number = i;
                first_number->head->power_of_simple_number = power;
                first_number->head->next = NULL;
                pointer_for_malloc = NULL;
                pointer = first_number->head;
                first_number->length++;
            }
            else
            {
                pointer->next = pointer_for_malloc;
                pointer = pointer->next;
                pointer->simple_number = i;
                pointer->power_of_simple_number = power;
                pointer_for_malloc = NULL;
                pointer->next = NULL;
                first_number->length++;
            }
            for (int j = 0; j < power; j++)
                first_proizv *= i;
        }
        if (first_proizv == first_int_number)
            break;
    }
}
void output_list(list_t *list)
{
    element_t *pointer = list->head;

    while (pointer != NULL)
    {
        printf("|%d, %d|", pointer->simple_number, pointer->power_of_simple_number);
        pointer = pointer->next;
    }
    printf("\n");
}

void free_list(list_t *list)
{
    element_t *pointer = list->head, *prev_pointer = list->head;

    while (list->length > 1)
    {
        for (int i = 0; i < list->length - 1; i++)
        {
            prev_pointer = pointer;
            pointer = pointer->next;
        }

        prev_pointer->next = NULL;
        free(pointer);
        pointer = list->head;
        list->length--;
    }

    free(list->head);
    free(list);
}

int check_for_simpliness(int number)
{
    for (int i = 2; i < number; i++)
    {
        if (number % i == 0)
            return 0;
    }

    return 1;
}

int power_of_simpliness(long int number, int i)
{
    long int cur_number = number;
    int power = 0;

    while (1)
    {
        if (cur_number % i == 0)
        {
            power++;
            cur_number /= i;
        }
        else
            break;
    }

    return power;
}

void square_number(list_t *list)
{
    element_t *pointer = list->head;

    for (int i = 0; i < list->length; i++)
    {
        pointer->power_of_simple_number *= 2;
        pointer = pointer->next;
    }
}

void numbers_multiplication(list_t *first_number, list_t *second_number)
{
    element_t *first_pointer = first_number->head, *second_pointer = second_number->head;

    if (first_number->length >= second_number->length)
        while (second_pointer != NULL)
        {
            first_pointer->power_of_simple_number += second_pointer->power_of_simple_number;
            first_pointer = first_pointer->next;
            second_pointer = second_pointer->next;
        }
    else
        while (first_pointer != NULL)
        {
            second_pointer->power_of_simple_number += first_pointer->power_of_simple_number;
            first_pointer = first_pointer->next;
            second_pointer = second_pointer->next;
        }
}

int number_division(list_t *first_number, list_t *second_number)
{
    element_t *first_pointer = first_number->head, *second_pointer = second_number->head;
    int first_proizv = 1, second_proizv = 1;
    int result;

    while (first_pointer != NULL)
    {
        for (int i = 0; i < first_pointer->power_of_simple_number; i++)
            first_proizv *= first_pointer->simple_number;

        first_pointer = first_pointer->next;
    }

    while (second_pointer != NULL)
    {
        for (int i = 0; i < second_pointer->power_of_simple_number; i++)
            second_proizv *= second_pointer->simple_number;

        second_pointer = second_pointer->next;
    }

    if (first_proizv < second_proizv)
        return 0;
    result = first_proizv / second_proizv;

    return result;
}
