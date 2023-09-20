#include "shell.h"

/**
 * _myenv - prints the current environment
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int _myenv(info_t *info)
{
	print_list_str(info->env);
	return (0);
}

/**
 * _getenv - gets the value of an environ variable
 * @info: Structure containing potential arguments. Used to maintain
 * @name: env var name
 *
 * Return: the value
 */
char *_getenv(info_t *info, const char *name)
{
	list_t *node = info->env;
	char *p;

	while (node)
	{
		p = starts_with(node->str, name);
		if (p && *p)
			return (p);
		node = node->next;
	}
	return (NULL);
}

/**
 * _mysetenv - Initialize a new environment variable,
 *             or modify an existing one
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int _mysetenv(info_t *info)
{
	if (info->argc != 3)
	{
		_eputs("Incorrect number of arguements\n");
		return (1);
	}

	char *new_env_var = malloc(sizeof(char) * (_strlen(info->argv[1]) + _strlen(info->argv[2]) + 2));

	if (!new_env_var)
		return (1);

	_strcpy(new_env_var, info->argv[1]);
	_strcat(new_env_var, "=");
	_strcat(new_env_var, info->argv[2]);

	list_t *new_node = malloc(sizeof(list_t));

	if (!new_node)
		return (1);

	new_node->str = new_env_var;
	new_node->next = NULL;

	add_node_end(&(info->env), new_node->str, 0);

	return (0);
}

/**
 * _myunsetenv - Remove an environment variable
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * Return: Always 0
 */
int _myunsetenv(info_t *info)
{
	int i;

	if (info->argc == 1)
	{
		_eputs("Too few arguements.\n");
		return (1);
	}

	for (i = 1; i <= info->argc; i++)
	{
		list_t *node = info->env;
		list_t *prev = NULL;

		while (node)
		{
			if (_strcmp(node->str, info->argv[i]) == 0)
			{
				if (prev)
					prev->next = node->next;
				else
					info->env = node->next;

				free(node->str);
				free(node);

				break;
			}

			prev = node;
			node = node->next;
		}
	}

	return (0);
}

/**
 * populate_env_list - populates env linked list
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int populate_env_list(info_t *info)
{
	list_t *node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
	{
		list_t *new_node = malloc(sizeof(list_t));

		if (!new_node)
			return (1);

		new_node->str = environ[i];
		new_node->next = NULL;

		add_node_end(&node, new_node->str, 0);
	}

	info->env = node;
