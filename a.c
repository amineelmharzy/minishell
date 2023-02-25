#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main()
{
	char *ar[] = {"script.sh", NULL};
	if (execve("script.sh", ar, NULL) < 0)
		perror("execve");
}
