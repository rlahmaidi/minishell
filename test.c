#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>

int main()
{
	execve(NULL, NULL, NULL);
	printf("%s\n", strerror(errno));
}