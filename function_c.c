#include "main.h"

/**
 * print_pointer - Prints the value of a pointer variable
 * @arglist: Lists arguments
 * @buffer: A buffer array to handle print
 * @flags:  Calculates active flags
 * @width: width
 * @acc: Accuracy
 * @size: Size
 * Return: Number of chars printed.
 */
int print_pointer(va_list arglist, char buffer[],
	int flags, int width, int acc, int size)
{
	char extra_c = 0, padd = ' ';
	int ind = BUFF_SIZE - 2, length = 2, padd_start = 1;
	unsigned long numAddr;
	char map_to[] = "0123456789abcdef";
	void *addr = va_arg(arglist, void *);

	UNUSED(width);
	UNUSED(size);

	if (addr == NULL)
		return (write(1, "(nil)", 5));

	buffer[BUFF_SIZE - 1] = '\0';
	UNUSED(acc);

	numAddr = (unsigned long)addr;

	while (numAddr > 0)
	{
		buffer[ind--] = map_to[numAddr % 16];
		numAddr /= 16;
		length++;
	}

	if ((flags & F_ZERO) && !(flags & F_MINUS))
		padd = '0';
	if (flags & F_PLUS)
		extra_c = '+', length++;
	else if (flags & F_SPACE)
		extra_c = ' ', length++;

	ind++;

	/*return (write(1, &buffer[i], BUFF_SIZE - i - 1));*/
	return (write_pointer(buffer, ind, length,
		width, flags, padd, extra_c, padd_start));
}

/**
 * print_non_printable - Prints ascii codes in hexa of non printable chars
 * @arglist: List of arguments
 * @buffer: A buffer array to handle print
 * @flags:  Calculates active flags
 * @width: width
 * @acc: Accuracy
 * @size: Size
 * Return: Number of chars printed
 */
int print_non_printable(va_list arglist, char buffer[],
	int flags, int width, int acc, int size)
{
	int i = 0, offset = 0;
	char *str = va_arg(arglist, char *);

	UNUSED(flags);
	UNUSED(width);
	UNUSED(acc);
	UNUSED(size);

	if (str == NULL)
		return (write(1, "(null)", 6));

	while (str[i] != '\0')
	{
		if (is_printable(str[i]))
			buffer[i + offset] = str[i];
		else
			offset += append_hexa_code(str[i], buffer, i + offset);

		i++;
	}

	buffer[i + offset] = '\0';

	return (write(1, buffer, i + offset));
}

/**
 * print_reverse - Prints reverse string.
 * @arglist: Lists arguments
 * @buffer: A buffer array to handle print
 * @flags:  Calculates active flags
 * @width: get width
 * @acc: Accuracy
 * @size: Size
 * Return: Numbers of chars printed
 */

int print_reverse(va_list arglist, char buffer[],
	int flags, int width, int acc, int size)
{
	char *str;
	int i, counter = 0;

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(size);

	str = va_arg(arglist, char *);

	if (str == NULL)
	{
		UNUSED(acc);

		str = ")Null(";
	}
	for (i = 0; str[i]; i++)
		;

	for (i = i - 1; i >= 0; i--)
	{
		char z = str[i];

		write(1, &z, 1);
		counter++;
	}
	return (counter);
}

/**
 * print_rot13string - Print a string in rot13.
 * @arglist: Lists arguments
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: get width
 * @acc: Accuracy
 * @size: Size
 * Return: Numbers of chars printed
 */
int print_rot13string(va_list arglist, char buffer[],
	int flags, int width, int acc, int size)
{
	char x;
	char *str;
	unsigned int i, j;
	int counts = 0;
	char input[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	char output[] = "NOPQRSTUVWXYZABCDEFGHIJKLMnopqrstuvwxyzabcdefghijklm";

	str = va_arg(arglist, char *);
	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(acc);
	UNUSED(size);

	if (str == NULL)
		str = "(AHYY)";
	for (i = 0; str[i]; i++)
	{
		for (j = 0; input[j]; j++)
		{
			if (input[j] == str[i])
			{
				x = output[j];
				write(1, &x, 1);
				counts++;
				break;
			}
		}
		if (!input[j])
		{
			x = str[i];
			write(1, &x, 1);
			counts++;
		}
	}
	return (counts);
}
