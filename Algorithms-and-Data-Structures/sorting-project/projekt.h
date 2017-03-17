#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
#include <math.h>

void insert_sort(int *a, int n);
void bubble_sort(int *a, int n);
void select_sort(int *a, int n);
void quicksort(int *a, int p, int k);
void shell_sort(int *a, int n);
void heap_sort(int *a, int n);

void sortowanie_ros_mal(int *tablica, int *rosnaco, int *malejaco, int n);