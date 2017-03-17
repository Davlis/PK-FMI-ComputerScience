#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

void generateArray(int n, int *tab, int type);
long randomNr(long min_num, long max_num);

FILE *file;

int main()
{
	int n, type, *tab;
	unsigned i;

	printf("\nPodaj ilość elementów tablicy: ");
	while(scanf("%d", &n)<1) printf("Podaj ponownie: ");
	printf("\nPodaj tryb generowania tablicy:\n\t[0] równomierny\n\t[1] nierównomierny\n\t[2] pseudolosowo\n");
	while(scanf("%d", &type)!=1||type>2) printf("Podaj ponownie: "); 

	tab=(int*)malloc(n*sizeof(int));

	generateArray(n, tab, type);

	file=fopen("dane", "w");
	for(i=0; i<n; i++)
		fprintf(file, "%d ", tab[i]);
	fprintf(file, "\n");
	fclose(file);

	puts("");
	puts("Tablica została wygenerowana do pliku \"dane\".");
	puts("");
}

void generateArray(int n, int *tab, int type)
{
	long i, d[n];
	unsigned long x=0, y, z=0;

	srand(time(0));

	if(type==1) y=randomNr(n, n-10000);

	switch(type)
	{
		case 2:
		for(i=0; i<n; i++)
			tab[i]=randomNr(-100, 100);
		break;

		default:
		for(i=1; i<=n; i++)
		{
			switch(type)
			{
				case 0:
				x+=(randomNr(n, n-10000)%i);
				break;

				case 1:
				x+=y%i;
				break;
			}
			while(x>200)
				x%=201;
			d[i-1]=(x-100);
		}

		for(i=0; i<n; i++)
		{
			z+=randomNr(1, n-1);
			if(z>=n) z%=n;
			if(d[z]==101){--i; continue;}
			tab[i]=d[z];
			d[z]=101;
		}
	}
}

long randomNr(long min_num, long max_num)
{
	long low_num=0,hi_num=0;
	if(min_num<max_num)
	{
		low_num=min_num;
		hi_num=max_num+1;
	}else{
		low_num=max_num;
		hi_num=min_num+1;
	}
	return (rand()%(hi_num-low_num))+low_num;
}