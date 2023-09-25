#include "main.h"
#include <unistd.h>
#include <stdarg.h>
#include <stdio.h>
#include <ctype.h>

/**
 * _printf - Produces output according to a format.
 * @format: The format string.
 * @...: The arguments.
 *
 * Return: The number of characters printed.
 */
int _printf(const char *format, ...)
{
    va_list args;
    int count = 0;
    int i = 0;

    va_start(args, format);

    while (format && format[i])
    {
        if (format[i] == '%')
        {
            if (format[i + 1] == '\0')
                return (-1);
            else if (format[i + 1] == '%')
            {
                write(1, &format[i], 1);
                count++;
                i++;
            }
            else if (format[i + 1] == 'c')
            {
                char c = va_arg(args, int);
                write(1, &c, 1);
                count++;
                i++;
            }
            else if (format[i + 1] == 's')
            {
                char *str = va_arg(args, char *);
                int j = 0;

                if (!str)
                    str = "(null)";

                while (str[j])
                {
                    write(1, &str[j], 1);
                    count++;
                    j++;
                }
                i++;
            }
            else if (format[i + 1] == 'd' || format[i + 1] == 'i')
            {
                int num = va_arg(args, int);
                char buffer[12]; // Assuming a maximum integer of 32 bits
                int j = 0;

                if (num < 0)
                {
                    write(1, "-", 1);
                    count++;
                    num = -num;
                }

                do
                {
                    buffer[j] = num % 10 + '0';
                    num /= 10;
                    j++;
                } while (num > 0);

                while (j--)
                {
                    write(1, &buffer[j], 1);
                    count++;
                }

                i++;
            }
            else if (format[i + 1] == 'u')
            {
                unsigned int num = va_arg(args, unsigned int);
                char buffer[12]; // Assuming a maximum unsigned integer of 32 bits
                int j = 0;

                do
                {
                    buffer[j] = num % 10 + '0';
                    num /= 10;
                    j++;
                } while (num > 0);

                while (j--)
                {
                    write(1, &buffer[j], 1);
                    count++;
                }

                i++;
            }
            else if (format[i + 1] == 'o')
            {
                unsigned int num = va_arg(args, unsigned int);
                char buffer[12]; // Assuming a maximum unsigned integer of 32 bits
                int j = 0;

                do
                {
                    buffer[j] = (num % 8) + '0';
                    num /= 8;
                    j++;
                } while (num > 0);

                while (j--)
                {
                    write(1, &buffer[j], 1);
                    count++;
                }

                i++;
            }
            else if (format[i + 1] == 'x' || format[i + 1] == 'X')
            {
                unsigned int num = va_arg(args, unsigned int);
                char buffer[12]; // Assuming a maximum unsigned integer of 32 bits
                int j = 0;
                char hex_digits[] = "0123456789abcdef";

                do
                {
                    buffer[j] = hex_digits[num % 16];
                    num /= 16;
                    j++;
                } while (num > 0);

                if (format[i + 1] == 'X')
                {
                    for (int k = 0; k < j; k++)
                        buffer[k] = toupper(buffer[k]);
                }

                while (j--)
                {
                    write(1, &buffer[j], 1);
                    count++;
                }

                i++;
            }
            else if (format[i + 1] == 'S')
            {
                char *str = va_arg(args, char *);
                int j = 0;

                if (!str)
                    str = "(null)";

                while (str[j])
                {
                    if (str[j] >= 32 && str[j] < 127)
                    {
                        write(1, &str[j], 1);
                        count++;
                    }
                    else
                    {
                        char hex_digit1 = (str[j] >> 4) & 0xF;
                        char hex_digit2 = str[j] & 0xF;
                        write(1, "\\x", 2);
                        write(1, &hex_digits[hex_digit1], 1);
                        write(1, &hex_digits[hex_digit2], 1);
                        count += 4;
                    }
                    j++;
                }

                i++;
            }
            else if (format[i + 1] == 'p')
            {
                void *ptr = va_arg(args, void *);
                unsigned long int num = (unsigned long int)ptr;
                char buffer[16]; // Assuming a maximum pointer size of 64 bits
                int j = 0;
                char hex_digits[] = "0123456789abcdef";

                write(1, "0x", 2);
                count += 2;

                do
                {
                    buffer[j] = hex_digits[num % 16];
                    num /= 16;
                    j++;
                } while (num > 0);

                for (int k = j - 1; k >= 0; k--)
                {
                    write(1, &buffer[k], 1);
                    count++;
                }

                i++;
            }
            else if (format[i + 1] == 'r')
            {
                char *str = va_arg(args, char *);
                int len = 0;

                if (!str)
                    str = "(null)";

                while (str[len])
                    len++;

                for (int j = len - 1; j >= 0; j--)
                {
                    write(1, &str[j], 1);
                    count++;
                }

                i++;
            }
            else if (format[i + 1] == 'R')
            {
                char *str = va_arg(args, char *);
                int j = 0;

                if (!str)
                    str = "(null)";

                while (str[j])
                {
                    char c = str[j];
                    if ((c >= 'a' && c <= 'm') || (c >= 'A' && c <= 'M'))
                        c += 13;
                    else if ((c >= 'n' && c <= 'z') || (c >= 'N' && c <= 'Z'))
                        c -= 13;

                    write(1, &c, 1);
                    count++;
                    j++;
                }

                i++;
            }
            // Add support for other features like flag characters, field width, precision, and length modifiers here
            // ...
        }
        else
        {
            write(1, &format[i], 1);
            count++;
        }
        i++;
    }

    va_end(args);
    return (count);
}
