#include "my_snprintf.h"
#include <stdio.h>

int my_snprintf(string_t buffer, size_t buff_size, const string_t format, ...)
{
    if (format == NULL)
        return EMERGENCY_EXIT;
    setbuf(stdin, NULL);
    strcln(buffer, buff_size);
    va_list args;
    va_start(args, format);
    int temp;
    int_string strint;
    string_t srcptr;
    bool key = buff_size != 0 && buffer != NULL;
    size_t index = 0, length = 0;
    char lol, *pointer;
    while (format[index])
    {
        if (format[index] == '%')
        {
            index++;
            switch (format[index])
            {
                case 's':
                    srcptr = va_arg(args, string_t);
                    temp = my_strlen(srcptr);
                    if (length < buff_size - key)
                    {
                        if (length + temp > buff_size - key)
                            srcptr[buff_size - length - key] = '\0';
                        my_strcat(buffer, srcptr);
                    }
                    length += temp;
                    break;
                case 'c':
                    temp = va_arg(args, int);
                    lol = temp;
                    pointer = strint;
                    *pointer = lol;
                    pointer++;
                    *pointer = '\0';
                    temp = 1;
                    if (length < buff_size - key)
                    {
                        if (length + temp > buff_size - key)
                            strint[buff_size - length - key] = '\0';
                        my_strcat(buffer, strint);
                    }
                    length += temp;
                    break;
            }
        }
        else
        {
            if (length < buff_size - key)
                buffer[length] = format[index];
            length++;
        }
        index++;
    }
    if (key)
        buffer[buff_size - key] = '\0';
    va_end(args);
    return length;
}
