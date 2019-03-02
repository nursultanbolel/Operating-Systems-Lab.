#include<stdio.h>

int main()
{
	int sayi;
	int i;
	int rakam;
	int temp;
	int top=0;

	printf("Bir sayi giriniz:");
	scanf("%d", &sayi);

	printf("\n");

	for(i=11;i<sayi;i++)
	{
		top=0;

		if(i%7==0 | i%12==0)
		{
			printf("%d: \t",i);
			temp=i;
			while(temp!=0)
			{
				rakam=temp%10;
				printf("%d",rakam);
				temp=temp/10;
				if(temp!=0)
				{
					printf("+");
				}
				top=top+rakam;
			} 
			printf("= %d \n",top);             

 		}
		top=0;
	}	

	return 0;
}
