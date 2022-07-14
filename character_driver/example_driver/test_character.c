#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/ioctl.h>

#define FILE	"/dev/char_dd"

char data[128];

int main()
{
	int fd = -1;
	int menu = 0;
	
	fd = open(FILE, O_RDWR);

	if(fd == -1)
	{
		printf("Open device file fail!\n");
		return -1;
	}

	write(fd,"This is data", strlen("This is data"));
	read(fd, data, 128);

	printf("data: %s\n", data);
	
	return 0;
}
