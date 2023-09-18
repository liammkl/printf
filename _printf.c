#include <stdarg.h>
#include <unistd.h>

/**
 * _printf - Custom printf function
 * @format: The format string
 * @...: Additional arguments based on format
 *
 * Return: Number of characters printed (excluding null byte)
 */
int _printf(const char *format, ...)
{
	va_list args;
	int char_count = 0;
	
	va_start(args, format);
	while (*format)
	{
		if (*format == '%')
		{
			format++;
			switch (*format)
			{
				case 'c':
					char_count += write(1, &va_arg(args, int), 1);
					break;
				case 's':
					{
						char *str = va_arg(args, char *);
						int len = 0;
						if (str == NULL)
							str = "(null)";
						while (str[len])
							len++;
						char_count += write(1, str, len);
					}
					break;
				case '%':
					char_count += write(1, "%", 1);
					break;
				default:
					write(1, "%", 1);
					write(1, format, 1);
					char_count += 2;
					break;
			}
		}
		else
		{
			write(1, format, 1);
			char_count++;
		}
		format++;
	}
	va_end(args);
	return char_count;
}
