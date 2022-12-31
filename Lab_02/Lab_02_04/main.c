#include <stdio.h>
#include <math.h>
//Вводите координаты 4 точек и узнаете что это за фигура
float length(float a, float b)
{
    float s;
    s = sqrt( a * a + b * b);
    return s;
}
int main()
{
    float x1, y1, x2, y2, x3, y3, x4, y4;
    float v1x, v2x, v3x, v4x;
    float v1y, v2y, v3y, v4y;

    printf("Input coordinates of the first dot:");
    if (scanf("%f%f", &x1, &y1) != 2)
    {
        printf("Неверные введенные значения!\n");
        return -1;
    }

    printf("Input coordinates of the second dot:");
    if (scanf("%f%f", &x2, &y2) != 2)
    {
        printf("Неверные введенные значения!\n");
        return -1;
    }

    printf("Input coordinates of the third dot:");
    if (scanf("%f%f", &x3, &y3) != 2)
    {
        printf("Неверные введенные значения!\n");
        return -1;
    }

    printf("Input coordinates of the fourth dot:");
    if (scanf("%f%f", &x4, &y4) != 2)
    {
        printf("Неверные введенные значения!\n");
        return -1;
    }

    else
    {
        v1x = x2 - x1;
        v2x = x3 - x2;
        v3x = x4 - x3;
        v4x = x1 - x4;

        v1y = y2 - y1;
        v2y = y3 - y2;
        v3y = y4 - y3;
        v4y = y1 - y4;

        if (length(v1x, v1y) == length(v2x, v2y) && length(v2x, v2y) == length(v3x, v3y) && length(v4x, v4y) == length(v1x, v1y) && v1x * v2x + v1y * v2y == 0)
        {
            printf("The figure is square.\n");
            return 0;
        }
        else if (length(v1x, v1y) == length(v2x, v2y) && length(v2x, v2y) == length(v3x, v3y) && length(v4x, v4y) == length(v1x, v1y) && v1x * v2x + v1y * v2y != 0)
        {
            printf("The figure is rhombus.\n");
            return 0;
        }
        else if (length(v1x, v1y) == length(v3x, v3y) && length(v2x, v2y) == length(v4x, v4y) && length(v4x, v4y) != length(v1x, v1y) && v1x * v2x + v1y * v2y == 0)
        {
            printf("The figure is rectangle.\n");
            return 0;
        }
        else if (length(v1x, v1y) == length(v3x, v3y) && length(v2x, v2y) == length(v4x, v4y) && v1x / v3x == v1y / v3y && v2x / v4x == v2y / v4y)
        {
            printf("The figure is parallelogram.\n");
            return 0;
        }
        else if ((v2x / v4x != v2y / v4y && v1x / v3x == v1y / v3y) || (v1x / v3x != v1y / v3y && v2x / v4x == v2y / v4y))
        {
            printf("The figure is trapeze.\n");
            return 0;
        }
        else
        {
            printf("The figure is an unknown figure.");
            return 0;
        }
    }
}
