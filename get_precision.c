#include "main.h"

/**
 * get_precision - Calculate the precision for printing
 * @format: The format string used for printing arguments
 * @currentIndex: Current index in the format string
 * @argsList: List of arguments to be printed
 *
 * Return: Precision value
 */
int get_precision(const char *format, int *currentIndex, va_list argsList)
{
    int currentIdx = *currentIndex + 1;
    int precision = -1;

    if (format[currentIdx] != '.')
        return precision;

    precision = 0;

    for (currentIdx += 1; format[currentIdx] != '\0'; currentIdx++)
    {
        if (is_digit(format[currentIdx]))
        {
            precision *= 10;
            precision += format[currentIdx] - '0';
        }
        else if (format[currentIdx] == '*')
        {
            currentIdx++;
            precision = va_arg(argsList, int);
            break;
        }
        else
            break;
    }

    *currentIndex = currentIdx - 1;

    return precision;
}
