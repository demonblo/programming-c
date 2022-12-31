#include <stdio.h>
#include <math.h>
//Посмотри на вывод
int length(int a)
{
    int quant = 0;

    while (a > 0)
    {
        quant += 1;
        a /= 10;
    }

    return quant;
}

int quantity(int a)
{
    int first = a / pow(10, length(a) - 1);
    int quant = 1;

    while (a > 10)
    {
        if (a % 10 == first)
            quant += 1;
        a /= 10;
    }

    return quant;
}

int main()
{
    float numb_0;
    int numb;

    printf("Введите натуральное число: ");
    if ((scanf("%f", &numb_0) != 1) || (numb_0 <= 0))
    {
        printf("Некорректный ввод\n");
        return -1;
    }
    numb = numb_0;
    if (numb < numb_0)
    {
        printf("Некорректный ввод\n");
        return -1;
    }
    printf("Первая цифра данного числа встречается %d раз(a)\n", quantity(numb));

    return 0;
}
