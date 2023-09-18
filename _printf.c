#include "main.h"
#include <stdarg.h>
#include <unistd.h>

/**
 * _printf - Printf function
 * @format: The format string
 *
 * Return: The number of printed characters
 */

int _printf(const char *format, ...)
{
	int count = 0;
	va_list args;

	if (format == NULL)
		return (-1);
	va_start(args, format);
	while (*format)
	{
		if (*format != '%')
		{
			write(1, format, 1);
			count++;
		}
		else
		{
			format++;
			if (*format == '\0')
				return (-1);
			if (*format == 'c')
			{
				char c = va_arg(args, int);

				write(1, &c, 1);
				count++;
			}
			else if (*format == 's')
			{
				char *s = va_arg(args, char *);
				if (s == NULL)
					s = "(null)";
				while (*s)
				{
					write(1, s, 1);
					s++;
					count++;
				}
			}
			else if (*format == '%')
			{
				write(1, "%", 1);
				count++;
			}
			else
				return (-1);
		}
		format++;
	}
	va_end(args);
	return (count);
}
