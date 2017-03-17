#include <stdio.h>

char lit[]={'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', 'ą', 'ć', 'ę', 'ł', 'ń', 'ó', 'ś', 'ż', 'ź'};
char *mors[]={"•—", "—•••", "—•—•", "—••", "•", "••—•", "——•", "••••", "••", "•———", "—•—", "•—••", "——", "—•", "———", "•——•", "——•—", "•—•", "•••", "—", "••—", "•••—", "•——", "—••—", "—•——", "——••", "•—•—", "—•—••", "••—••", "•—••—", "——•——", "———•", "•••—•••", "——••—•", "——••—"};

int main()
{
	char bufor[256], *dd, b;
	int i, n, length;
	printf("Podaj tekst do zamiany na alfabet Morse'a: ");
	dd=gets(bufor);
	length=strlen(bufor);
	//while((b=*dd++)!='/0')	
	//{
		for(n=0; n<35 ; n++)
		{
			if(bufor[n]==' ') {printf("|"); continue;}
			if(bufor[n]=='\0') break;
			for(i=0; ; i++) if(bufor[n]==lit[i]) break;
			printf("%s|", mors[i]);
		}
	//}	
	printf("\n");
	return 0;
}
