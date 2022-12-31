#include <stdio.h>
#include <math.h>
//Из исходного массива получаем массив с элементами Армстронга
//Или не получаем, или все элементы Армстронга
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

int lengthOf(int cur)
{
    int quant = 0;

    while (cur > 0)
    {
        cur /= 10;
        quant += 1;
    }

    return quant;
}

int armstrong(int cur)
{
    int s = 0, stableCur = cur;

    while (cur > 0)
    {
        s += pow(cur % 10, lengthOf(stableCur));
        cur /= 10;
    }

    if (s == stableCur)
    {
        return 1;
    }
    else
        return 0;
}

int main()
{
    int a[10], b[10], n, k, counter = 0;

    if (scanf("%d", &n) != 1)
    {
        printf("Incorrect input!\n");
        return -1;
    }
    else if (n <= 0)
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
    for (int i = 0; i < n; i++)
    {
        if (armstrong(a[i]))
        {
            b[counter] = a[i];
            counter += 1;
        }
    }
    if (n == counter)
    {
        printf("all ellemets are Armstrong's!\n");
        return -3;
    }
    if (counter == 0)
    {
        printf("there are no Armstrong's!\n");
        return -4;
    }
    for (int i = 0; i < counter; i++)
        printf("%d ", b[i]);

    printf("\n");
    return 0;
}
