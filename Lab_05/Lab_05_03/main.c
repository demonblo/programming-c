#include <stdio.h>
#define Max_size              10
#define Error_input_size      -1
#define Error_input_elements  -2
int input(int matr [][Max_size], int n, int m)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            printf("Input [%d][%d] element:", i, j);
            if (scanf("%d", &(matr[i][j])) != 1)
                return Error_input_elements;
        }
    }

    return 0;
}

void outputMatrix(int matr[][Max_size], int n, int m)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
            printf("%d ", matr[i][j]);
        printf("\n");
    }
}

int min(int mass[], int n)
{
    int min = mass[0];

    for (int i = 1; i < n; i++)
        if (mass[i] < min)
            min = mass[i];

    return min;
}

void massSwap(int firstRow[], int secondRow[], int m)
{
    int temp;

    for (int i = 0; i < m; i++)
    {
        temp = first_row[i];
        firstRow[i] = secondRow[i];
        secondRow[i] = temp;
    }
}

void sortMatrix(int matr[][Max_size], int n, int m, int mass[])
{
    int temp;

    for (int i = 0; i < n; i++)
        mass[i] = min(matr[i], m);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n - i - 1; j++)
        {
            if (mass[j] < mass[j + 1])
            {
                temp = mass[j];
                mass[j] = mass[j + 1];
                mass[j + 1] = temp;
                massSwap(matr[j], matr[j + 1], m);
            }
        }
}

int main()
{
    int matr[Max_size][Max_size], mass[Max_size], n, m, k;

    printf("Input size of matrix:");
    if (scanf("%d%d", &n, &m) != 2)
    {
        printf("Incorrect input of size!\n");
        return Error_input_size;
    }
    if ((n <= 0 || n > 10) || (m <= 0 || m > 10))
    {
        printf("Incorrect input of size!\n");
        return Error_input_elements;
    }
    k = input(matr, n, m);
    if (k != 0)
    {
        printf("Incorrect input of elements!\n");
        return k;
    }
    printf("Source matrix\n");
    outputMatrix(matr, n, m);
    sortMatrix(matr, n, m, mass);
    printf("Calculated matrix\n");
    outputMatrix(matr, n, m);
    return 0;
}
