#ifndef MAIN_H
#define MAIN_H

#include <stdarg.h>

/**
 * struct print_fn - Struct to match a specifier with its corresponding function
 * @specifier: The format specifier
 * @fn: The function to handle the specifier
 */
typedef struct print_fn
{
    char specifier;
    int (*fn)(va_list args);
} print_fn_t;

int _printf(const char *format, ...);

int print_char(va_list args);
int print_string(va_list args);
int print_int(va_list args);
int print_unsigned_int(va_list args);
int print_octal(va_list args);
int print_hex(va_list args);
int print_HEX(va_list args);
int print_binary(va_list args);
int print_S(va_list args);
int print_pointer(va_list args);
int print_reverse(va_list args);
int print_rot13(va_list args);

#endif
