#include "shell.h"

/**
 * print_alias - prints the alias
 * @data: struct of data
 * @alias: alias' name
 * Return: successful = (0)
 */
int print_alias(data_of_program *data, char *alias)
{
	int i, j, len;
	char buffer[250] = {'\0'};

	if (data->alias_list)
	{
		len = str_length(alias);
		for (i = 0; data->alias_list[i]; i++)
		{
			if (!alias || (str_compare(data->alias_list[i], alias, len)
				&&	data->alias_list[i][len] == '='))
			{
				for (j = 0; data->alias_list[i][j]; j++)
				{
					buffer[j] = data->alias_list[i][j];
					if (data->alias_list[i][j] == '=')
						break;
				}
				buffer[j + 1] = '\0';
				buffer_add(buffer, "'");
				buffer_add(buffer, data->alias_list[i] + j + 1);
				buffer_add(buffer, "'\n");
				_print(buffer);
			}
		}
	}

	return (0);
}

/**
 * get_alias - gets the alias
 * @data: struct of data
 * @name: alias' name.
 * Return: successful = (0)
 */
char *get_alias(data_of_program *data, char *name)
{
	int i, len;

	if (name == NULL || data->alias_list == NULL)
		return (NULL);

	len = str_length(name);

	for (i = 0; data->alias_list[i]; i++)
	{
		if (str_compare(name, data->alias_list[i], len) &&
			data->alias_list[i][len] == '=')
		{
			return (data->alias_list[i] + len + 1);
		}
	}
	return (NULL);

}

/**
 * set_alias - Sets or updates an alias in the program's data.
 * @alias_string: The alias string to be set or updated.
 * @data: Pointer to the program's data structure.
 *
 * Returns:
 *  - 0 on success.
 *  - 1 if arguments are invalid.
 */
int set_alias(char *alias_string, data_of_program *data)
{
	int i, k;
	char buffer[250] = {'0'}, *temp = NULL;

	if (alias_string == NULL ||  data->alias_list == NULL)
		return (1);
	for (i = 0; alias_string[i]; i++)
		if (alias_string[i] != '=')
			buffer[i] = alias_string[i];
		else
		{
			temp = get_alias(data, alias_string + i + 1);
			break;
		}

	for (k = 0; data->alias_list[k]; k++)
		if (str_compare(buffer, data->alias_list[k], i) &&
			data->alias_list[k][i] == '=')
		{
			free(data->alias_list[k]);
			break;
		}

	if (temp)
	{
		buffer_add(buffer, "=");
		buffer_add(buffer, temp);
		data->alias_list[k] = str_duplicate(buffer);
	}
		data->alias_list[k] = str_duplicate(alias_string);
	return (0);
}
