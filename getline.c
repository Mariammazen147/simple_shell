#include "shell.h"

/**
* _getline - read one line.
* @data: struct of data
*
* Return: counting bytes.
*/
int _getline(data_of_program *data)
{
	char buff[BUFFER_SIZE] = {'\0'};
	static char *array_commands[10] = {NULL};
	static char array_operators[10] = {'\0'};
	ssize_t read_bytes, i = 0;

	if (!array_commands[0] || (array_operators[0] == '&' && errno != 0) ||
		(array_operators[0] == '|' && errno == 0))
	{
		for (i = 0; array_commands[i]; i++)
		{
			free(array_commands[i]);
			array_commands[i] = NULL;
		}

		read_bytes = read(data->file_descriptor, &buff, BUFFER_SIZE - 1);
		if (read_bytes == 0)
			return (-1);

		i = 0;
		do {
			array_commands[i] = str_duplicate(_strtok(i ? NULL : buff, "\n;"));
			i = check_logic_ops(array_commands, i, array_operators);
		} while (array_commands[i++]);
	}

	data->input_line = array_commands[0];
	for (i = 0; array_commands[i]; i++)
	{
		array_commands[i] = array_commands[i + 1];
		array_operators[i] = array_operators[i + 1];
	}

	return (str_length(data->input_line));
}


/**
* check_logic_ops - checks && and || operators
* @array_commands: commands.
* @i: index in array_commands that is to be checked
* @array_operators: logical operators for each previous command
*
* Return: last command's index in the array_commands.
*/
int check_logic_ops(char *array_commands[], int i, char array_operators[])
{
	char *temp = NULL;
	int k;

	for (k = 0; array_commands[i] != NULL  && array_commands[i][k]; k++)
	{
		if (array_commands[i][k] == '&' && array_commands[i][k + 1] == '&')
		{
			temp = array_commands[i];
			array_commands[i][k] = '\0';
			array_commands[i] = str_duplicate(array_commands[i]);
			array_commands[i + 1] = str_duplicate(temp + k + 2);
			i++;
			array_operators[i] = '&';
			free(temp);
			k = 0;
		}
		if (array_commands[i][k] == '|' && array_commands[i][k + 1] == '|')
		{
			temp = array_commands[i];
			array_commands[i][k] = '\0';
			array_commands[i] = str_duplicate(array_commands[i]);
			array_commands[i + 1] = str_duplicate(temp + k + 2);
			i++;
			array_operators[i] = '|';
			free(temp);
			k = 0;
		}
	}
	return (i);
}
