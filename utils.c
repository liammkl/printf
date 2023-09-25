#include "main.h"

/**
 * is_printable - Checks if a character is printable
 * @c: The character to evaluate.
 *
 * Return: Returns 1 if 'c' is a printable character, otherwise returns 0.
 */
int is_printable(char c)
{
    if (c >= 32 && c < 127)
        return 1;

    return 0;
}

/**
 * append_hexa_code - Appends the hexadecimal representation of an ASCII code to a buffer
 * @buffer: The character array where the hexadecimal code is added.
 * @i: The index at which appending starts.
 * @ascii_code: The ASCII code to be converted to hexadecimal.
 * 
 * Return: Always returns 3.
 */
int append_hexa_code(char ascii_code, char buffer[], int i)
{
    char map_to[] = "0123456789ABCDEF";
    /* The hexadecimal format code is always 2 digits long */
    if (ascii_code < 0)
        ascii_code *= -1;

    buffer[i++] = '\\';
    buffer[i++] = 'x';

    buffer[i++] = map_to[ascii_code / 16];
    buffer[i] = map_to[ascii_code % 16];

    return 3;
}

/**
 * is_digit - Checks if a character is a digit
 * @c: The character to evaluate.
 *
 * Return: Returns 1 if 'c' is a digit, otherwise returns 0.
 */
int is_digit(char c)
{
    if (c >= '0' && c <= '9')
        return 1;

    return 0;
}

/**
 * convert_size_number - Casts a number to a specified size
 * @num: The number to be casted.
 * @size: The size indicator for the type to be casted.
 *
 * Return: The casted value of 'num'.
 */
long int convert_size_number(long int num, int size)
{
    if (size == S_LONG)
        return num;
    else if (size == S_SHORT)
        return (short)num;

    return (int)num;
}

/**
 * convert_size_unsgnd - Casts an unsigned number to a specified size
 * @num: The unsigned number to be casted.
 * @size: The size indicator for the type to be casted.
 *
 * Return: The casted value of 'num'.
 */
long int convert_size_unsgnd(unsigned long int num, int size)
{
    if (size == S_LONG)
        return num;
    else if (size == S_SHORT)
        return (unsigned short)num;

    return (unsigned int)num;
}
