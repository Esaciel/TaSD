#ifndef DEFINITIONS_H__
#define DEFINITIONS_H__

#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

#define OK 0

#define NOT_DIGIT_INT 1
#define TOO_LONG_INT 2
#define EMPTY_INT 3

#define NOT_DIGIT_FLOAT 4
#define TOO_LONG_FLOAT 5
#define EMPTY_FLOAT 6
#define NOT_DIGIT_EXPONENT 7
#define EMPTY_EXPONENT 8
#define TOO_LARGE_EXPONENT 9

#define DIVISION_BY_ZERO 10
#define RESULT_ORDER_OUT_OF_RANGE 11

// Мантисса числа представленна в виде массива символов длиной 41; 41-ый символ является замыкающим нулем в случае самого длинного числа, т.к. при выводе мантисса обрабатывается как строка.
typedef struct 
{
    char sign;
    char mantissa[41];
    short int mantissa_len;
    int exponent;
} my_float;

#endif // DEFINITIONS_H__
