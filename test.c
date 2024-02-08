#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int	main(void)
{
	int	id1;
	int	id2;

	id1 = fork();
	if (id1 == 0)
		printf("Hello\n");
	else
	{
		wait(&id1);
		id2 = fork();
		printf("Hello 2\n");
	}
}
