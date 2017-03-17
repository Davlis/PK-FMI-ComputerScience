/* W tym pliku znajdują się algorytmy sortowania */

void insert_sort(int *a, int n)
{
	int i, j, x;
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
	int i, j, k, tmp, zamiana=1;
	for(j=0; j<n-1 && zamiana; j++) 
	{
		zamiana=0;
		for(i=n-2;i>=j;i--)
			if(a[i]>a[i+1])
 			{
 				tmp=a[i];
 				a[i]=a[i+1];
 				a[i+1]=tmp;
				zamiana=1;
			};
	}
}

void select_sort(int *a, int n)
{
	int i, j, pos, tmp;
    for(i=0; i<n; i++)
    {
        for(j=i, pos=i; j<n; j++)
            if(a[j]<a[pos])
                pos=j;
        tmp=a[pos];
        a[pos]=a[i];
        a[i]=tmp;
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

void shell_sort(int *a, int n)
{
	int h, i, j, t;
	for(h=n; h/=2; )
	{
		for(i=h; i<n; i++)
		{
			t=a[i];
			for(j=i; j>=h&&t<a[j-h]; j-=h)
				a[j]=a[j-h];
			a[j]=t;
		}
	}
}

void heap_sort(int *x, int n)
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