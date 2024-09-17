#include "definitions.h"
#include "io.h"
#include "divide.h"

int main(void)
{
    int check;
    my_float intnum;
    my_float floatnum;
    my_float result;

    fprintf(stdout, "Калькулятор для деления длинных чисел\n");
    fprintf(stdout, "Производит деление целого длинного числа на дробное в экспоненциальной форме\n");

    fprintf(stdout, "\nВведите целое число;\nМаксимальная длина после первой значащей цифры включительно - 40 цифр\nЗнак перед числом опционален\n");
    fprintf(stdout, "+____5____0____5____0____5____0____5____0|\n");
    check = enter_newint(&intnum);
    if (check != OK)
    {
        error_messagebox(check);
        return check;
    }

    fprintf(stdout, "\nВведите действительное число;\nМаксимальная длина после первой значащей цифры - 40 цифр\n");
    fprintf(stdout, "Знак перед числом опционален, показатель экспоненты (знак E/e и значение после него) и знак числа в ней опциональны\n");
    fprintf(stdout, "Ограничение на показатель экспоненты - целое число длиной 5 цифр, т.е от -99999 до +99999\n");
    fprintf(stdout, "+____5____0____5____0____5____0____5____0 E+____5|\n");
    check = enter_newfloat(&floatnum);
    if (check != OK)
    {
        error_messagebox(check);
        return check;
    }

    fprintf(stdout, "\n");
    check = divide(&intnum, &floatnum, &result);
    if (check != OK)
    {
        error_messagebox(check);
        return check;
    }
    fprintf(stdout, "Результат деления в экспоненциальной форме:\n");
    output_number(&result);
    return check;
}