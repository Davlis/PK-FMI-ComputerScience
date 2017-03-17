#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#define n 10000

FILE *los;

int main()
{
	int i, prosta[n], tablica[n], x=-101, z=0;

	for(i=0; i<n; i++)
	{
		if(++x==101) x=-100; 
		prosta[i]=x;
	}

	for(i=0; i<n; i++)
	{
		z+=random_nr(0, n-1);
		if(z>=n) z%=n;
		if(prosta[z]==101){--i; continue;}
		tablica[i]=prosta[z];
		prosta[z]=101;
	}

	los=fopen("tablica", "w");

	for(i=0; i<n; i++)
		fprintf(los, "%d ", tablica[i]);

	fclose(los);

	return 0;
}

int random_nr(int min_num, int max_num)
{
	int result=0,low_num=0,hi_num=0;
	if(min_num<max_num)
	{
		low_num=min_num;
		hi_num=max_num+1;
	}else{
		low_num=max_num;
		hi_num=min_num+1;
	}
	srand((unsigned)time(NULL));
	result = (rand()%(hi_num-low_num))+low_num;
	return result;
}