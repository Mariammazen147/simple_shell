#include "shell.h"
/**
 * long_to_string - Converts a number to a string.
 *
 * @number: Number to be converted into a string.
 * @string: Buffer to save the number as a string.
 * @base: Base to convert the number.
 *
 * Return: Nothing.
 */
void long_to_string(long number, char *string, int base)
{
	int index = 0, inNegative = 0;
	long cociente = number;
	char letters[] = {"0123456789abcdef"};

	if (cociente == 0)
		string[index++] = '0';

	if (string[0] == '-')
		inNegative = 1;

	while (cociente)
	{
		if (cociente < 0)
			string[index++] = letters[-(cociente % base)];
		else
			string[index++] = letters[cociente % base];
		cociente /= base;
	}
	if (inNegative)
		string[index++] = '-';

	string[index] = '\0';
	str_reverse(string);
}

/**
 * _atoi - Convert a string to an integer.
 *
 * @s: Pointer to the string origin.
 *
 * Return: Integer representation of the string or 0.
 */
int _atoi(char *s)
{
	int sign = 1;
	unsigned int number = 0;
	while (!('0' <= *s && *s <= '9') && *s != '\0')
	{
		if (*s == '-')
			sign *= -1;
		if (*s == '+')
			sign *= +1;
		s++;
	}

	while ('0' <= *s && *s <= '9' && *s != '\0')
	{

		number = (number * 10) + (*s - '0');
		s++;
	}
	return (number * sign);
}

/**
 * count_characters - Count the coincidences of a character in a string.
 *
 * @string: Pointer to the string origin.
 * @character: String with characters to be counted.
 *
 * Return: Count of occurrences of the character in the string.
 */

int count_characters(char *string, char *character)
{
	int i = 0, counter = 0;

	for (; string[i]; i++)
	{
		if (string[i] == character[0])
			counter++;
	}
	return (counter);
}
