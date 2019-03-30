#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <signal.h>
#include <sys/wait.h>

#define BUFFER 1024
#define READ 0
#define WRITE 1

bool flag = false;

void alarmHandler()
{
	printf("Alarm Handler -> Alarm clock signal has been received.\n");
	flag = true;
}

void multipleSignalHandler()
{
	printf("Sig. Handler -> And some lived happily ever after (Protection from Ctrl+C & Ctrl+Z)!!!\n");
}

void main(int argc, char *argv[])
{
	int pd[2];
	int clocktime;
	char buf[BUFFER];

	int result = pipe(pd);
	if (0 == result)
	{
		printf("Pipe was created successfully...\n");
		int pid = fork();
		if (0 > pid)
		{
			perror("fork failed");
			exit(2);
		}	
		else if (0 < pid)
		{
			signal(SIGINT, multipleSignalHandler);
			signal(SIGTSTP, multipleSignalHandler);

			printf("Parent        -> Pipe was created succesfully...\n");
			printf("Parent        -> My PID is %d, PPID is %d\n", getpid(), getppid());
			printf("Parent        -> Alarm clock time: %d (a run argument by user)\n",atoi(argv[1]));
		
       			clocktime=atoi(argv[1]);		
	
			if (clocktime % 2 == 0)
			{
				printf("Parent        -> The number is even, the message is about \"KILLING\"\n");
				strcpy(buf, "I'll try to kill you when your time is up!");
			}
			else
			{
				printf("Parent        -> The number is odd, the message is about \"LIVING\"\n");
				strcpy(buf, "You'll live your life!");
			}

			close(pd[READ]);
			write(pd[WRITE], buf, strlen(buf) + 1);
			close(pd[WRITE]);

			signal(SIGALRM, alarmHandler);
			alarm(clocktime);
			printf("Parent        -> Alarm clock signal was scheduled in %d seconds...\n",clocktime);
			while (!flag);
	
			if (clocktime % 2 == 0)
			{
				kill(pid, SIGQUIT);
				printf("Parent        -> Child is tried to be killed.\n");
			}
			else
			{
				printf("Parent        -> Only the God can judge me! (endless loop).\n");
				while (true);
			}
		}
		else
		{
			close(pd[WRITE]);
			while (0 != read(pd[READ], buf, BUFFER))
			{
				printf("Child         -> My PID is %d, PPID is %d\n", getpid(), getppid());
				printf("Child         -> Incoming message from child is: %s\n", buf);
			}
			close(pd[READ]);
			sleep(5);
		}
		printf("Terminating PID: %d, PPID: %d\n", getpid(), getppid());
	}
	else if (-1 == result)
	{
		perror("pipe failed");
		exit(1);
	}
	
}
