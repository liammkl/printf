#include "main.h"

/**
 * get_size - Determine the size specifier for argument casting
 * @format: The format string used for printing arguments
 * @currentIndex: Current index in the format string
 *
 * Return: Size specifier value
 */
int get_size(const char *format, int *currentIndex)
{
    int currentIdx = *currentIndex + 1;
    int sizeSpecifier = 0;

    if (format[currentIdx] == 'l')
        sizeSpecifier = SIZE_LONG;
    else if (format[currentIdx] == 'h')
        sizeSpecifier = SIZE_SHORT;

    if (sizeSpecifier == 0)
        *currentIndex = currentIdx - 1;
    else
        *currentIndex = currentIdx;

    return sizeSpecifier;
}
