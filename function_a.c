#include "main.h"

/**
 * print_char - Prints a character
 * @arglist: Lists arguments
 * @buffer: A buffer array to handle printed characters
 * @flags:  Calculates active flags
 * @width: Width
 * @acc: Accuracy
 * @size: Size
 * Return: Number of characters printed
 */
int print_char(va_list arglist, char buffer[],
	int flags, int width, int acc, int size)
{
	char ch = va_arg(arglist, int);

	return (write_char(ch, buffer, flags, width, acc, size));
}

/**
 * print_string - Prints a string
 * @arglist: Lists arguments
 * @buffer: A buffer array to handle print
 * @flags:  Calculates active flags
 * @width: width
 * @acc: Accuracy
 * @size: Size
 * Return: Number of chars printed
 */
int print_string(va_list arglist, char buffer[],
	int flags, int width, int acc, int size)
{
	int len = 0, i;
	char *str = va_arg(arglist, char *);

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(acc);
	UNUSED(size);
	if (str == NULL)
	{
		str = "(null)";
		if (acc >= 6)
			str = "      ";
	}

	while (str[len] != '\0')
		len++;

	if (acc >= 0 && acc < len)
		len = acc;

	if (width > len)
	{
		if (flags & F_MINUS)
		{
			write(1, &str[0], len);
			for (i = width - len; i > 0; i--)
				write(1, " ", 1);
			return (width);
		}
		else
		{
			for (i = width - len; i > 0; i--)
				write(1, " ", 1);
			write(1, &str[0], len);
			return (width);
		}
	}

	return (write(1, str, len));
}

/**
 * print_percent - Prints a percent sign
 * @arglist: Lists arguments
 * @buffer: A buffer array to handle print
 * @flags:  Calculates active flags
 * @width: width.
 * @acc: Accuracy
 * @size: Size
 * Return: Number of characters printed
 */
int print_percent(va_list arglist, char buffer[],
	int flags, int width, int acc, int size)
{
	UNUSED(arglist);
	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(acc);
	UNUSED(size);
	return (write(1, "%%", 1));
}

/**
 * print_int - Print int
 * @arglist: Lists arguments
 * @buffer: A buffer array to handle print
 * @flags:  Calculates active flags
 * @width: width.
 * @acc: Accuracy
 * @size: Size
 * Return: Number of characters printed
 */
int print_int(va_list arglist, char buffer[],
	int flags, int width, int acc, int size)
{
	int i = BUFF_SIZE - 2;
	int is_negative = 0;
	long int n = va_arg(arglist, long int);
	unsigned long int num;

	n = convert_size_number(n, size);

	if (n == 0)
		buffer[i--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';
	num = (unsigned long int)n;

	if (n < 0)
	{
		num = (unsigned long int)((-1) * n);
		is_negative = 1;
	}

	while (num > 0)
	{
		buffer[i--] = (num % 10) + '0';
		num /= 10;
	}

	i++;

	return (write_number(is_negative, i, buffer, flags, width, acc, size));
}

/**
 * print_binary - Prints an unsigned number
 * @arglist: List of arguments
 * @buffer: A buffer array to handle print
 * @flags:  Calculates active flags
 * @width: Get width.
 * @acc: Accuracy
 * @size: Size specifier
 * Return: Numbers of char printed.
 */
int print_binary(va_list arglist, char buffer[],
	int flags, int width, int acc, int size)
{
	unsigned int k, j, i, sum;
	unsigned int a[32];
	int counts;

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(acc);
	UNUSED(size);

	k = va_arg(arglist, unsigned int);
	j = 2147483648;
	a[0] = k / j;
	for (i = 1; i < 32; i++)
	{
		j /= 2;
		a[i] = (k / j) % 2;
	}
	for (i = 0, sum = 0, counts = 0; i < 32; i++)
	{
		sum += a[i];
		if (sum || i == 31)
		{
			char z = '0' + a[i];

			write(1, &z, 1);
			counts++;
		}
	}
	return (counts);
}
