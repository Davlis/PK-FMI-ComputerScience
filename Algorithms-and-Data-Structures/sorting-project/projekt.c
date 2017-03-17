#include "projekt.h"

void test(int n, int *tablica, int *malejaco, int *rosnaco);

FILE *tab, *wyn;

int main()
{
	int liczba, x, *tablica, *malejaco, *rosnaco;
	unsigned n=0, i;
	char znak;

	tab=fopen("dane", "r");
	if(tab==0)
	{
		puts("\nNie znaleziono pliku \"dane\".\n");
		fclose(tab);
		return 1;
	}

	printf("\nIle liczb z pliku \"dane\" chcesz wczytać? ");
	while(scanf("%d", &x)==EOF||x<1) printf("Podaj ponownie: ");

	for(i=0; znak!='\n'; i++)
	{
		if(n==x) break;
		znak=fgetc(tab);
		if(znak==' ') n++;
	}
	fclose(tab);

	if(x>n)
	{
		puts("\nW pliku \"dane\" znajduje się zbyt mało liczb.\n");
		return 1;
	}

	tablica=(int*)malloc(n*sizeof(int));

	tab=fopen("dane", "r");
	for(i=0; i<n; i++)
	{
		fscanf(tab, "%d ", &liczba);
		tablica[i]=liczba;
	}
	fclose(tab);

	rosnaco=(int*)malloc(n*sizeof(int));
	malejaco=(int*)malloc(n*sizeof(int));

	sortowanie_ros_mal(tablica, rosnaco, malejaco, n);

	puts("");
	test(n, tablica, malejaco, rosnaco);

	puts("Program został zakończony pomyślnie.");
	puts("Jego wyniki znajdują się w folderze z programem.");
	
	return 0;
}

void test(int n, int *tablica, int *malejaco, int *rosnaco)
{
	int tmp[n], x, y, z;
	clock_t tp, tk;
	double elapsed;
	wyn=fopen("wyniki", "w");
	fprintf(wyn, "Testy sortowań dla tablicy o wielkości n równej %d.\n", n);

	for(z=0; z<3; z++)
	{
		switch(z)
		{
			case 0:
			puts("Zostanie wykonany test 1 - dla tablicy posortowanej losowo.");
			fprintf(wyn, "\n\tTEST 1\n======================\n");
			break;

			case 1:
			puts("Zostanie wykonany test 2 - dla tablicy posortowanej odwrotnie (malejąco).");
			fprintf(wyn, "\n\tTEST 2\n======================\n");
			break;

			case 2:
			puts("Zostanie wykonany test 3 - dla tablicy posortowanej właściwie (rosnąco).");
			fprintf(wyn, "\n\tTEST 3\n======================\n");
			break;
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
				for(y=0; y<n; y++)
					tmp[y]=malejaco[y];
				break;

				case 2:
				for(y=0; y<n; y++)
					tmp[y]=rosnaco[y];
				break;
			}
			tp=clock();
			switch(x)
			{
				case 0:
				puts("Trwa wykonywanie sortowania przez insertion sort.");
				insert_sort(tmp, n);
				break;

				case 1:
				puts("Trwa wykonywanie sortowania przez bubble sort.");
				bubble_sort(tmp, n);
				break;
			
				case 2:
				puts("Trwa wykonywanie sortowania przez selection sort.");
				select_sort(tmp, n);
				break;

				case 3:
				puts("Trwa wykonywanie sortowania przez Quicksort.");
				quicksort(tmp, 0, n-1);
				break;

				case 4:
				puts("Trwa wykonywanie sortowania przez Shell sort.");
				shell_sort(tmp, n);
				break;

				case 5:
				puts("Trwa wykonywanie sortowania przez kopcowanie.");
				heap_sort(tmp, n);
				break;
			}
			tk=clock();
			elapsed=(tk-tp)/(double)CLOCKS_PER_SEC;
			switch(x)
			{
				case 0: fprintf(wyn, "Czas wykonania dla insertion sort wyniósł %lf sekund.\n", elapsed); break;
				case 1: fprintf(wyn, "Czas wykonania dla bubble sort wyniósł %lf sekund.\n", elapsed);break;
				case 2:	fprintf(wyn, "Czas wykonania dla selection sort wyniósł %lf sekund.\n", elapsed);break;
				case 3: fprintf(wyn, "Czas wykonania dla Quicksort wyniósł %lf sekund.\n", elapsed);break;
				case 4: fprintf(wyn, "Czas wykonania dla Shell sort wyniósł %lf sekund.\n", elapsed);break;
				case 5:	fprintf(wyn, "Czas wykonania dla heapsort wyniósł %lf sekund.\n", elapsed);break;
			}
		}
		puts("Wykonano.\n");
	}
	fclose(wyn);
}