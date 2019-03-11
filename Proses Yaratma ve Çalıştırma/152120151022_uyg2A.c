#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>
#include<sys/types.h>


void main()
{
	pid_t pid_first,pid_second,pid_a,pid_b,pid_c;
	int durum,cpid;

	pid_first=fork();

	if(pid_first==0)
	{
		printf("PID: %d, PPID: %d: Çocuk 1 \n", getpid(), getppid());
        	
		pid_a=fork();
		
		if(pid_a==0)
		{
			printf("PID: %d, PPID: %d: Torun 1 \n", getpid(), getppid());
           		printf("     %d çalışma yolunu ve içeriğini basar\n", getpid());
			system("echo calisma yolu >> logs/log_all.log ; pwd >> logs/log_all.log ; echo icerik > logs/log_all.log ; ls >> logs/log_all.log");


			printf("PID: %d, PPID: %d, Bekliyor \n", getpid(), getppid());
			sleep(1);
			printf("PID: %d, PPID: %d, Bekleme bitti\n", getpid(), getppid());


		}
		else
		{
			
			pid_b=fork();

			if(pid_b==0)
			{
				printf("PID: %d, PPID: %d: Torun 2 \n", getpid(), getppid());
                    		printf("     %d  işletim  sistemi  üzerinde  koşan üstteki proses  ağacını  basar\n", getpid());


				system("echo process agaci >> logs/log_all.log ; pstree -sg >>  logs/log_all.log");
    

				printf("PID: %d, PPID: %d, Bekliyor  \n", getpid(), getppid());
				sleep(2);
				printf("PID: %d, PPID: %d, Bekleme bitti  \n", getpid(), getppid());


			}
			else
			{
				
				pid_c=fork();
				if(pid_c==0)
				{
					printf("PID: %d, PPID: %d: Torun 3 \n", getpid(), getppid());
            				printf("     %d işletim sisteminde oturum açan kişiyi ve oturum detayını basar\n", getpid());	
					system("echo oturum acan kullanıcı ismi >> logs/log_all.log ; whoami >> logs/log_all.log");


					printf("PID: %d, PPID: %d, Bekliyor\n", getpid(), getppid());
					sleep(3);
					printf("PID: %d, PPID: %d, Bekleme bitti\n", getpid(), getppid());

				

				}
				else
                		{
					printf("PID: %d Çocuk 1 torunlarını bekliyor\n", getpid());
					cpid = wait(&durum);
					printf("PID: %d, beklemesi biten torun: %d \n", getpid(), cpid);                    
               			}
			}
		}

	}
	else
	{
		pid_second=fork();
		if(pid_second==0)
		{
			printf("PID: %d, PPID: %d: Çocuk 2\n", getpid(), getppid());
			printf("PID: %d, PPID: %d, Bekliyor\n", getpid(), getppid());
			sleep(1);
			printf("PID: %d, PPID: %d, Bekleme bitti\n", getpid(), getppid());
        		
		}
		else
		{
			printf("PID: %d, PPID: %d: Ebeveyn \n", getpid(), getppid());
			printf("     %d  logs isminde bir klasör oluşturur\n", getpid());
			system("mkdir -p logs ; echo tarih >> logs/log_all.log ; date >> logs/log_all.log");


			printf("PID: %d, PPID: %d, Bekliyor\n", getpid(), getppid());
			sleep(2);
			printf("PID: %d, PPID: %d, Bekleme bitti\n", getpid(), getppid());

		}	

	}
}
