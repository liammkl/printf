#include "main.h"
#include <stdarg.h>
#include <unistd.h>

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
			else if (*format == '%')
			{
				printed_chars += write(1, "%", 1);
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
