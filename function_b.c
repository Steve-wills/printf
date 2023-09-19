#include "main.h"

/**
 * print_unsigned - Prints an unsigned number
 * @arglist: List of arguments
 * @buffer: A buffer array to handle print
 * @flags:  Calculates active flags
 * @width: width
 * @acc: Accuracy
 * @size: Size specifier
 * Return: Number of chars printed.
 */
int print_unsigned(va_list arglist, char buffer[],
	int flags, int width, int acc, int size)
{
	int i = BUFF_SIZE - 2;
	unsigned long int num = va_arg(arglist, unsigned long int);

	num = convert_size_unsgnd(num, size);

	if (num == 0)
		buffer[i--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';

	while (num > 0)
	{
		buffer[i--] = (num % 10) + '0';
		num /= 10;
	}

	i++;

	return (write_unsgnd(0, i, buffer, flags, width, acc, size));
}

/**
 * print_octal - Prints an unsigned number in octal notation
 * @arglist: List of arguments
 * @buffer: A buffer array to handle print
 * @flags:  Calculates active flags
 * @width: width
 * @acc: Accuracy
 * @size: Size
 * Return: Number of characters printed
 */
int print_octal(va_list arglist, char buffer[],
	int flags, int width, int acc, int size)
{

	int i = BUFF_SIZE - 2;
	unsigned long int num = va_arg(arglist, unsigned long int);
	unsigned long int initNum = num;

	UNUSED(width);

	num = convert_size_unsgnd(num, size);

	if (num == 0)
		buffer[i--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';

	while (num > 0)
	{
		buffer[i--] = (num % 8) + '0';
		num /= 8;
	}

	if (flags & F_HASH && initNum != 0)
		buffer[i--] = '0';

	i++;

	return (write_unsgnd(0, i, buffer, flags, width, acc, size));
}

/**
 * print_hexadecimal - Prints an unsigned number in hexadecimal notation
 * @arglist: Lists arguments
 * @buffer: A buffer array to handle print
 * @flags:  Calculates active flags
 * @width: width
 * @acc: Accuracy
 * @size: Size
 * Return: Number of chars printed
 */
int print_hexadecimal(va_list arglist, char buffer[],
	int flags, int width, int acc, int size)
{
	return (print_hexa(types, "0123456789abcdef", buffer,
		flags, 'x', width, acc, size));
}

/**
 * print_hexa_upper - Prints an unsigned number in upper hexadecimal notation
 * @arglist: Lists arguments
 * @buffer: A buffer array to handle print
 * @flags:  Calculates active flags
 * @width: width
 * @acc: Accuracy
 * @size: Size
 * Return: Number of chars printed
 */
int print_hexa_upper(va_list arglist, char buffer[],
	int flags, int width, int acc, int size)
{
	return (print_hexa(arglist, "0123456789ABCDEF", buffer,
		flags, 'X', width, acc, size));
}

/**
 * print_hexa - Prints a hexadecimal number in lower or upper
 * @arglist: Lists arguments
 * @map_to: Array of values to map the number to
 * @buffer: A buffer array to handle print
 * @flags:  Calculates active flags
 * @flag_ch: Calculates active flags
 * @width: get width
 * @acc : Accuracy
 * @size: Size specifier
 * @size: Size specification
 * Return: Number of chars printed
 */
int print_hexa(va_list arglist, char map_to[], char buffer[],
	int flags, char flag_ch, int width, int acc, int size)
{
	int j = BUFF_SIZE - 2;
	unsigned long int num = va_arg(arglist, unsigned long int);
	unsigned long int initNum = num;

	UNUSED(width);

	num = convert_size_unsgnd(num, size);

	if (num == 0)
		buffer[j--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';

	while (num > 0)
	{
		buffer[j--] = map_to[num % 16];
		num /= 16;
	}

	if (flags & F_HASH && initNum != 0)
	{
		buffer[j--] = flag_ch;
		buffer[j--] = '0';
	}

	j++;

	return (write_unsgnd(0, j, buffer, flags, width, acc, size));
}
