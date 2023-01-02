#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "header.h"

#define OK                  0
#define INCORRECT_INPUT    -1
#define INCORRECT_FILE     -2
#define NO_ELEMENTS        -3
#define ERROR              -4

int main()
{
    int n, p;
    int n_error;
    double *mass;
    double *mass_end;
    //printf("Введите число n, максимальное число 20!\n");
    if (scanf("%d", &n_error) != 1)
    {
        printf("Некорректный ввод!\n");
        return INCORRECT_INPUT;
    }
    n = n_error;
    if (n_error - n != OK)
    {
        printf("Некорректный ввод!\n");
        return INCORRECT_INPUT;
    }
    if (n > 20)
    {
        printf("Слишком много элементов!\n");
        return INCORRECT_INPUT;
    }
    mass = (double*)malloc(sizeof(double) * (n + 3));
    mass_end = mass + n;
    if (input_array(mass, mass_end))
    {
        printf("Некорректный ввод!\n");
        free(mass);
        return INCORRECT_INPUT;
    }
    //printf("Введите значение p:");
    if (scanf("%d", &p) != 1)
    {
        printf("Некорректный ввод!\n");
        free(mass);
        return INCORRECT_INPUT;
    }
    if (p > n)
    {
        printf("Исключительная ситуация!\n");
        free(mass);
        return ERROR;
    }
    else if (p < 0)
    {
        printf("Отрицательное значение p!\n");
        free(mass);
        return ERROR;
    }
    //printf("Первоначальный массив\n");
    //output_array(mass, mass_end);
    //printf("u_first:%lf\n", sr_cube_modules(mass, mass_end));
    mass_end = remove_from_array(mass, mass_end);
    //printf("Массив после удаления:\n");
    //output_array(mass, mass_end);
    mass_end = new_array(mass, mass_end, p);
    //printf("u_second:%lf\n", min(mass, mass_end));
    //printf("Итоговый массив:\n");
    output_array(mass, mass_end);
    free(mass);

    return 0;
}
