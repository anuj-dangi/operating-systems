#include<stdio.h>
#include<unistd.h>


int main()
{
	pid_t pid = fork();

	if(pid < 0)
	{
		perror("failed to create child process\n");
		return 1;
	}
	else if(pid == 0)
	{
		printf("This is child process-> current pid: %d, parent pid: %d\n", getpid(), getppid());
	}
	else
	{
		printf("This is current process->parent pid: %d, current pid:  %d,child pid:  %d\n",getppid(),  getpid(), pid);
	}

	return 0;	
}
