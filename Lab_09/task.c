#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "header.h"

#define OK                  0
#define INCORRECT_INPUT    -1
#define INCORRECT_FILE     -2
#define NO_ELEMENTS        -3
#define ERROR              -4

void allocate_matrix(int **mass, int rows, int columns)
{
    for (int row = 0; row < rows; row++)
        mass[row] = (int*)malloc(sizeof (int) * columns);
}

void increase_memory(int **mass, int first_rows, int second_rows, int columns)
{
    for (int row = 0; row < first_rows; row++)
        mass[row] = (int*)realloc(mass[row], sizeof (int) * (columns));

    for (int row = first_rows; row < second_rows; row++)
        mass[row] = (int*)malloc(sizeof (int) * (columns));
}

void decrease_memory(int**mass, int rows, int columns)
{
    for (int row = 0; row < rows; row++)
        mass[row] = (int*)realloc(mass[row], sizeof (int) * (columns));
}

int input_matrix(int **mass, int rows, int columns)
{
    //printf("Введите матрицу:\n");
    for (int row = 0; row < rows; row++)
        for (int column = 0; column < columns; column++)
            if (!scanf("%d", &mass[row][column]))
                return INCORRECT_INPUT;

    return OK;
}

void output_matrix(int **mass, int m, int n)
{
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
            printf("%d ", mass[i][j]);

        printf("\n");
    }
}

void free_matrix(int **mass, int rows)
{
    for (int row = 0; row < rows; row++)
        free(mass[row]);

    free(mass);
}

int find_max_row(int **mass, int rows, int columns)
{
    int max = mass[0][0], max_row = 0;

    for (int column = 0; column < columns; column++)
        for (int row = 0; row < rows; row++)
        {
            if (mass[row][column] > max)
            {
                max = mass[row][column];
                max_row = row;
            }
        }

    return max_row;
}

int find_max_column(int **mass, int rows, int columns)
{
    int max = mass[0][0], max_column = 0;

    for (int column = 0; column < columns; column++)
        for (int row = 0; row < rows; row++)
        {
            if (mass[row][column] > max)
            {
                max = mass[row][column];
                max_column = column;
            }
        }

    return max_column;
}

void delete_row(int **mass, int rows, int columns, int deleted_row)
{
    int cur = 0;

    for (int column = 0; column < columns; column++)
        for (int row = deleted_row; row < rows - 1; row++)
        {
            cur = mass[row][column];
            mass[row][column] = mass[row + 1][column];
            mass[row + 1][column] = cur;
        }
}

void delete_column(int **mass, int rows, int columns, int deleted_column)
{
    int cur = 0;

    for (int row = 0; row < rows; row++)
        for (int column = deleted_column; column < columns - 1; column++)
        {
            cur = mass[row][column];
            mass[row][column] = mass[row][column + 1];
            mass[row][column + 1] = cur;
        }
}

int lower_s_a(int **mass, int rows, int column)
{
    double s_a = 0;
    int result;

    for (int row = 0; row < rows; row++)
        s_a += mass[row][column];

    s_a = floor(s_a / rows);
    result = (int)s_a;

    return result;
}

int max_in_row(int **mass, int row, int columns)
{
    int max = mass[row][0];

    for (int column = 0; column < columns; column++)
        if (mass[row][column] > max)
            max = mass[row][column];

    return max;
}

void add_row(int **mass, int rows, int columns)
{
    for (int column = 0; column < columns; column++)
        mass[rows][column] = lower_s_a(mass, rows, column);
}

void add_column(int **mass, int rows, int columns)
{
    for (int row = 0; row < rows; row++)
        mass[row][columns] = max_in_row(mass, row, columns);
}

void make_coppy_matrix(int **mass, int **second_mass, int rows, int columns)
{
    for (int row = 0; row < rows; row++)
        for (int column = 0; column < columns; column++)
            mass[row][column] = second_mass[row][column];
}

void make_ed_matrix(int **mass, int rows, int columns)
{
    for (int row = 0; row < rows; row++)
        for (int column = 0; column < columns; column++)
        {
            if (row == column)
                mass[row][column] = 1;
            else
                mass[row][column] = 0;
        }
}

void matrix_multiplication(int **result_matrix, int **first_mass, int size)
{
    int sum = 0;
    int **coppy_mass;

    coppy_mass = (int**)malloc(sizeof (int*) * size);
    allocate_matrix(coppy_mass, size, size);
    make_coppy_matrix(coppy_mass, result_matrix, size, size);
    for (int row = 0; row < size; row++)
        for (int column = 0; column < size; column++)
        {
            for (int cur = 0; cur < size; cur++)
                sum += coppy_mass[row][cur] * first_mass[cur][column];

            result_matrix[row][column] = sum;
            sum = 0;
        }

    free_matrix(coppy_mass, size);
}
