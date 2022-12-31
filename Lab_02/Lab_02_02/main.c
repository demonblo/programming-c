#include <stdio.h>
#include <math.h>
//Возможно тут что-то связано с 3 точками(но это не точно)
int k(float x1,float y1,float x2,float y2,float xa,float ya)
{
    int k = 1;

    if ((ya - y1) * (x2 - x1) - (xa - x1) * (y2 - y1) > 0)
        k = 0;
    else if ((ya - y1) * (x2 - x1) - (xa - x1) * (y2 - y1) < 0)
        k = 2;
    return k;
}

int main()
{
    float x1, y1, x2, y2, xa, ya;

    if (scanf("%f %f %f %f %f %f", &x1, &y1, &x2, &y2, &xa, &ya) != 6)
    {
        printf("Неверные введенные значения!\n");
        return -1;
    }
    else if ((x1 == x2) && (y1 == y2))
    {
        printf("Неверные введенные значения!\n");
        return -1;
    }
    else
    {
        printf("%d\n", k(x1, y1, x2, y2, xa, ya));
        return 0;
    }
}
