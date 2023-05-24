#include "main.h"

/**
 * handleSIGINT - Signal handler for SIGINT (CTRL + C)
 * @sigNum: Signal number
 */
void handleSIGINT(int sigNum)
{
	(void)sigNum;
	write(STDOUT_FILENO, "\n", 1);
	signal(SIGINT, handleSIGINT);
}
Changes made:

Renamed the function sigintHandler to handleSIGINT.
Adjusted the function comment to match the updated function name.


