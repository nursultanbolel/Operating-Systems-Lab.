#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <semaphore.h>
#include <time.h>

pthread_mutex_t printLine_sync;
sem_t sem1, sem2, sem3, sem4, sem5;

int lineID = 0;
int lastCount = 5;

void printLine(char *name)
{
	pthread_mutex_lock(&printLine_sync);

	if(lineID == 0)
	{
		printf(" 0. \t\t\t--> Hadi baslayalim...\n");
	}
	if(name == "Gozluk" || name == "Sapka")
	{
		printf("%2d. (kafa ) " , ++lineID);
	}
	else if(name == "Gomlek" || name == "Kravat" || name == "Ceket" || name == "Mont")
	{
		printf("%2d. (govde) ", ++lineID);
	}
	else if(name == "Pantolon" || name == "Kemer" || name == "Cuzdan")
	{
		printf("%2d. (bacak) ", ++lineID);
	}
	else if(name == "Corap" || name == "Ayakkabi")
	{
		printf("%2d. (ayak ) ", ++lineID);
	}
	printf("%s", name);
	if(lineID >= 6)
	{
		if(lastCount == 0)
		{
			printf("\t--> Hazirim...");
		}
		else
		{
			printf("\t--> Kalan oge sayisi : %d", lastCount--);
		}
	}

	printf("\n");
	pthread_mutex_unlock(&printLine_sync);
}
void *funcA(void *p)
{
	printLine("Gozluk");
	sem_post(&sem1);
	sem_wait(&sem2);
	printLine("Sapka");
	sem_post(&sem4);

	pthread_exit(0);
}
void *funcB(void *p)
{
	sem_wait(&sem1);
	printLine("Gomlek");
	sem_post(&sem2);
	sem_wait(&sem1);
	printLine("Kravat");
	printLine("Ceket");
	printLine("Mont");
	sem_post(&sem2);

	pthread_exit(0);
}
void *funcC(void *p)
{
	sem_wait(&sem2);
	printLine("Pantolon");
	printLine("Kemer");
	sem_post(&sem3);
	sem_wait(&sem4);
	printLine("Cuzdan");
	sem_post(&sem5);

	pthread_exit(0);
}
void *funcD(void *p)
{
	sem_wait(&sem3);
	printLine("Corap");
	sem_post(&sem1);
	sem_wait(&sem5);
	printLine("Ayakkabi");

	pthread_exit(0);
}
int main() 
{ 		
	sem_init(&sem1, 0, 0);
	sem_init(&sem2, 0, 0);
	sem_init(&sem3, 0, 0);
	sem_init(&sem4, 0, 0);
	sem_init(&sem5, 0, 0);

	pthread_mutex_init(&printLine_sync, NULL);

	pthread_t thread_A, thread_B, thread_C, thread_D;

	pthread_create(&thread_A, NULL, funcA,NULL );
	pthread_create(&thread_B, NULL, funcB,NULL);
	pthread_create(&thread_C, NULL, funcC,NULL);
	pthread_create(&thread_D, NULL, funcD,NULL );

	pthread_join(thread_A, NULL);
	pthread_join(thread_D, NULL);

	pthread_mutex_destroy(&printLine_sync);

	sem_destroy(&sem1);
	sem_destroy(&sem2);
	sem_destroy(&sem3);
	sem_destroy(&sem4);
	sem_destroy(&sem5);

}
