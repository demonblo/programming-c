#include "string_func.h"

size_t my_strlen(string_t str)
{
    size_t length = 0;
    while (str[length++]);
    return length ? length - 1 : length;
}

void strcln(string_t str, size_t size)
{
    size_t index = 0;
    while (index < size)
        str[index++] = '\0';
}

int my_strcat(string_t destptr, string_t srcptr)
{
    if (destptr == NULL || srcptr == NULL)
        return EMERGENCY_EXIT;
    size_t length = my_strlen(destptr);
    for (size_t index = 0; (destptr[length + index] = srcptr[index]); index++);
    return EXIT_SUCCESS;
}


