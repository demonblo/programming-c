#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#ifndef HEADER_H
#define HEADER_H
#define OK                  0
#define INCORRECT_INPUT    -1
#define INCORRECT_FILE     -2
#define NO_ELEMENTS        -3
#define ERROR              -4

#endif // HEADER_H

int input_array(double *, double *);
void output_array(double *, double *);
double sr_cube_modules(double *, double *);
double *remove_from_array(double *, double *);
double min(double *, double *);
double *new_array(double *, double *, int );
