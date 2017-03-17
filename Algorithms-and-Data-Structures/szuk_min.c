#include<stdio.h>
#define n 7

int szuk_min(int /*mi*/n, int *tab, int i)
{
	/*if(tab[i]<min) min=tab[i];
	if(i==0) return min;
	szuk_min(min, tab, i-1);
	return min;*/
}

int main()
{
	int tab[n], i=n, min, a=0;
	printf("Podaj pierwszy element tablicy: ");
	scanf("%d", &tab[a]);
	for(a++; a<n; a++)
	{
		printf("Podaj kolejny element tablicy: ");
		scanf("%d", &tab[a]);
	}
	printf("Podaj ostatni element tablicy: ");
	scanf("%d", &tab[a]);
	printf("Najmniejszy element z podanych to: %d\n", szuk_min(tab[i-1], tab, i-1));
	return 0;
}