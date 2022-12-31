#include <stdio.h>
#include <math.h>

int main()
{
    double a, b, h, d1, d2, p;
    printf("Please,input a,b,h\n");
    scanf("%lf%lf%lf", &a, &b, &h);
    printf("\n");
    d2 = (b - a) / 2;
    d1 = sqrt(h * h + d2 * d2);
    p = 2 * d1 + a + b;
    printf("P= %.5f\n", p);
    return 0;
}
