#include "io.h"

// Функция ввода целого числа
// Число вводится как целое, но хранится в структуре действительных чисел, т.е. 1230 => +0.123E+4
int enter_newint(my_float *enter_int)
{
    // Установка базового значения знакак на '+'
    enter_int->sign = '+';

    char string_int[41];
    short int pointer = 0;
    char symbol, zeroexist = 0;

    // Считывание первого символа в строке
    symbol = fgetc(stdin);
    if (symbol == '+' || symbol == '-')
    {
        // В случае если введен знак числа - запись его в структуру вводимого числа и чтение следующего знака
        enter_int->sign = symbol;
        symbol = fgetc(stdin);
    }

    // Пропуск нулей в начале фильма т.к. они не являются значащими цифрами
    while (symbol == '0')
    {
        // Установка флага наличия нулей в числе
        zeroexist = 1;
        symbol = fgetc(stdin);
    }

    // Указатель нормализации для обрезания нулей в конце числа
    short int normalize = pointer;
    
    // Считывание строки посимвольно
    while (symbol != '\n')
    {
        // В случае если считанный символ не является цифрой - возврат кода ошибки
        if (!isdigit(symbol))
        {
            return NOT_DIGIT_INT;
        }
        // В случае если считано более 40 цифр - возврат кода ошибки
        else if (pointer == 40)
        {
            return TOO_LONG_INT;
        }
        // В случае корректного чтения - запись очередного считанного числа в массив символов
        else
        {
            string_int[pointer++] = symbol;
            // Установка указателя нормализации на последний ненулевой символ
            if (symbol != '0')
            {
                normalize = pointer;
            }
            symbol = fgetc(stdin);
        }
    }
    // Установка значения экспоненты числа на длину прочтенного числа после пропущенных нулей
    enter_int->exponent = pointer;
    // Возврат обычному указателю значения нормализованного
    pointer = normalize;
    // Проверка пустоты прочтенного числа
    if (pointer == 0)
    {
        // В случае если в числе не было пропущенных нулей - возврат кода ошибки
        if (!zeroexist)
        {
            return EMPTY_INT;
        }
        // Иначе - установка значения числа на 0 и знака на '+', увеличение значения указателя
        else
        {
            string_int[pointer++] = '0';
            enter_int->sign = '+';
        }
    }
    // Замыкание строки нулевый байтом и запись её в структуру действительного числа, запись значения указателя после нормализации в поле длина мантиссы
    string_int[pointer] = '\0';
    memcpy(enter_int->mantissa, string_int, 41);
    enter_int->mantissa_len = pointer;
    return OK;
}

// Функция вывода действительного числа в виде его экспоненциальной записи
int enter_newfloat(my_float *enter_float)
{
    // Установка базового значения знака на '+'
    enter_float->sign = '+';

    char string_float[41];
    short int pointer = 0;
    char symbol, zeroexist = 0;
    int exponent = 0;

    // Считывание первого символа в строке
    symbol = fgetc(stdin);
    if (symbol == '+' || symbol == '-')
    {
        // В случае если введен знак числа - запись его в структуру вводимого числа и чтение следующего знака
        enter_float->sign = symbol;
        symbol = fgetc(stdin);
    }
    // Пропуск незначащих нулей в начале числа
    while (symbol == '0')
    {
        //  Установка флага существования нулей если они есть
        zeroexist = 1;
        symbol = fgetc(stdin);
    }
    // Установка указателя нормализации
    short int normalize = pointer;
    // Чтение строки до точки или символа экспоненты (до конца строки в случае отсутствия оных)
    while (symbol != '.' && symbol != 'E' && symbol != 'e' && symbol != '\n')
    {
        // Выход в случае иного нечислового значения или выхода количества значащих цифр за допустимый предел
        if (!isdigit(symbol))
        {
            return NOT_DIGIT_FLOAT;
        }
        else if (pointer == 40)
        {
            return TOO_LONG_FLOAT;
        }
        else
        {
            // Иначе - запись очередной цифры в массив символов
            string_float[pointer++] = symbol;
            if (symbol != '0')
            {
                // Установка указателя нормализации на последнюю ненулевую цифру
                normalize = pointer;
            }
            // Увеличение значения экспоненты
            exponent++;
            symbol = fgetc(stdin);
        }
    }
    // В случае наличия дробной части числа
    if (symbol == '.')
    {
        symbol = fgetc(stdin);
        // Чтения до символа экспоненты или конца строки
        while (symbol != 'E' && symbol != 'e' && symbol != '\n')
        {
            // Возврат кода ошибки в случае иного нечислового значения или выхода кол-ва значащих цифр за допустимые пределыы
            if (!isdigit(symbol))
            {
                return NOT_DIGIT_FLOAT;
            }
            else if (pointer == 40)
            {
                return TOO_LONG_FLOAT;
            }
            // В случае отсутствия значащих цифр слева от точки и продолжения нулей после неё - уменьшение экспоненты и установка флага существования нулей 
            else if (pointer == 0 && symbol == '0')
            {
                zeroexist = 1;
                exponent--;
            }
            // Иначе - запись очередной цифры в массив символов и установка указателя нормализации на последнюю ненулевую цифру
            else
            {
                string_float[pointer++] = symbol;
                if (symbol != '0')
                {
                    normalize = pointer;
                }
            }
            symbol = fgetc(stdin);
        }
    }
    char entering_exponent[7];
    // В случае наличия символа экспоненты
    if (symbol == 'E' || symbol == 'e')
    {
        int i = 0;
        symbol = fgetc(stdin);
        // Чтение первого символа и запись его в первое поле строки экспоненты в случае если он является знаком
        if (symbol == '-' || symbol == '+')
        {
            entering_exponent[i++] = symbol;
            symbol = fgetc(stdin);
        }
        // Чтение 5 цифр после знака
        int checkzero_exp = 0, zeroexist_exp = 0;
        for (int j = 0; j < 5; j++)
        {
            // Остановка по достижении конца строки
            if (symbol == '\n')
            {
                break;
            }
            // В случае иного нечислового значения - возврат кода ошибки
            else if (!isdigit(symbol))
            {
                return NOT_DIGIT_EXPONENT;
            }
            else if (!checkzero_exp && symbol == '0')
            {
                zeroexist_exp = 1;
                j--;
                symbol = fgetc(stdin);
            }
            // В случае корректного чтения - запись очередного символа в строку экспоненты
            else
            {
                checkzero_exp = 1;
                entering_exponent[i++] = symbol;
                symbol = fgetc(stdin);
            }
        }
        // В случае отсутствия цифр в экспоненте - возврат кода ошибки
        if (i == 0 || (i == 1 && !isdigit(entering_exponent[0])))
        {
            if (zeroexist_exp)
            {
                entering_exponent[i++] = '0';
            }
            else
            {
                return EMPTY_EXPONENT;
            }
        }
        // Иначе - замыкание строки экспоненты
        entering_exponent[i] = '\0';

        // Если последний символ строки является цифрой - возвращает код ошибки слишком большой экспоенты
        if (isdigit(symbol))
        {
            return TOO_LARGE_EXPONENT;
        }
        // В случае иного символа кроме конца строки - возврат кода ошибки нечисловой экспоненты
        if (symbol != '\n')
        {
            return NOT_DIGIT_EXPONENT;
        }
    }
    // Превращение строки экспоненты в число
    int entered_exponent = atoi(entering_exponent);

    // Увеличение экспоненты на прочитанное значение
    exponent += entered_exponent;
    // Присвоение указателю нормализованного значения
    pointer = normalize;

    // Проверка на пустую введенную строку
    if (pointer == 0)
    {
        // В случае отсутствия пропущенных нулей - возврат кода ошибки
        if (!zeroexist)
        {
            return EMPTY_FLOAT;
        }
        // Иначе - установка показателя экспоненты и значения числа на ноль, его знака - на '+'
        else
        {
            string_float[pointer++] = '0';
            enter_float->sign = '+';
            exponent = 0;
        }
    }
    // Замыкание строки числа, запись его в мантиссу действительного числа
    string_float[pointer] = '\0';
    memcpy(enter_float->mantissa, string_float, 41);
    // Установка значения длины мантиссы на нормализованный указатель и его экспоненты на вычисленное значение
    enter_float->mantissa_len = pointer;
    enter_float->exponent = exponent;
    return OK;
}

// Функция вывода сообщения об ошибках
void error_messagebox(int check)
{
    switch (check)
    {
        case NOT_DIGIT_INT:
            fprintf(stderr, "Ошибка: введено не числовое значение при вводе целого числа\n");
            break;
        case TOO_LONG_INT:
            fprintf(stderr, "Ошибка: длина целого числа выходит за допустимые пределы\n");
            break;
        case EMPTY_INT:
            fprintf(stderr, "Ошибка: введено пустое поле при вводе целого числа\n");
            break;
        case NOT_DIGIT_FLOAT:
            fprintf(stderr, "Ошибка: введено не числовое значение при вводе числа в экспоненциальной форме\n");
            break;
        case TOO_LONG_FLOAT:
            fprintf(stderr, "Ошибка: длина числа в экспоненциальной форме выходит за допустимые пределы\n");
            break;
        case EMPTY_FLOAT:
            fprintf(stderr, "Ошибка: введено пустое поле при вводе действительного числа\n");
            break;
        case NOT_DIGIT_EXPONENT:
            fprintf(stderr, "Ошибка: введено не числовое значение при вводе экспоненты\n");
            break;
        case EMPTY_EXPONENT:
            fprintf(stderr, "Ошибка: отсутствует значение экспоненты после соответствующего знака\n");
            break;
        case TOO_LARGE_EXPONENT:
            fprintf(stderr, "Ошибка: значение экспоненты выходит за допустимые пределы\n");
            break;
        case DIVISION_BY_ZERO:
            fprintf(stderr, "Ошибка: попытка деления на ноль\n");
            break;
        case RESULT_ORDER_OUT_OF_RANGE:
            fprintf(stderr, "Невозможно отобразить результат, т.к. значение его экспоненты выходит за допустимые пределы\n");
            break;
    }
}

// Функция вывода числа в экспоненциальной форме
void output_number(my_float *number)
{
    // fprintf(stdout, "%d\n", number->mantissa_len);
    fprintf(stdout, "%c0.%sE%+d\n", number->sign, number->mantissa, number->exponent);
}
