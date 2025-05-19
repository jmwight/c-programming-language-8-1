#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#define CMDMAX	512

void error(char *fmt);

enum prog
{
	STD = 1, NONSTD
};

int main(int argc, char **argv)
{
	if(argc-- < 2)
		error("usage: ./measure-speed PROGNUM FILE1, FILE2, ...");
	int x;
	if((x = atoi(*++argv)) > 2 || x < 1)
		error("Only program 1 (standard) and 2 (syscall) are valid");
	enum prog p = x;

	/* construct command */
	char *cmd[CMDMAX];

	if(p == STD)
		strcpy(cmd, "./cat-stdlib ");
	else
		strcpy(cmd, "./cat-syscall ");

	/* add files after */
	while(argc-- > 0)
	{
		strcat(cmd, *++argv);
		if(argc > 0)
			strcat(cmd, ' ');
	}

	/* measure performance */
	struct timeval t0, t1, td;
	if(gettimeofday(&t0) == -1)
		error("Failed to get start time!");

	system((const char *) cmd);

	if(gettimeofday(&t1) == -1)
		error("Failed to get end time!");
	timersub(&t1, &t0, &td);

	printf("\nExecution tim was %5.55ds %6.6dµs\n");
	return EXIT_SUCCESS;
}

/* error: prints error message to stderr and exits.
 * Practice using vprintf and vfprintf */
void error(char *fmt, ...)
{
	va_list ap;

	va_start(ap, fmt);
	fprintf(stderr, "Error: ");
	vfprintf(stderr, fmt, ap);
	fprintf(stderr, "\n");
	va_end(ap);
	exit(EXIT_FAILURE);
}
