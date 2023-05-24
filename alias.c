#include "main.h"

/**
 * my_alias - Handles the "alias" command
 * @args: List of commands
 * Return: Always 0 (Success)
 */
int my_alias(char **args)
{
	int i = 1;
	alias *list_copy = get_alias_list();
	char *equals;

	if (args[i] == NULL)
	{
		if (list_copy == NULL)
			printf("NULL\n");
		else
		{
			printf("Wants to enter print_alias_list\n");
			print_alias_list(list_copy);
		}
		return (0);
	}
	for (i = 1; args[i] != NULL; i++)
	{
		equals = strchr(args[i], '=');
		list_copy = get_alias_list();
		if (equals == NULL)
		{
			while (list_copy != NULL)
			{
				if (strcmp(args[i], list_copy->main_command) == 0)
				{
					print_alias_list(list_copy);
					break;
				}
				list_copy = list_copy->next;
			}
		}
		else
		{
			printf("Calling create_keyvalue_pair function. args = %s\n", args[i]);
			create_keyvalue_pair(&list_copy, args[i], equals);
		}
	}
	return (0);
}

/**
 * get_alias_list - Returns the alias list
 * Return: The alias list
 */
alias *get_alias_list(void)
{
	alias *alias_list = NULL;

	return (alias_list);
}
