#include <iostream>
#include <ctime>
#include <cstdlib>

using namespace std;

class Konto
{
	int accountNumber;
	double amountOfMoney, maxDebit, money;
	bool hasCard;
public:
	Konto()
	{
		accountNumber=rand();
		amountOfMoney=0;
		hasCard=false;
		maxDebit=100;
	}

	int cashIn()
	{
		if(hasCard==false) return -1;
		cout<<"Jaką kwotę chciałbyś wpłacić: ";
		cin>>money;
		if(money<0) return 3;
		amountOfMoney+=money;
		return 0;
	}
	int cashOut()
	{
		if(hasCard==false) return -1;
		cout<<"Jaką kwotę chciałbyś wypłacić: ";
		cin>>money;
		if(money<0) return 3;
		if(amountOfMoney-money<-maxDebit) return 1;
		amountOfMoney-=money;
		return 0;
	}
	int makeCard()
	{
		if(hasCard==true) return 2;
		if(amountOfMoney-20<-maxDebit) return 1;
		amountOfMoney-=20;
		hasCard=true;
		return 0;
	}
	int setMaxDebit()
	{
		cout<<"Maksymalny poziom debetu: ";
		cin>>money; 
		if(money<0) return 3;
		if(amountOfMoney<-money) return 4;
		maxDebit=money;
		return 0;
	}
	void display()
	{
		cout<<"Numer konta: "<<accountNumber<<endl<<"Saldo konta: "<<amountOfMoney<<endl<<"Maksymalny debet: "<<maxDebit<<endl<<"Posiadanie karty: ";
		if(hasCard==false) cout<<"Nie"<<endl;
		else cout<<"Tak"<<endl;
	}

};

int main()
{
	srand((unsigned int)NULL);
	Konto account;
	int choice, result;
	cout<<"Witamy w naszym banku."<<endl;
	while(1)
	{
		cout<<"Jaką operację chciałbyś wykonać?"<<endl;
		cout<<"\t[0] wyjdź"<<endl;
		cout<<"\t[1] pokaż dane konta"<<endl;
		cout<<"\t[2] wpłać gotówkę"<<endl;
		cout<<"\t[3] wypłać gotówkę"<<endl;
		cout<<"\t[4] stwórz kartę"<<endl;
		cout<<"\t[5] ustal poziom debetu"<<endl;
		cin>>choice;
		switch(choice)
		{
			case 0:
			cout<<"Dziękujemy za skorzystanie z naszego banku."<<endl;
			return 0;

			case 1:
			account.display();
			break;

			case 2:
			result=account.cashIn();
			break;

			case 3:
			result=account.cashOut();
			break;

			case 4:
			result=account.makeCard();
			break;

			case 5:
			result=account.setMaxDebit();
			break;

		}
		
		switch(result)
		{
			case -1:
			cout<<"Błąd operacji: użytkownik nie posiada karty."<<endl;
			break;

			case 0:
			cout<<"Operację wykonano pomyślnie."<<endl;
			break;

			case 1:
			cout<<"Błąd operacji: operacja spowodowałaby przekroczenie debetu."<<endl;
			break;

			case 2:
			cout<<"Błąd operacji: użytkownik już posiada kartę."<<endl;
			break;

			case 3:
			cout<<"Błąd operacji: podana kwota jest ujemna."<<endl;
			break;

			case 4:
			cout<<"Błąd operacji: nowy poziom debetu byłby wyższy od obecnego stanu konta."<<endl;
		}	
		cout<<endl;
	}
}