#include <iostream>
#include <cmath>

using namespace std;

template <typename T>
int count(T& number){
	int sum=0;
	T prev=number=(T)1;

	while(1){
		number/=2;
		++sum;
		if((number+(T)1)==(T)1){
			number=prev;
			--sum;
			break;
		}
		prev=number;
	}
	return sum;
}

int main(){
	float fl;
	double db;

	cout<<"FLOAT: "<<count(fl)<<" ";
	cout<<fl<<endl;

	cout<<"DOUBLE: "<<count(db)<<" ";
	cout<<db<<endl;
}