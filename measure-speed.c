#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <stdarg.h>
#include <string.h>

#define CMDMAX	512

void error(char *fmt, ...);

enum prog
{
	STD = 1, NONSTD
};

int main(int argc, char **argv)
{
	if(argc-- < 2)
		error("usage: ./measure-speed PROGNUM FILE1, FILE2, ...");
	int x, l;
	if(**++argv == '-')
	{
		/* XXX: find out why these brackets are necessary else statement fall in when not supposed to */
		if(*++*argv == 'l')
		{
			if((l = atoi(*++argv)) < 1)
			{
				error("No number or negative number given for iterations!");
			}
			else
			{
				++argv;
			}
			argc -= 2;
		}
		else
			error("Invalid option given. Only -l NUM_OF_ITERATIONS permitted.");
	}
	if((x = atoi(*argv)) > 2 || x < 1)
		error("Only program 1 (standard) and 2 (syscall) are valid");
	enum prog p = x;

	/* construct command */
	char cmd[CMDMAX];

	if(p == STD)
		strcpy(cmd, "./cat-stdlib ");
	else
		strcpy(cmd, "./cat-syscall ");

	/* add files after */
	while(--argc > 0)
	{
		strcat(cmd, *++argv);
		if(argc > 0)
			strcat(cmd, " ");
	}

	/* measure performance */
	struct timeval t0, t1, td;
	if(gettimeofday(&t0, NULL) == -1)
		error("Failed to get start time!");

	system((const char *) cmd);

	if(gettimeofday(&t1, NULL) == -1)
		error("Failed to get end time!");
	timersub(&t1, &t0, &td);

	printf("\nExecution time was %5.5ds %6.6dµs\n", td.tv_sec, td.tv_usec);
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
