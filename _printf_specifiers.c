#include "main.h"
#include <unistd.h>
#include <stdarg.h>

/**
 * _printf - Custom printf function
 * @format: The format string
 * Return: Number of characters printed
 */
int _printf(const char *format, ...)
{
	va_list args;
	int count = 0;

	va_start(args, format);

	while (*format)
	{
		if (*format == '%' && (*(format + 1) == 'd' || *(format + 1) == 'i'))
		{
			int num = va_arg(args, int);
			char buffer[12];
			int len = 0;

			if (num < 0)
			{
				write(1, "-", 1);
				num = -num;
				count++;
			}

			while (num > 0)
			{
				buffer[len++] = '0' + (num % 10);
				num /= 10;
			}

			while (len > 0)
			{
				write(1, &buffer[--len], 1);
				count++;
			}

			format += 2;
		}
		else
		{
			write(1, format, 1);
			count++;
			format++;
		}
	}

	va_end(args);
	return count;
}
