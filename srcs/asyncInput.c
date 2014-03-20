/* 
* @Author: Adrien Chardon
* @Date:   2014-02-14 10:11:00
* @Last Modified by:   Adrien Chardon
* @Last Modified time: 2014-02-15 15:29:02
*/

#include <stdlib.h> /* atexit */
#include <stdio.h>
#include <string.h> /* strerror */
#include <errno.h> /* errno */
#include <unistd.h>
#include <sys/select.h>
#include <termios.h>

struct termios old_term;

/* reset term */
void reset_terminal_mode(void)
{
	tcsetattr(0, TCSANOW, &old_term);
}

/* set non blocking input */
void set_conio_terminal_mode(void)
{
	struct termios new_term;

	/* save original attr and set to new term no buffered io */
	tcgetattr(STDIN_FILENO, &old_term);
	new_term = old_term;
	new_term.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(STDIN_FILENO, TCSANOW, &new_term);

	/* register cleanup handler */
	atexit(reset_terminal_mode);
}

/* return if a key is pressed */
int kbhit(void)
{
	int val;

	struct timeval tv = {0, 0};
	fd_set rdfs;

	FD_ZERO(&rdfs);
	FD_SET( STDIN_FILENO, &rdfs);

	val = select(STDIN_FILENO + 1, &rdfs, NULL, NULL, &tv) == 1;

	return val;
}
