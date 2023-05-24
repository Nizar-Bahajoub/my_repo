#include "main.h"

/**
 * check_alias - Checks if an alias exists
 * @neww: List of arguments
 * Return: Name of alias if it exists, NULL otherwise
 */
char *check_alias(char *neww)
{
	alias *temp = get_alias_list();

	while (temp != NULL)
	{
		if (_strcmp(neww, temp->new_command) == 0)
		{
			return (temp->new_command);
		}
		temp = temp->next;
	}
	return (NULL);
}

/**
 * execute_alias - Executes an alias command
 * @main: Main command
 * @args: List of arguments
 * Return: Always 0 (Success)
 */
int execute_alias(char *main, char **args)
{
	if (execve(main, args, environ) == -1)
	{
		fprintf(stderr, "%s: No such file or directory\n", args[0]);
		exit(EXIT_FAILURE);
	}
	return (0);
}

/**
 * create_keyvalue_pair - Creates an alias key-value pair
 * @name: Argument to be initialized into the name_command
 * @alias_list: Pointer to the alias list
 * @equals: Pointer to the '=' in the args
 * Return: 0 on success, -1 on failure
 */
int create_keyvalue_pair(alias **alias_list, char *name, char *equals)
{
	alias *list_copy = *alias_list;
	int i, b = 0, j, value_length;
	char *main_command, *new_command = malloc((strlen(name) + 1) * sizeof(char));

	while (name[b] != '=')
	{
		new_command[b] = name[b];
		b++;
	}

	*equals = '\0';
	equals = equals + 1;

	printf("Now allocating memory for value_command equals = %s\n", equals);
	value_length = strlen(equals) - strspn(equals, "'\"");
	main_command = malloc(sizeof(char) * (value_length + 1));

	printf("Now Entering Initialization loop\n");
	for (i = 0, j = 0; equals[i] != '\0'; i++)
	{
		if (equals[i] != '\'' && equals[i] != '"')
		{
			main_command[j] = equals[i];
			j++;
		}
	}
	main_command[j] = '\0';

	printf(" Before adding : name = %s, value = %s\n", new_command, main_command);
	*alias_list = add_alias(&list_copy, new_command, main_command);

	return (0);
}

/**
 * add_alias - Adds an alias to the list
 * @head: Pointer to the head of the alias list
 * @new: Name of the new command
 * @main: Name of the main command
 * Return: Pointer to the head of the alias list
 */
alias *add_alias(alias **head, char *new, char *main)
{
	alias *new_node = malloc(sizeof(alias));
	alias *temp;

	new_node->main_command = strdup(main);
	new_node->new_command = strdup(new);
	new_node->next = NULL;

	if (*head == NULL)
	{
		*head = new_node;
	}
	else
	{
		temp = *head;
		while (temp->next != NULL)
		{
			if (strcmp(new, temp->new_command) == 0)
			{
				free(temp->main_command);
				temp->main_command = strdup(main);
				free(new_node->main_command);
				free(new_node->new_command);
				return (*head);
			}
			temp = temp->next;
		}
		temp->next = new_node;
	}
	printf("Added Alias to the list successfully \n");

	temp = *head;
	while (temp != NULL)
	{
		printf("Alias: %s='%s'\n", temp->new_command, temp->main_command);
		temp = temp->next;
	}
	return (*head);
}

/**
 * print_alias_list - Prints the alias list
 * @head: Pointer to the head of the alias list
 * Return: Always 0 (Success)
 */
int print_alias_list(alias *head)
{
	alias *temp = head;

	while (temp != NULL)
	{
		printf("Alias: %s='%s'\n", temp->new_command, temp->main_command);
		temp = temp->next;
	}
	printf(" Printed list successfully \n");

	return (0);
}
