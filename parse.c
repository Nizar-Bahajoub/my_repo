#include "main.h"

/**
 * str_tok - Entry point
 * @command: command line
 * @delim: delimiter
 * Return: current token
 */
char *str_tok(char *command, const char *delim)
{
	static char *lastToken;
	char *currentToken;

	if (command != NULL)
		lastToken = command;

	if (lastToken == NULL || *lastToken == '\0')
		return NULL;

	currentToken = lastToken;
	while (*currentToken != '\0' && _strchr(delim, *currentToken) != NULL)
		currentToken++;

	if (*currentToken == '\0')
	{
		lastToken = NULL;
		return NULL;
	}

	lastToken = currentToken;
	while (*lastToken != '\0' && _strchr(delim, *lastToken) == NULL)
		lastToken++;

	if (*lastToken != '\0')
	{
		*lastToken = '\0';
		lastToken++;
	}

	return currentToken;
}

/**
 * tokenize - Entry point
 * @command: string passed
 * @args: arguments passed
 * Return: Number of tokens
 */
int tokenize(char *command, char **args)
{
	int i = 0;
	char *token = str_tok(command, " \n\t\r\a");
	char *trimmedToken;

	while (token != NULL && i < MAXARGS - 1)
	{
		trimmedToken = token;
		while (*trimmedToken == ' ')
		{
			trimmedToken++;
		}

		if (trimmedToken[0] == '#')
		{
			break;
		}

		if (*trimmedToken != '\0')
		{
			args[i++] = trimmedToken;
		}

		token = str_tok(NULL, " \n\t\r\a");
	}

	return i;
}
