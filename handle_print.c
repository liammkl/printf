#include "main.h"

/**
 * handle_print - Print an argument based on its format specifier
 * @fmt: The format string for printing arguments
 * @ind: Current index in the format string
 * @list: List of arguments
 * @buffer: Buffer array for printing
 * @flags: Active flags for formatting
 * @width: Width specification
 * @precision: Precision specification
 * @size: Size specifier
 *
 * Return: Number of characters printed
 */
int handle_print(const char *fmt, int *ind, va_list list, char buffer[],
	int flags, int width, int precision, int size)
{
	int i, unknownLength = 0, printedChars = -1;
	fmt_t fmtTypes[] = {
		{'c', print_char}, {'s', print_string}, {'%', print_percent},
		{'i', print_int}, {'d', print_int}, {'b', print_binary},
		{'u', print_unsigned}, {'o', print_octal}, {'x', print_hexadecimal},
		{'X', print_hexa_upper}, {'p', print_pointer}, {'S', print_non_printable},
		{'r', print_reverse}, {'R', print_rot13string}, {'\0', NULL}
	};

	for (i = 0; fmtTypes[i].fmt != '\0'; i++)
	{
		if (fmt[*ind] == fmtTypes[i].fmt)
		{
			return fmtTypes[i].fn(list, buffer, flags, width, precision, size);
		}
	}

	if (fmtTypes[i].fmt == '\0')
	{
		if (fmt[*ind] == '\0')
		{
			return -1;
		}

		unknownLength += write(1, "%%", 1);

		if (fmt[*ind - 1] == ' ')
		{
			unknownLength += write(1, " ", 1);
		}
		else if (width)
		{
			--(*ind);

			while (fmt[*ind] != ' ' && fmt[*ind] != '%')
			{
				--(*ind);
			}

			if (fmt[*ind] == ' ')
			{
				--(*ind);
			}

			return 1;
		}

		unknownLength += write(1, &fmt[*ind], 1);
		return unknownLength;
	}

	return printedChars;
}
