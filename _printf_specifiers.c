#include "main.h"
#include <stdarg.h>
#include <unistd.h>

int _print_number(int n);

/**
 * _printf - Produces output according to a format.
 * @format: The format string.
 *
 * Return: The number of characters printed (excluding the null byte).
 */
int _printf(const char *format, ...)
{
	va_list args;
	int printed_chars = 0;
	va_start(args, format);
	while (*format)
	{
		if (*format == '%')
		{
			format++;
			if (*format == '\0')
				break;
			
			if (*format == 'c')
			{
				int c = va_arg(args, int);
				printed_chars += write(1, &c, 1);
			}
			else if (*format == 's')
			{
				char *str = va_arg(args, char *);
				if (str == NULL)
					str = "(null)";
				while (*str)
				{
					printed_chars += write(1, str, 1);
					str++;
				}
			}
			else if (*format == 'd' || *format == 'i')
			{
				int num = va_arg(args, int);
				printed_chars += _print_number(num);
			}
			else
			{
				printed_chars += write(1, "%", 1);
				printed_chars += write(1, format, 1);
			}
		}
		else
		{
			printed_chars += write(1, format, 1);
		}
		format++;
	}
	va_end(args);
	return (printed_chars);
}

/**
 * _print_number - Prints an integer.
 * @n: The integer to print.
 *
 * Return: The number of characters printed.
 */
int _print_number(int n)
{
	int printed_chars = 0;
	
	char digit;
	if (n < 0)
	{
		printed_chars += write(1, "-", 1);
		n = -n;
	}
	if (n / 10)
		printed_chars += _print_number(n / 10);
	
	digit = (n % 10) + '0';
	printed_chars += write(1, &digit, 1);
	
	return (printed_chars);
}
