typedef struct el_listy
{
	int klucz;
	struct el_listy *nast;
}LISTA, *USTAWSK

void dodaj_costam(p, k)
	LISTAWSK p;
	int k;
{
	LISTAWSK nowy;
	nowy=(LISTAWSK)malloc(sizeof(LISTA));
	nowy -> klucz = p -> klucz;
	nowy -> nast = p -> nast;
	p -> klucz = k;
	p -> nast = nowy;
}

void usun_nast(LISTAWSK p)
{
	LISTAWSK tmp = p -> nast;
	if(tmp!=NULL)
	{
		p -> nast = tmp -> nast;
		delete(tmp);
	}
}

void usun(LISTAWSK glowa, LISTAWSK p)
{
	LISTAWSK usun, p1, p2;
	if(p->nast!=NULL)
	{
		usun= p -> nast;
		p -> klucz = usun -> klucz;
		p -> nast = usun -> nast;
		delete(usun);
	}
	else
	{
		p1=glowa;
		p2=glowa->nast;
		while(p2->nast!=NULL)
		{
			p1=p2;
			p2=p2->nast;
		}
		p1=>nast=NULL;
		delete(p2);
	}
}