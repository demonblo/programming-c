#ifndef __STRING_FUNC__
#define __STRING_FUNC__

#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

#define EMERGENCY_EXIT  -1
#define LENGTH_OF_DIGIT 12

typedef char *string_t;
typedef char int_string[LENGTH_OF_DIGIT];

int my_strcat(string_t destptr, string_t srcptr);
void strcln(string_t str, size_t size);
size_t my_strlen(string_t str);


#endif
