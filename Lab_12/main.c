#include "header.h"

int main()
{
    list_t *first_number, *second_number, *result_division;
    long int first_int_number;
    long int second_int_number;
    int division;
    char key;

    printf("Выберите пункт меню:\n");
    printf("a) - Умножение 2 чисел хранящихся в данном формате.\n");
    printf("b) - Возведение числа в квадрат.\n");
    printf("c) - Деление без остатка.\n");
    printf("Числа должны быть больше 1!\n");
    //Считывание ключа
    if (scanf("%c", &key) != 1)
    {
        printf("Некорректный ввод!\n");
        return INPUT_ERROR;
    }
    if (key  != 'a' && key != 'b' && key != 'c')
    {
        printf("Некорректный ввод!\n");
        return INPUT_ERROR;
    }
    getchar();
    printf("Введите первое число:");
    //Ввод первого числа
    if (scanf("%ld", &first_int_number) != 1)
    {
        printf("Некорректный ввод!\n");
        return INPUT_ERROR;
    }
    if (first_int_number < 2)
    {
        printf("Число не может быть меньше 2!\n");
        return INPUT_ERROR;
    }
    first_number = allocate_list();
    input_number(first_number, first_int_number);
    printf("Первое число:\n");
    output_list(first_number);
    printf("\n");


    if (key == 'a' || key == 'c')
    {
        printf("Введите второе число:");
        second_number = allocate_list();
        //Вводв второго числа
        if (scanf("%ld", &second_int_number) != 1)
        {
            printf("Некорректный ввод!\n");
            return INPUT_ERROR;
        }
        if (second_int_number < 2)
        {
            printf("Число не может быть меньше 2!\n");
            return INPUT_ERROR;
        }
        input_number(second_number, second_int_number);
        printf("Второе число:\n");
        output_list(second_number);
        printf("\n");
    }

    if (key == 'a')
    {
        numbers_multiplication(first_number, second_number);
        printf("Результат умножения первого и второго чисел:\n");
        if (first_number->length >= second_number->length)
            output_list(first_number);
        else
            output_list(second_number);
        free_list(first_number);
        free_list(second_number);
    }
    else if (key == 'b')
    {
        printf("Результат возведение числа в квадрат:\n");
        square_number(first_number);
        output_list(first_number);
        free_list(first_number);
    }
    else if (key == 'c')
    {
        division = number_division(first_number, second_number);
        if (division == 0)
        {
            printf("Делитель больше делимого, результат деления:0\n");
            return 0;
        }
        else if (division == 1)
        {
            printf("Результат деления:1\n");
            return 0;
        }
        else
        {
            result_division = allocate_list();
            input_number(result_division, division);
            printf("Результат деления без остатка первого числа на второе:\n");
            output_list(result_division);
            free_list(first_number);
            free_list(second_number);
            free_list(result_division);
        }
    }

    return 0;
}
