#include<stdio.h>
#include<unistd.h>

int main()
{
	pid_t pid = fork();

	if(pid < 0)
	{
		perror("error cannot create child proces\n");
		return 1;
	}
	else if(pid == 0)
	{
		execl("/bin/ls", "ls", "-l", NULL);
		perror("error excel failed");
	}
	else
	{
		printf("Parent process: child created with Pid: %d\n", pid);
	}

		
	return 0;
}
