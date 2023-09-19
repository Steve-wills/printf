#include "main.h"

void print_buffer(char buffer[], int *buff_ind);

/**
 * _printf - Printf function
 * @format: format.
 * Return: Printed chars.
 */
int _printf(const char *format, ...)
{
	int i, print = 0, printChar = 0;
	int flags, width, acc, size, buff_ind = 0;
	va_list lists;
	char buffer[BUFF_SIZE];

	if (format == NULL)
		return (-1);

	va_start(lists, format);

	for (i = 0; format && format[i] != '\0'; i++)
	{
		if (format[i] != '%')
		{
			buffer[buff_ind++] = format[i];
			if (buff_ind == BUFF_SIZE)
				print_buffer(buffer, &buff_ind);
			printChar++;
		}
		else
		{
			print_buffer(buffer, &buff_ind);
			flags = get_flags(format, &i);
			width = get_width(format, &i, lists);
			acc = get_accuracy(format, &i, lists);
			size = get_size(format, &i);
			++i;
			print = handle_print(format, &i, lists, buffer,
				flags, width, acc, size);
			if (print == -1)
				return (-1);
			printChar += print;
		}
	}

	print_buffer(buffer, &buff_ind);

	va_end(lists);

	return (printChar);
}

/**
 * print_buffer - Prints the contents of the buffer if it exist
 * @buffer: A buffer array to handle printed characters
 * @buff_ind: Index to input next character, representing the length
 */
void print_buffer(char buffer[], int *buff_ind)
{
	if (*buff_ind > 0)
		write(1, &buffer[0], *buff_ind);

	*buff_ind = 0;
}
