#include <stdio.h>
#include <string.h>
#include <limits.h>
#include "my_snprintf.h"

int main(void)
{
    int n_my = 0, n_system = 0;
    {
        printf("_____Test #1_____\n");
        char system[15];
        char my[15];
        n_my = my_snprintf(my, 15, "%c%s%c", '2', "fgd", 'A');
        n_system = snprintf(system, 15, "%c%s%c", '2', "fgd", 'A');
        if (strcmp(my, system) == 0 && n_my == n_system)
            printf("Test #1: Passed\n\n");
        printf("\n%c\n%c", n_my, n_system);
    }
    {
        printf("_____Test #2_____\n");
        char system[5];
        char my[5];
        n_my = my_snprintf(my, 5, "%c", 'c');
        n_system = snprintf(system, 5, "%c", 'c');
        if (strcmp(my, system) == 0 && n_my == n_system)
            printf("Test #2: Passed\n\n");
    }
    {
        printf("_____Test #3_____\n");
        char system[15];
        char my[15];
        n_my = my_snprintf(my, 15, "%sqwert", "one");
        n_system = snprintf(system, 15, "%sqwert", "one");
        if (strcmp(my, system) == 0 && n_my == n_system)
            printf("Test #3: Passed\n\n");
    }
    {
        printf("_____Test #4_____\n");
        char system[15];
        char my[15];
        n_my = my_snprintf(my, 15, "%s", "fadqeqwqewew");
        n_system = snprintf(system, 15, "%s", "fadqeqwqewew");
        if (strcmp(my, system) == 0 && n_my == n_system)
            printf("Test #4: Passed\n\n");
    }
    {
        printf("_____Test #5_____\n");
        char system[15];
        char my[15];
        n_my = my_snprintf(my, 15, "%s", "jiq");
        n_system = snprintf(system, 15, "%s", "jiq");
        if (strcmp(my, system) == 0 && n_my == n_system)
            printf("Test #5: Passed\n\n");
    }
    {
        printf("_____Test #6_____\n");
        char system[15];
        char my[15];
        n_my = my_snprintf(my, 15, "%s %c %c", "test", 'a', 'A');
        n_system = snprintf(system, 15, "%s %c %c", "test", 'a', 'A');
        if (strcmp(my, system) == 0 && n_my == n_system)
            printf("Test #6: Passed\n\n");
    }
    {
        printf("_____Test #7_____\n");
        char system[15];
        char my[15];
        n_my = my_snprintf(my, 15, "%c %c", 'b', 'B');
        n_system = snprintf(system, 15, "%c %c", 'b', 'B');
        if (strcmp(my, system) == 0 && n_my == n_system)
            printf("Test #7: Passed\n\n");
    }
    {
        printf("_____Test #8_____\n");
        char system[15];
        char my[15];
        n_my = my_snprintf(my, 15, "%c", ':');
        n_system = snprintf(system, 15, "%c", ':');
        if (strcmp(my, system) == 0 && n_my == n_system)
            printf("Test #8: Passed\n\n");
    }
    {
        printf("_____Test #9_____\n");
        char system[15];
        char my[15];
        n_my = my_snprintf(my, 15, "%c", 'z');
        n_system = snprintf(system, 15, "%c", 'z');
        if (strcmp(my, system) == 0 && n_my == n_system)
            printf("Test #9: Passed\n\n");
    }
    {
        printf("_____Test #10_____\n");
        char system[15];
        char my[15];
        n_my = my_snprintf(my, 15, "%c", '0');
        n_system = snprintf(system, 15, "%c", '0');
        if (strcmp(my, system) == 0 && n_my == n_system)
            printf("Test #10: Passed\n\n");
    }
    {
        printf("_____Test #11_____\n");
        char system[50];
        char my[50];
        n_my = my_snprintf(my, 50, "%c %s", '0', "onetwo");
        n_system = snprintf(system, 50, "%c %s", '0', "onetwo");
        if (strcmp(my, system) == 0 && n_my == n_system)
            printf("Test #11: Passed\n\n");
    }
    {
        printf("_____Test #12_____\n");
        char system[50];
        char my[50];
        n_my = my_snprintf(my, 50, "%s%c%s", "one", '0', "two");
        n_system = snprintf(system, 50, "%s%c%s", "one", '0', "two");
        if (strcmp(my, system) == 0 && n_my == n_system)
            printf("Test #12: Passed\n\n");
    }
    {
        printf("_____Test #13_____\n");
        char system[50];
        char my[50];
        n_my = my_snprintf(my, 50, "%c%s", 'x', "twothree");
        n_system = snprintf(system, 50, "%c%s", 'x', "twothree");
        if (strcmp(my, system) == 0 && n_my == n_system)
            printf("Test #13: Passed\n\n");
    }
    {
        printf("_____Test #14_____\n");
        char system[50];
        char my[50];
        n_my = my_snprintf(my, 50, "%c%s%c", 'x', "twothree", 'x');
        n_system = snprintf(system, 50, "%c%s%c", 'x', "twothree", 'x');
        if (strcmp(my, system) == 0 && n_my == n_system)
            printf("Test #14: Passed\n\n");
    }
    {
        printf("_____Test #15_____\n");
        char system[15];
        char my[15];
        n_my = my_snprintf(my, 15, "  ");
        n_system = snprintf(system, 15, "  ");
        if (strcmp(my, system) == 0 && n_my == n_system)
            printf("Test #15: Passed\n\n");
    }
    {
        printf("_____Test #16_____\n");
        char system[50];
        char my[50];
        n_my = my_snprintf(my, 50, "%c%s%c%c", 'a', "twothree", '0', 'Z');
        n_system = snprintf(system, 50, "%c%s%c%c", 'a', "twothree", '0', 'Z');
        if (strcmp(my, system) == 0 && n_my == n_system)
            printf("Test #16: Passed\n\n");
    }
    {
        printf("_____Test #17_____\n");
        char system[50];
        char my[50];
        n_my = my_snprintf(my, 50, "%c0%s4", 'a', "twothree");
        n_system = snprintf(system, 50, "%c0%s4", 'a', "twothree");
        if (strcmp(my, system) == 0 && n_my == n_system)
            printf("Test #17: Passed\n\n");
    }
    {
        printf("_____Test #18_____\n");
        char system[50];
        char my[50];
        n_my = my_snprintf(my, 50, "%c%s", 'z', "twothree");
        n_system = snprintf(system, 50, "%c%s", 'z', "twothree");
        if (strcmp(my, system) == 0 && n_my == n_system)
            printf("Test #18: Passed\n\n");
    }
    {
        printf("_____Test #19_____\n");
        char system[50];
        char my[50];
        n_my = my_snprintf(my, 50, "%s\n%s", "twothree", "len");
        n_system = snprintf(system, 50, "%s\n%s", "twothree", "len");
        if (strcmp(my, system) == 0 && n_my == n_system)
            printf("Test #19: Passed\n\n");
    }
    {
        printf("_____Test #20_____\n");
        char system[15];
        char my[15];
        n_my = my_snprintf(my, 15, "%s%c", "twothreefour", 'x');
        n_system = snprintf(system, 15, "%s%c", "twothreefour", 'x');
        if (strcmp(my, system) == 0 && n_my == n_system)
            printf("Test #20: Passed\n\n");
    }
}
