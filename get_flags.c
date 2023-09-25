#include "main.h"

/**
 * get_flags - Determine active formatting flags
 * @format: The format string used for printing arguments
 * @currentIndex: Current index in the format string
 * Return: Flags indicating formatting options
 */
int get_flags(const char *format, int *currentIndex)
{
    int index, currentIdx;
    int flags = 0;
    const char FLAG_CHARACTERS[] = {'-', '+', '0', '#', ' ', '\0'};
    const int FLAG_VALUES[] = {F_MINUS, F_PLUS, F_ZERO, F_HASH, F_SPACE, 0};

    for (currentIdx = *currentIndex + 1; format[currentIdx] != '\0'; currentIdx++)
    {
        for (index = 0; FLAG_CHARACTERS[index] != '\0'; index++)
        {
            if (format[currentIdx] == FLAG_CHARACTERS[index])
            {
                flags |= FLAG_VALUES[index];
                break;
            }
        }

        if (FLAG_CHARACTERS[index] == 0)
            break;
    }

    *currentIndex = currentIdx - 1;

    return flags;
}
