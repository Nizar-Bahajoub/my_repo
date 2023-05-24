#include "main.h"

/**
 * execute_with_path - Executes a command from the path
 * @args: Array of tokenized commands
 * Return: The process id
 */
int execute_with_path(char **args)
{
	linked_path *temp = link_path();
	char fullpath[1024];

	while (temp != NULL)
	{
		sprintf(fullpath, "%s/%s", temp->dir, args[0]);
		if (access(fullpath, F_OK) == 0)
		{
			execve(fullpath, args, NULL);
		}
		temp = temp->next;
	}
	return (-1);
}

/**
 * check_path - Checks for a command in the path
 * @args: Command to check
 * Return: 1 if command found, -1 otherwise
 */
int check_path(char **args)
{
	linked_path *temp = link_path();
	char fullpath[1024];

	while (temp != NULL)
	{
		sprintf(fullpath, "%s/%s", temp->dir, args[0]);
		if (access(fullpath, F_OK) == 0)
		{
			return (1);
		}
		temp = temp->next;
	}
	return (-1);
}

/**
 * link_path - Creates a linked list for the path
 * Return: A pointer to the first node
 */
linked_path *link_path(void)
{
	char *dir;
	char *path;
	char *pathDup;
	linked_path *head;
	linked_path *currentNode = (linked_path *)malloc(sizeof(linked_path));

	head = currentNode;

	path = _getenv("PATH");
	pathDup = _strdup(path);
	dir = str_tok(pathDup, ":");
	currentNode->dir = _strdup(dir);

	while (dir != NULL)
	{
		dir = str_tok(NULL, ":");
		if (dir != NULL)
		{
			currentNode->next = (linked_path *)malloc(sizeof(linked_path));
			currentNode = currentNode->next;
			currentNode->dir = _strdup(dir);
		}
	}
	currentNode->next = NULL;

	return (head);
}
