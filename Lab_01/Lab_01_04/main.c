#include <stdio.h>
#include <math.h>

int main()
{
    int s, maxq, perh;
    printf("Input s:");
    scanf("%d", &s);
    maxq = s / 45;
    s = s % 45 + maxq * 20;
    do
    {
        maxq += s / 45;
        perh = s / 45;
        s = s % 45 + perh * 20;
    }
    while (s >= 45);
    printf("Maxq: %d\n", maxq);
    return 0;
}
