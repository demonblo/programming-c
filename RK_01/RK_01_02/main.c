#include <stdio.h>
#include <math.h>
//Вводите массив а потом удаляете(кек) все элементы меньше первого(нулевого)
int input(int a[], int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("Введите a[%d]: ", i);
        if (scanf("%d", &(a[i])) != 1)
            return -2;
    }

    return 0;
}

void output(int a[], int n)
{
    for (int i = 0; i < n; i++)
        printf("%d ", a[i]);
    printf("\n");
}

int delete(int a[], int n)
{
    int i = 1;

    while (i < n)
    {
        if (a[i] < a[i - 1])
        {
            for (int j = i; j < n; j++)
                a[j] = a[j + 1];
            n -= 1;
        }
        else
            i += 1;
    }

    return n;
}

int main()
{
    int a[10], n, b, new_n;

    printf("Введите размерность массива: ");
    if (scanf("%d", &n) != 1)
    {
        printf("Неверный ввод\n");
        return -1;
    }
    else if (n <= 0)
    {
        printf("Неверный ввод\n");
        return -1;
    }
    else if (n > 10)
    {
        printf("Неверный ввод\n");
        return -1;
    }
    b = input(a, n);
    if (b != 0)
        {
            printf("Неверный ввод\n");
            return -2;
        }

    printf("Исходный массив: ");
    output(a, n);
    new_n = delete(a, n);
    printf("Получившийся массива: ");
    output(a, new_n);
    return 0;
}
