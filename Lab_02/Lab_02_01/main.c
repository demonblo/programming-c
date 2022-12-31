#include <stdio.h>
#include <math.h>
//nod =(?) наибольший общий делитель 2 чисел
int nod(int a, int b)
{
    int the_end, i = 1, nod = 1;

    if (a > b)
        the_end = a;
    else
        the_end = b;

    while (i <= the_end)
    {
        if ((a % i == 0) && (b % i == 0))
            nod = i;
        i++;
    }
    return nod;
}

int main()
{
    int a = 0, b = 0, answer;

    printf("Input a, b: ");
    if ((scanf("%d%d", &a, &b) != 2) || (a <= 0) || (b <= 0))
    {
        printf("Неверные введенные значения!\n");
        return 1;
    }
    else
    {
        answer = nod(a, b);
        printf("NOD = %d\n", answer);
        return 0;
    }
}

