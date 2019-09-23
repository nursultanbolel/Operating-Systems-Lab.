#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <sys/wait.h>
#include <string.h>


struct multiplePrintData
{
	pthread_t id;
	char printText[20];
	int waitDuration;
};

int duration;
int duration_counter=0;

void * printCharMultipleTimes(void *p)
{
	struct multiplePrintData *mP=(struct multiplePrintData *)p;
	struct multiplePrintData MP=*mP;
	
	if(duration_counter<duration)
	{
		fflush(stdout);
		printf("%s: \n",MP.printText);
		usleep(MP.waitDuration);
		duration_counter+=MP.waitDuration;
	}
	
	
}


int main(int argc, char *argv[])
{

	int number;
	int sum;


	if(argc == 1)
	{
		printf("%s musts be executed with arguments! Aborted automatically!\n",argv[0]);
		return 0;
	} 
	else if(argc == 2)
	{
		printf("%s needs at least 2 additional arguments correctly to go on! Aborted automatically!\n",argv[0]);
		return 0;
	}
	else
	{

		sum = (atoi(argv[2]))*2+3;


		if(argc < sum)
		{	
			printf("%s needs at least %d arguments in total!\n",argv[0],sum);	
			return 0;
		}


		printf("\nMain Function        -> Duration:%s",argv[1]);
		duration = atoi(argv[1]);


		printf("\nMain Function        -> Number of words:%s",argv[2]);
		number = atoi(argv[2]);

		printf("\n");


		struct multiplePrintData *veri = malloc(number*sizeof(struct multiplePrintData));
		
		pthread_t id[number];		
		int k=0;
		for(int i=0;i<number;i++)
		{
			veri[i].id=id[i];
			strcpy(veri[i].printText,argv[k+3]);
			veri[i].waitDuration=atoi(argv[k+4]);
			k=k+2;
		}

		while(duration_counter<duration)
		{
			printf("\n\n\n");
			for(int j=0;j<number && duration_counter<duration;j++)
			{
				pthread_create(&id[j],NULL,printCharMultipleTimes,&veri[j]);
				pthread_join(id[j], NULL);
			}
		}
		return 0;
	}


}
