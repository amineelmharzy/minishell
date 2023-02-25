#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main()
{
	char *ar[] = {"ls", NULL};
	if (execve("ls", ar, NULL) < 0)
		perror("execve");
}
