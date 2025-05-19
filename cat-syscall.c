#include <fcntl.h>
#include <unistd.h> /* need this just for write function oddly. Why isn't it with fcntl.h? */

int main(int argc, char **argv)
{
	int fd;
	void filecopy(int, int);
	int mystrlen(char *);
	
	if(argc == 1)
		filecopy(0, 1);
	else
	{
		while(--argc > 0)
		{
			if((fd = open(*++argv, O_RDONLY, 0)) == -1)
			{
				write(1, "cat: can't open ", 16);
				write(1, *argv, mystrlen(*argv));
				write(1, "\n", 1);
				return 1;
			}
			else
			{
				filecopy(fd, 1);
				close(fd);
			}
		}
	}
	return 0;
}

int mystrlen(char *s)
{
	int i = 0;
	while(*s++ != '\0')
		++i;
	return i+1;
}

/* filecopy: copy file ifp to file ofp */
void filecopy(int fdi, int fdo)
{
	int c;

	while((read(fdi, &c, sizeof c) == 0))
		write(fdo, &c, sizeof c);
}
