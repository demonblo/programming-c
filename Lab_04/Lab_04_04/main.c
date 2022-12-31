#include <stdio.h>
#include <math.h>
//Гномья сортировка
int input(int a[], int n)
{
    for (int i = 0; i < n; i++)
    {
        if (scanf("%d", &(a[i])) != 1)
        {
            printf("Incorrect input!\n");
            return -2;
        }
    }

    return 0;
}

void gnomeSort(int a[], int n)
{
    int i = 1, temp;

    while (i < n)
    {
        if (a[i] >= a[i - 1] || i == 0)
            i += 1;
        else if (a[i] < a[i - 1])
        {
            temp = a[i];
            a[i] = a[i - 1];
            a[i - 1] = temp;
            i -= 1;
        }
    }
}

int main()
{
    int a[10], n, k;

    if (scanf("%d", &n) != 1)
    {
        printf("Incorrect input!\n");
        return -1;
    }
    else if (n < 0)
    {
        printf("Incorrect input!\n");
        return -1;
    }
    else if (n > 10)
    {
        printf("Incorrect input!\n");
        return -1;
    }
    //
    k = input(a, n);
    if (k != 0)
        return -2;
    gnomeSort(a, n);

    for (int i = 0; i < n; i++)
        printf("%d ", a[i]);

    printf("\n");
    return 0;
}
