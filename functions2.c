#include "main.h"

/****************** PRINT POINTER ******************/
/**
 * print_pointer - Print the value of a pointer variable
 * @types: List of arguments
 * @buffer: Buffer array for printing
 * @flags: Calculate active flags
 * @width: Width specification
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of characters printed
 */
int print_pointer(va_list types, char buffer[],
    int flags, int width, int precision, int size)
{
    char extra_char = 0, padding_char = ' ';
    int index = BUFF_SIZE - 2, length = 2, padding_start = 1; /* length=2, for '0x' */
    unsigned long num_address;
    char map_to[] = "0123456789abcdef";
    void *address = va_arg(types, void *);

    UNUSED(width);
    UNUSED(size);

    if (address == NULL)
        return (write(1, "(nil)", 5));

    buffer[BUFF_SIZE - 1] = '\0';
    UNUSED(precision);

    num_address = (unsigned long)address;

    while (num_address > 0)
    {
        buffer[index--] = map_to[num_address % 16];
        num_address /= 16;
        length++;
    }

    if ((flags & F_ZERO) && !(flags & F_MINUS))
        padding_char = '0';

    if (flags & F_PLUS)
        extra_char = '+', length++;
    else if (flags & F_SPACE)
        extra_char = ' ', length++;

    index++;

    return (write_pointer(buffer, index, length,
        width, flags, padding_char, extra_char, padding_start));
}

/************************* PRINT NON PRINTABLE *************************/
/**
 * print_non_printable - Prints ASCII codes in hexadecimal for non-printable characters
 * @types: List of arguments
 * @buffer: Buffer array for printing
 * @flags: Calculate active flags
 * @width: Width specification
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of characters printed
 */
int print_non_printable(va_list types, char buffer[],
    int flags, int width, int precision, int size)
{
    int i = 0, offset = 0;
    char *str = va_arg(types, char *);

    UNUSED(flags);
    UNUSED(width);
    UNUSED(precision);
    UNUSED(size);

    if (str == NULL)
        return (write(1, "(null)", 6));

    while (str[i] != '\0')
    {
        if (is_printable(str[i]))
            buffer[i + offset] = str[i];
        else
            offset += append_hexadecimal_code(str[i], buffer, i + offset);

        i++;
    }

    buffer[i + offset] = '\0';

    return (write(1, buffer, i + offset));
}

/************************* PRINT REVERSE *************************/
/**
 * print_reverse - Prints a reversed string.
 * @types: List of arguments
 * @buffer: Buffer array for printing
 * @flags: Calculate active flags
 * @width: Width specification
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of characters printed
 */

int print_reverse(va_list types, char buffer[],
    int flags, int width, int precision, int size)
{
    char *str;
    int i, count = 0;

    UNUSED(buffer);
    UNUSED(flags);
    UNUSED(width);
    UNUSED(size);

    str = va_arg(types, char *);

    if (str == NULL)
    {
        UNUSED(precision);

        str = ")Null(";
    }

    for (i = 0; str[i]; i++)
        ;

    for (i = i - 1; i >= 0; i--)
    {
        char character = str[i];

        write(1, &character, 1);
        count++;
    }
    return (count);
}

/************************* PRINT A STRING IN ROT13 *************************/
/**
 * print_rot13string - Prints a string in ROT13.
 * @types: List of arguments
 * @buffer: Buffer array for printing
 * @flags: Calculate active flags
 * @width: Width specification
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of characters printed
 */
int print_rot13string(va_list types, char buffer[],
    int flags, int width, int precision, int size)
{
    char x;
    char *str;
    unsigned int i, j;
    int count = 0;
    char in[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    char out[] = "NOPQRSTUVWXYZABCDEFGHIJKLMnopqrstuvwxyzabcdefghijklm";

    str = va_arg(types, char *);

    UNUSED(buffer);
    UNUSED(flags);
    UNUSED(width);
    UNUSED(precision);
    UNUSED(size);

    if (str == NULL)
        str = "(AHYY)";

    for (i = 0; str[i]; i++)
    {
        for (j = 0; in[j]; j++)
        {
            if (in[j] == str[i])
            {
                x = out[j];
                write(1, &x, 1);
                count++;
                break;
            }
        }
        if (!in[j])
        {
            x = str[i];
            write(1, &x, 1);
            count++;
        }
    }
    return (count);
}
