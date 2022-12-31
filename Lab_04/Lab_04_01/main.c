#include <stdio.h>
#include <math.h>
//Среднее геометрическое массива
int input(int a[], int n)
{
    for (int i = 0; i < n; i++)
    {
        if (scanf("%d", &(a[i])) != 1)
        {
            printf("Incorrect input!");
            return -2;
        }
    }

    return 0;
}

double srGeom(int a[], int n)
{
    double s = 1, ans, step, counter = 0.0;

    for (int i = 0; i < n; i++)
    {
        if (a[i] > 0)
        {
            s *= a[i];
            counter += 1;
        }
    }

    if (counter != 0)
    {
        step = 1.0 / counter;
        ans = pow(s, step);
    }
    else
        ans = 0;
    return ans;
}

int main()
{
    int a[10], n, k;

    if (scanf("%d", &n) != 1)
    {
        printf("Incorrect input!");
        return -1;
    }
    else if (n <= 0)
    {
        printf("Incorrect input!");
        return -1;
    }
    else if (n > 10)
    {
        printf("Incorrect input!");
        return -1;
    }
    else
    {
        k = input(a, n);
        if (k >= 0)
        {
            if ((srGeom(a, n)) > 0)
            {
                printf("%lf\n", srGeom(a, n));
                return 0;
            }
            else
            {
                printf("Error!");
                return -3;
            }
        }
        else
        {
            return k;
        }
    }
}
