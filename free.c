#include "main.h"

/**
 * _freeargs - Frees the arguments
 * @args: Tokenized arguments
 * Return: void
 */
void _freeargs(char **args)
{
	int index;
	int len = 0;

	while (args[len] != NULL)
		len++;

	for (index = 0; index < len; index++)
	{
		free(args[index]);
	}
}

/**
 * _freepath - Frees the path
 * @path: Pointer to the linked path
 * Return: void
 */
void _freepath(linked_path *path)
{
	linked_path *temp;

	while (path != NULL)
	{
		temp = path->next;
		free(path->dir);
		free(path);
		path = temp;
	}
}

/**
 * _freeenv - Frees the environment variables
 * Return: void
 */
void _freeenv(void)
{
	int index;

	for (index = 0; environ[index] != NULL; index++)
	{
		free(environ[index]);
	}
	free(environ);
}
