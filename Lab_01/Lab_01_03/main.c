#include <stdio.h>
#include <math.h>

int main()
{
    double h, t, m;
    printf("Input h, t, m:");
    scanf("%lf%lf%lf", &h, &t, &m);
    printf("\n");
    printf("Ves=%.5f , Im=%.5f \n", h * t / 240, m / h / h * 10000);
    return 0;
}
