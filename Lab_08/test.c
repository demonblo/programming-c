#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "header.h"

#define EPS          0.000001
#define OK                  0
#define INCORRECT_INPUT    -1
#define ANSWER_FIRST 2.924018

void test_min()
{
    int err_cnt = 0;
    double mass[] = { 1, 1, 1, 1, 1 };
    int size = 5;
    double *mass_a = mass;
    double *mass_end = mass_a + size;
    int i = 0;
    {
        if (min(mass_a, mass_end) - *mass_a > EPS)
            err_cnt++;
    }
    {
        mass[0] = 10;
        mass[1] = 2;
        mass[2] = -2;
        mass[3] = 100;
        mass[4] = 0;
        if (min(mass_a, mass_end) - *(mass_a + 2) > EPS)
            err_cnt++;
    }
    {
        for (double *mass_cur = mass_a; mass_cur < mass_end; mass_cur++, i++)
            mass[i] = -i;
        if (min(mass_a, mass_end) - *(mass_a + 4) > EPS)
            err_cnt++;
    }
    printf("%s: %s\n", __func__, err_cnt ? "FAILED" : "SUCCESSFULLY");
}

void test_sr_cube_modules()
{
    int err_cnt = 0;
    int size = 4;
    double mass[] = { 3, 3, 3, 3, 3 };
    double *mass_d = mass;
    double *mass_end = mass_d + size;
    {
        if (sr_cube_modules(mass_d, mass_end) != 3.0)
            err_cnt++;
    }
    {
        mass[0] = 1.0;
        mass[1] = 3.0;
        mass[2] = 2.0;
        mass[3] = 4.0;
        if (sr_cube_modules(mass_d, mass_end) - ANSWER_FIRST > EPS)
            err_cnt++;
    }
    {
        mass[0] = -1.0;
        mass[1] = -3.0;
        mass[2] = -2.0;
        mass[3] = -4.0;
        if (sr_cube_modules(mass_d, mass_end) - ANSWER_FIRST > EPS)
            err_cnt++;
    }
    printf("%s: %s\n", __func__, err_cnt ? "FAILED" : "SUCCESSFULLY");
}

void test_remove_from_array()
{
    int err_cnt = 0;
    int size = 5;
    double mass[5];
    double *mass_g = mass;
    double *mass_end = mass_g + size;
    {
        for (int i = 0; i < size; i++)
            mass[i] = -1 - i;
        mass_end = remove_from_array(mass_g, mass_end);
        if (mass_end - mass_g != 2)
            err_cnt++;
    }
    mass_end = mass_g + size;
    {
        for (int i = 0; i < size; i++)
            mass[i] = 3;
        mass_end = remove_from_array(mass_g, mass_end);
        if (mass_end - mass_g != 5)
            err_cnt++;
    }
    mass_end = mass_g + size;
    {
        for (int i = 0; i < size - 1; i++)
            mass[i] = 1;
        mass[4] = 100;
        mass_end = remove_from_array(mass_g, mass_end);
        if (mass_end - mass_g != 1)
            err_cnt++;
    }
    mass_end = mass_g + size;
    printf("%s: %s\n", __func__, err_cnt ? "FAILED" : "SUCCESSFULLY");
}

int main()
{
    test_min();
    test_remove_from_array();
    test_sr_cube_modules();

    return OK;
}

