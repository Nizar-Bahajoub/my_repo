#include "main.h"

/**
 * execute - Executes a command
 * @command: Command passed
 * @line_num: Line number to track commands
 * Return: ID of fork
 */
int execute(char *command, int line_num)
{
	char *args[MAXARGS];
	char command_path[MAX_PATH_LENGTH];
	pid_t pid;
	int i;

	i = tokenize(command, args);
	args[i] = NULL;

	if (built_ins(args, line_num) || built_ins2(args, line_num))
		return (0);
	if (access(args[0], X_OK) == -1)
	{
		_strcpy(command_path, "/bin/");
		_strcat(command_path, args[0]);
		if (access(command_path, X_OK) == -1)
		{
			print_error(args[0], "not found", line_num);
			return (0);
		}
	}

	pid = fork();

	if (pid == -1)
		exit(EXIT_FAILURE);

	if (pid != 0)
		run_parent();

	if (pid == 0 && args[0][0] != '\0')
	{
		run_child(args);
	}

	return (0);
}


/**
 * run_child - Executes the child process
 * @args: Command passed
 * Return: ID of fork
 */
int run_child(char **args)
{
	if (args[0][0] == '/' || args[0][0] == '.')
	{
		if (execve(args[0], args, environ) == -1)
		{
			perror(args[0]);
			exit(EXIT_FAILURE);
		}
	}
	else if (check_path(args) == 1)
	{
		execute_with_path(args);
	}
	else
	{
		perror(args[0]);
		exit(EXIT_FAILURE);
	}
	return (0);
}

/**
 * run_parent - Executes the parent process
 *
 * Return: ID of fork
 */
int run_parent(void)
{
	exit_status();
	return (0);
}

/**
 * exit_status - Retrieves the exit status of the child process
 *
 * Return: Exit status
 */
int exit_status(void)
{
	int status;
	static int exit_status;

	wait(&status);

	if (WIFEXITED(status))
	{
		exit_status = WEXITSTATUS(status);
	}
	return (exit_status);
}
