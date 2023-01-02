#ifndef __MY_SNPRINTF__
#define __MY_SNPRINTF__

#include <stdlib.h>
#include <stdarg.h>
#include <stdbool.h>
#include "string_func.h"

int my_snprintf(string_t buffer, size_t buf_size, const string_t format, ...);


#endif
