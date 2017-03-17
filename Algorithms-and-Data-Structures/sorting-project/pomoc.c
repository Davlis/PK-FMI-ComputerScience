/* W tym pliku znajdują się funkcje dodatkowe potrzebne do działania programu sortującego */

void sortowanie_ros_mal(int *tablica, int *rosnaco, int *malejaco, int n)
{
	unsigned m=n, i;

	for(i=0; i<n; i++)
			rosnaco[i]=tablica[i];
	quicksort(rosnaco, 0, n-1);
	for(i=0; i<n; i++)
			malejaco[i]=rosnaco[--m];
}