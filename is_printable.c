#include "main.h"

/**
 * is_printable - Assesses if a char is printable
 * @c: Char to be assessed.
 *
 * Return: 1 if c is printable, 0 otherwise
 */
int is_printable(char c)
{
	if (c >= 32 && c < 127)
		return (1);

	return (0);
}

/**
 * append_hexa_code - Append ascii in hexadecimal code to buffer
 * @buffer: A buffer array to handle print
 * @i: Index at which to start appending.
 * @ascii_code: ASCII CODE.
 * Return: Always 3
 */
int append_hexa_code(char ascii_code, char buffer[], int i)
{
	char map_to[] = "0123456789ABCDEF";

	if (ascii_code < 0)
		ascii_code *= -1;

	buffer[i++] = '\\';
	buffer[i++] = 'x';

	buffer[i++] = map_to[ascii_code / 16];
	buffer[i] = map_to[ascii_code % 16];

	return (3);
}

/**
 * is_digit - Confirms if a character is a digit
 * @c: Char to be assessed
 *
 * Return: 1 if c is a digit, 0 otherwise
 */
int is_digit(char c)
{
	if (c >= '0' && c <= '9')
		return (1);

	return (0);
}

/**
 * convert_size_number - Converts a number to the specified size
 * @number: Number to be converted.
 * @size: Number indicating the type to be converted.
 *
 * Return: Converted value of number
 */
long int convert_size_number(long int number, int size)
{
	if (size == S_LONG)
		return (number);
	else if (size == S_SHORT)
		return ((short)number);

	return ((int)number);
}

/**
 * convert_size_unsgnd - Converts a number to the specified size
 * @number: Number to be converted
 * @size: Number indicating the type to be converted
 *
 * Return: Converted value of number
 */
long int convert_size_unsgnd(unsigned long int number, int size)
{
	if (size == S_LONG)
		return (number);
	else if (size == S_SHORT)
		return ((unsigned short)number);

	return ((unsigned int)number);
}
