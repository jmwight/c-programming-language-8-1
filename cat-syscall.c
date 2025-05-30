#include <fcntl.h>
#include <unistd.h> /* need this just for write function oddly. Why isn't it with fcntl.h? */

#define EOF	-1
#define BUFSIZ	16384

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
	char buf[BUFSIZ];
	ssize_t bytesread;
	while((bytesread = read(fdi, buf, sizeof buf)) != 0)
		write(fdo, buf, (size_t) bytesread);
}
