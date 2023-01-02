#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "header.h"

#define OK                  0
#define INCORRECT_INPUT    -1
#define INCORRECT_MATRIX   -2
#define INCORRECT_POWERS   -3
#define NO_ELEMENTS        -4
#define ERROR              -5


int main()
{
    int **first_mass, **second_mass, **result_matrix;
    int first_rows, first_columns, second_rows, second_columns;
    int r, g, turn;
    int max_row, max_column;

    //printf("Введите количество строк и столбцов первой матрицы:");
    if (scanf("%d %d", &first_rows, &first_columns) != 2)
    {
        printf("Размерность матрицы введена некорректно!\n");
        return INCORRECT_INPUT;
    }
    if (first_rows < 1 || first_columns < 1)
    {
        printf("Размерность матрицы введена некорректно!\n");
        return INCORRECT_INPUT;
    }
    first_mass = (int**)malloc(sizeof (int*) * first_rows);
    allocate_matrix(first_mass, first_rows, first_columns);
    if (input_matrix(first_mass, first_rows, first_columns))
    {
        printf("Матрица введена некорректно!\n");
        free_matrix(first_mass, first_rows);
        return INCORRECT_MATRIX;
    }
    //printf("Первая матрица:\n");
    //output_matrix(first_mass, first_rows, first_columns);
    //printf("Введите количество строк и столбцов второй матрицы:");
    if (scanf("%d %d", &second_rows, &second_columns) != 2)
    {
        printf("Размерность матрицы введена некорректно!\n");
        free_matrix(first_mass, first_rows);
        return INCORRECT_INPUT;
    }
    if (second_rows < 1 || second_columns < 1)
    {
        printf("Размерность матрицы введена некорректно!\n");
        free_matrix(first_mass, first_rows);
        return INCORRECT_INPUT;
    }
    second_mass = (int**)malloc(sizeof (int*) * second_rows);
    allocate_matrix(second_mass, second_rows, second_columns);
    if (input_matrix(second_mass, second_rows, second_columns))
    {
        printf("Матрица введена некорректно!\n");
        free_matrix(first_mass, first_rows);
        free_matrix(second_mass, second_rows);
        return INCORRECT_MATRIX;
    }
    //printf("Вторая матрица:\n");
    //output_matrix(second_mass, second_rows, second_columns);
    //printf("Введите степени p и q:");
    if (scanf("%d %d", &r, &g) != 2)
    {
        printf("Степени r и g введены неверно!\n");
        free_matrix(first_mass, first_rows);
        free_matrix(second_mass, second_rows);
        return INCORRECT_POWERS;
    }
    if (r < 0 || g < 0)
    {
        printf("Степени r и g не могут быть отрицательными!\n");
        free_matrix(first_mass, first_rows);
        free_matrix(second_mass, second_rows);
        return INCORRECT_POWERS;
    }
    if (first_rows > first_columns)
    {
        while (first_rows > first_columns)
        {
            max_row = find_max_row(first_mass, first_rows, first_columns);
            delete_row(first_mass, first_rows, first_columns, max_row);
            first_rows--;
            free(first_mass[first_rows]);
        }
        first_mass = (int**)realloc(first_mass, sizeof (int*) * first_rows);
        decrease_memory(first_mass, first_rows, first_columns);
    }
    if (first_columns > first_rows)
    {
        while (first_columns > first_rows)
        {
            max_column = find_max_column(first_mass, first_rows, first_columns);
            delete_column(first_mass, first_rows, first_columns, max_column);
            first_columns--;
        }
        first_mass = (int**)realloc(first_mass, sizeof (int*) * first_rows);
        decrease_memory(first_mass, first_rows, first_columns);
    }
    if (second_rows > second_columns)
    {
        while (second_rows > second_columns)
        {
            max_row = find_max_row(second_mass, second_rows, second_columns);
            delete_row(second_mass, second_rows, second_columns, max_row);
            second_rows--;
            free(second_mass[second_rows]);
        }
        second_mass = (int**)realloc(second_mass, sizeof (int*) * second_rows);
        decrease_memory(second_mass, second_rows, second_columns);
    }
    if (second_columns > second_rows)
    {
        while (second_columns > second_rows)
        {
            max_column = find_max_column(second_mass, second_rows, second_columns);
            delete_column(second_mass, second_rows, second_columns, max_column);
            second_columns--;
        }
        second_mass = (int**)realloc(second_mass, sizeof (int*) * second_rows);
        decrease_memory(second_mass, second_rows, second_columns);
    }
    //printf("Первая матрица после удаления:\n");
    //output_matrix(first_mass, first_rows, first_columns);
    //printf("Вторая матрица после удаления:\n");
    //output_matrix(second_mass, second_rows, second_columns);
    if (second_rows > first_rows)
    {
        first_mass = (int**)realloc(first_mass, sizeof (int*) * (second_rows));
        increase_memory(first_mass, first_rows, second_rows, second_columns);
        while (second_rows > first_rows)
        {
            add_row(first_mass, first_rows, first_columns);
            first_rows++;
        }
        while (second_columns > first_columns)
        {
            add_column(first_mass, first_rows, first_columns);
            first_columns++;
        }
    }
    if (first_rows > second_rows)
    {
        second_mass = (int**)realloc(second_mass, sizeof (int*) * (first_rows));
        increase_memory(second_mass, second_rows, first_rows, first_columns);
        while (first_rows > second_rows)
        {
            add_row(second_mass, second_rows, second_columns);
            second_rows++;
        }
        while (first_columns > second_columns)
        {
            add_column(second_mass, second_rows, second_columns);
            second_columns++;
        }
    }
    result_matrix = (int**)malloc(sizeof (int*) * first_rows);
    allocate_matrix(result_matrix, first_rows, first_columns);
    if (r == 0)
        make_ed_matrix(first_mass, first_rows, first_columns);
    if (g == 0)
        make_ed_matrix(second_mass, second_rows, second_columns);
    make_coppy_matrix(result_matrix, first_mass, first_rows, first_columns);
    turn = 1;
    while (turn < r)
    {
        matrix_multiplication(result_matrix, first_mass, first_rows);
        turn++;
    }

    if (g > 0)
    {
        turn = 0;
        while (turn < g)
        {
            matrix_multiplication(result_matrix, second_mass, second_rows);
            turn++;
        }
    }
    else if (!g)
        matrix_multiplication(result_matrix, second_mass, second_rows);
    //printf("Первая матрица перед умножением:\n");
    //output_matrix(first_mass, first_rows, first_columns);
    //printf("Вторая матрица перед умножением:\n");
    //output_matrix(second_mass, second_rows, second_columns);
    //printf("Результат:\n");
    output_matrix(result_matrix, first_rows, first_columns);
    free_matrix(first_mass, first_rows);
    free_matrix(second_mass, second_rows);
    free_matrix(result_matrix, first_rows);

    return OK;
}
