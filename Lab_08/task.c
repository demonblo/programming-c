#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "header.h"

#define OK                  0
#define INCORRECT_INPUT    -1
#define INCORRECT_FILE     -2
#define NO_ELEMENTS        -3
#define ERROR              -4

int input_array(double *mass, double *mass_end)
{
    //printf("Введите массив\n");
    for (double *mass_cur = mass; mass_cur < mass_end; mass_cur++)
        if (scanf("%lf", &(*mass_cur)) != 1)
            return INCORRECT_INPUT;

    return OK;
}

void output_array(double *mass, double *mass_end)
{
    double *mass_cur;

    for (mass_cur = mass; mass_cur < mass_end; mass_cur++)
        printf("%lf ", *mass_cur);

    printf("\n");
}

double sr_cube_modules(double *mass, double *mass_end)
{
    double *mass_cur, cube = 0.0;

    for (mass_cur = mass; mass_cur < mass_end; mass_cur++)
        cube += fabs(*(mass_cur)) * (*(mass_cur)) * (*(mass_cur)) / (mass_end - mass);

    cube = pow(cube, 1.0 / 3.0);

    return cube;
}

double *remove_from_array(double *mass, double *mass_end)
{
    double *mass_cur, *change;
    double u_first = sr_cube_modules(mass, mass_end), current;

    for (mass_cur = mass; mass_cur < mass_end; mass_cur++)
    {
        if (fabs(*mass_cur) < u_first)
        {
            for (change = mass_cur; change < mass_end - 1; change++)
            {
                current = *change;
                *change = *(change + 1);
                *(change + 1) = current;
            }

            mass_cur--;
            mass_end--;
        }
    }

    return mass_end;
}

double min(double *mass, double *mass_end)
{
    double *mass_cur, min;

    min = *mass;
    for (mass_cur = mass; mass_cur < mass_end; mass_cur++)
        if (*mass_cur < min)
            min = *mass_cur;

    return min;
}

double *new_array(double *mass, double *mass_end, int p)
{
    double *mass_cur;
    double u_second = min(mass, mass_end), prev = u_second, current;

    for (mass_cur = mass + p; mass_cur < mass_end; mass_cur++)
    {
        current = *mass_cur;
        *mass_cur = prev;
        prev = current;
    }

    mass_end++;
    *mass_end = prev;
    //Помещение u_second в начало массива
    prev = u_second;
    for (mass_cur = mass; mass_cur < mass_end; mass_cur++)
    {
        current = *mass_cur;
        *mass_cur = prev;
        prev = current;
    }

    mass_end++;
    *mass_end = prev;
    //Помещение u_second в конец массива
    *mass_end = u_second;
    mass_end++;

    return mass_end;
}
