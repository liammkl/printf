#include "main.h"

/**
 * get_width - Determine the width for formatting arguments
 * @format: The format string used for printing arguments
 * @currentIndex: Current index in the format string
 * @args: List of arguments
 *
 * Return: Width specification
 */
int get_width(const char *format, int *currentIndex, va_list args)
{
    int currentIdx;
    int width = 0;

    for (currentIdx = *currentIndex + 1; format[currentIdx] != '\0'; currentIdx++)
    {
        if (is_digit(format[currentIdx]))
        {
            width *= 10;
            width += format[currentIdx] - '0';
        }
        else if (format[currentIdx] == '*')
        {
            currentIdx++;
            width = va_arg(args, int);
            break;
        }
        else
        {
            break;
        }
    }

    *currentIndex = currentIdx - 1;

    return width;
}
