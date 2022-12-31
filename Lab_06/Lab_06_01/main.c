#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//Реализация strchr
char *strchrByMe(const char *s, int c)
{
    while(*s != (char)c)
    {
        s++;

        if (*s == '\0')
            return NULL;
    }

    return (char *)s;
}

int main()
{
    char *firstTest = "abevgdei";
    char *myTirstStrchar = strchrByMe(firstTest, 'e');
    char *standartFirstStrchar = strchr(firstTest, 'e');
    char *secondTest = "Work hard die hard";
    char *mySecondStrchar = strchrByMe(secondTest, ' ');
    char *standartSecondStrchar = strchr(secondTest, ' ');

    printf("\nThe first test: %s\n", firstTest);
    printf("Expected answer - %s\nMy answer - %s\n", myFirstStrchar, standartFirstStrchar);
    printf("\nSecond test:%s\n", secondTest);
    printf("Expected answer -%s\nMy answer -%s\n", mySecondStrchar, standartSecondStrchar);
    return 0;
}
