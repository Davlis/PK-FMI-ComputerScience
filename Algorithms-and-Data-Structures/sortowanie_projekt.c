#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
#include <math.h>

void test(int n, int *tablica, int *malejaco, int *rosnaco);
long random_nr(long min_num, long max_num, int i);
void generowanie_tablicy(int n, int *tablica, int tryb);
void sortowanie_ros_mal(int *rosnaco, int *malejaco, int n);
void insert_sort(int *a, int n);
void bubble_sort(int *a, int n);
void select_sort(int *a, int n);
void quicksort(int *a, int p, int k);
void shell_sort(int *tab, int max);
void shell_sort_insert(int tab[], int imax, int h);
void kopcowanie(int *a, int n);
void swap(int i, int j);

FILE *tab, *wyn;

int main()
{
	int n=0, i, tryb, stara, liczba;
	char znak;
	clock_t tp, tk;
	double elapsed;

	puts("");
	printf("Czy chcesz użyć poprzedniej tablicy(0-nie, 1-tak)? ");
	scanf("%d", &stara);
	while(!(tryb==0||tryb==1)) {scanf("%d", &stara); printf("Podaj ponownie: ");}

	switch(stara)
	{
		case 0:
		printf("Podaj ilość elementów tablicy: ");
		while(scanf("%d", &n)<1) printf("Podaj ponownie: ");
		printf("Podaj tryb generowania tablicy(0-równomierny, 1-mniej równomierny): ");
		scanf("%d", &tryb);
		while(!(tryb==0||tryb==1)) {scanf("%d", &tryb); printf("Podaj ponownie: ");}
		break;

		case 1:
		tp=clock();
		tab=fopen("tablica", "r");
		for(i=0; znak!='\n'; i++)
		{
			znak=fgetc(tab);
			if(znak==' ') n++;
		}
		fclose(tab);
		break;
	}

	int tablica[n], malejaco[n], rosnaco[n];

	switch(stara)
	{
		case 0:
		tp=clock();
		puts("");
		puts("Zaraz zostaną wygenerowane tablice do posortowania.");
		generowanie_tablicy(n, tablica, tryb);
		for(i=0; i<n; i++)
			rosnaco[i]=tablica[i];
		sortowanie_ros_mal(rosnaco, malejaco, n);
		puts("Tablice zostały wygenerowane.");
		break;

		case 1:
		tab=fopen("tablica", "r");
		for(i=0; i<n; i++)
		{
			fscanf(tab, "%d ", &liczba);
			tablica[i]=liczba;
		}
		fclose(tab);
		for(i=0; i<n; i++)
			rosnaco[i]=tablica[i];
		sortowanie_ros_mal(rosnaco, malejaco, n);
		break;
	}

	puts("");
	test(n, tablica, malejaco, rosnaco);

	tk=clock();
	elapsed=(tk-tp)/(double)CLOCKS_PER_SEC;

	puts("Program został zakończony pomyślnie.");
	puts("Jego wyniki znajdują się w folderze z programem.");
	printf("Jego wykonanie zajęło %lf sekund.\n", elapsed);
	
	return 0;
}

void test(int n, int *tablica, int *malejaco, int *rosnaco)
{
	int tmp[n], x, y, z;
	clock_t tp, tk;
	double elapsed;

	for(z=0; z<3; z++)
	{
	
	switch(z)
	{
		case 0: puts("Zostanie wykonany test 1 - dla tablicy posortowanej losowo."); break;
		case 1: puts("Zostanie wykonany test 2 - dla tablicy posortowanej odwrotnie."); break;
		case 2: puts("Zostanie wykonany test 3 - dla tablicy posortowanej właściwie."); break;
	}
	
	for(x=0; x<6; x++)
	{
		switch(z)
		{
			case 0:
			for(y=0; y<n; y++)
				tmp[y]=tablica[y];
			break;

			case 1:
			switch(x)
			{
				case 2:
				for(y=0; y<n; y++)
					tmp[y]=rosnaco[y];
				break;

				default:
				for(y=0; y<n; y++)
					tmp[y]=malejaco[y];
			}
			break;

			case 2:
			switch(x)
			{
				case 2:
				for(y=0; y<n; y++)
					tmp[y]=malejaco[y];
				break;

				default:
				for(y=0; y<n; y++)
					tmp[y]=rosnaco[y];
			}
			break;
		}
		tp=clock();
		switch(x)
		{
			case 0:
			puts("Trwa wykonywanie sortowania przez insertion sort.");
			insert_sort(tmp, n);
			switch(z)
			{
				case 0: wyn=fopen("t1_insert_sort", "w"); break;
				case 1: wyn=fopen("t2_insert_sort", "w"); break;
				case 2: wyn=fopen("t3_insert_sort", "w"); break;
			}
			break;

			case 1:
			puts("Trwa wykonywanie sortowania przez bubble sort.");
			bubble_sort(tmp, n);
			switch(z)
			{
				case 0: wyn=fopen("t1_bubble_sort", "w"); break;
				case 1: wyn=fopen("t2_bubble_sort", "w"); break;
				case 2: wyn=fopen("t3_bubble_sort", "w"); break;
			}
			break;
			
			case 2:
			puts("Trwa wykonywanie sortowania przez selection sort.");
			select_sort(tmp, n);
			switch(z)
			{
				case 0: wyn=fopen("t1_select_sort", "w"); break;
				case 1: wyn=fopen("t2_select_sort", "w"); break;
				case 2: wyn=fopen("t3_select_sort", "w"); break;
			}
			break;

			case 3:
			puts("Trwa wykonywanie sortowania przez Quicksort.");
			quicksort(tmp, 0, n-1);
			switch(z)
			{
				case 0: wyn=fopen("t1_quicksort", "w"); break;
				case 1: wyn=fopen("t2_quicksort", "w"); break;
				case 2: wyn=fopen("t3_quicksort", "w"); break;
			}
			break;

			case 4:
			puts("Trwa wykonywanie sortowania przez Shell sort.");
			shell_sort(tmp, n);
			switch(z)
			{
				case 0: wyn=fopen("t1_shell_sort", "w"); break;
				case 1: wyn=fopen("t2_shell_sort", "w"); break;
				case 2: wyn=fopen("t3_shell_sort", "w"); break;
			}
			break;

			case 5:
			puts("Trwa wykonywanie sortowania przez kopcowanie.");
			kopcowanie(tmp, n);
			switch(z)
			{
				case 0: wyn=fopen("t1_kopcowanie", "w"); break;
				case 1: wyn=fopen("t2_kopcowanie", "w"); break;
				case 2: wyn=fopen("t3_kopcowanie", "w"); break;
			}
			break;
		}
		tk=clock();
		elapsed=(tk-tp)/(double)CLOCKS_PER_SEC;
		for(y=0; y<n; y++)
				fprintf(wyn, "%d ", tmp[y]);
		fprintf(wyn, "\n\ntime= %lf", elapsed);
		fclose(wyn);
		puts("Wykonano.");
	}
	puts("");
	}
}

long random_nr(long min_num, long max_num, int i)
{
	long result=0,low_num=0,hi_num=0;
	if(min_num<max_num)
	{
		low_num=min_num;
		hi_num=max_num+1;
	}else{
		low_num=max_num;
		hi_num=min_num+1;
	}
	srand((unsigned)time(0)+i);
	result = (rand()%(hi_num-low_num))+low_num;
	return result;
}

void generowanie_tablicy(int n, int *tablica, int tryb)
{
	long i, prosta[n], x=0, z=0, y;

	if(tryb==1) y=random_nr(n, n+10000, 0);

	for(i=1; i<=n; i++)
	{
		switch(tryb)
		{
			case 0:
			x+=(random_nr(n, n+10000, i)%i);
			break;

			case 1:
			x+=y%i;
			break;
		}
		while(x>200||x<0)
			x%=201;
		prosta[i-1]=(x-100);
	}

	for(i=0; i<n; i++)
	{
		z+=random_nr(1, n-1, i);
		if(z>=n) z%=n;
		if(prosta[z]==101){--i; continue;}
		tablica[i]=prosta[z];
		prosta[z]=101;
	}

	tab=fopen("tablica", "w");
	for(i=0; i<n; i++)
		fprintf(tab, "%d ", tablica[i]);
	int licznik, licznik2=0;
	fprintf(tab, "\n\n");
	for(i=-100; i<=100; i++)
	{
		licznik=0;
		for(y=0; y<n; y++)
			if(tablica[y]==i) {licznik++; licznik2++;}
		fprintf(tab, "Wygenerowano %d sztuk liczby %ld.\n", licznik, i);
	}
	fprintf(tab, "Wygenerowano łącznie %d liczb.\n", licznik2);
	fclose(tab);
}

void sortowanie_ros_mal(int *rosnaco, int *malejaco, int n)
{
	int n2=n;
	quicksort(rosnaco, 0, n-1);
	for(int i=0; i<n; i++)
			malejaco[i]=rosnaco[--n2];
}

void insert_sort(int *a, int n)
{
	int i,x,j;
	for(i=1; i<n; i++)
	{
		x=a[i];
		j=i-1;
		while(j>=0&&a[j]>x)
		{ 
			a[j+1]=a[j];
			j--;
		}
		a[j+1]=x;
	}
}

void bubble_sort(int *a, int n)
{
	int i, j, k, pom, zamiana=1;
	for(j=0; j<n-1 && zamiana; j++) 
	{
		zamiana=0;
		for(i=n-2;i>=j;i--)
			if(a[i]>a[i+1])
 			{ 
 				pom=a[i];
				a[i]=a[i+1];
				a[i+1]=pom;
				zamiana=1;
			};
	}
}

void select_sort(int *a, int n)
{
	int i, pom, i_max, max, m;
	for(i=0; i<n; i++)
	{
	max = a[i];
	i_max = i;
	for(m=i+1; m<n; m++)
		if(a[m] > max)
		{
			max = a[m];
			i_max = m;
		};
	pom=a[i]; 
	a[i]=max; 
	a[i_max]=pom;
	}
}

void quicksort(int *a, int p, int k)
{
	int i=p, j=k, s, pom;
	s=a[(i+j)/2];
	do
	{
		while (a[i]<s)
			i++;
		while (a[j]>s)
			j--;
		if(i<=j)
		{
			pom=a[i];
			a[i]=a[j];
			a[j]=pom;
			i++;
			j--;
		};
	}
	while (i<=j);
	if(j>p) quicksort(a,p,j);
	if(i<k) quicksort(a,i,k);
}

void shell_sort(int *tab, int max)
{
	int hn=1, h=1;
	do
	{
		h=hn;
		hn=h*3+1;
	}
	while(hn<=max);

	while(h>0)
	{
		shell_sort_insert(tab, max, h);
		h/=3;
	}
}

void shell_sort_insert(int *tab, int imax, int h)
{
	int x, n, i, j;
	for(n=0; n<h; n++)
	{
		for(i=n+h; i<imax; i+=h)
		{
			for(j=i-h; j>=0&&tab[j]>tab[j+h]; j-=h)
				swap(tab[j+h], tab[j]);
		}
	}
}

void kopcowanie(int *x, int n)
{
	int i, val, s, f;
	for(i=1; i<n; i++)
	{
		val=x[i];
		s=i;
		f=(s-1)/2;
		while(s>0&&x[f]<val)
		{
			x[s]=x[f];
			s=f;
			f=(s-1)/2;
		}
		x[s]=val;
	}

	for(i=n-1; i>0; i--)
	{
		val=x[i];
		x[i]=x[0];
		f=0;
	
		if(i==1)
			s=-1;
		else
			s=1;

		if(i>2&&x[2]>x[1])
			s=2;

		while(s>=0&&val<x[s])
		{
			x[f]=x[s];
			f=s;
			s=2*f+1;

			if(s+1<=i-1&&x[s]<x[s+1])
				s++;
			if(s>i-1)
				s=-1;
		}
		x[f]=val;
	}
}

void swap(int i, int j)
{
	int tmp;
	tmp=i;
	i=j;
	j=tmp;
}