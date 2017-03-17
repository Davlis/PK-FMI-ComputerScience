#include <iostream>
#include <fstream>
#include <cmath>
#include <cfloat>

using namespace std;

long double fx(long double x){
	return (1.0L-exp(-x))/x;
}

long double _fx(long double x){
	unsigned long n=0;
	long double sum=1.0L, ratio=sum, epsilon=DBL_MIN;
	
	while(fabs(ratio*=(-x)/(n++ +2.0L))>epsilon && !isinf(sum))
		sum+=ratio;
	
	return sum;
}

int main(){
	cout.precision(20);
	cout<<scientific;
	cout<<"#==================================================================================="<<endl;
	cout<<"#  Dane wyjściowe do ćwiczenia nr 2"<<endl;
	cout<<"#==================================================================================="<<endl;
	cout<<"#                   log10(x)                           x               (1-exp(-x))/x"<<endl;
	cout<<"#==================================================================================="<<endl;
	
	long double power, x, reference, result;
	ifstream ifs;
	ifs.open("oneminexp_ref.txt", ifstream::in);
	
	for(int i=0; i<5; i++) ifs.ignore(256, '\n');
	while(ifs.good()){
		ifs>>power>>x>>reference;
		cout<<scientific<<power<<" "<<x<<" "<<(result = (x < 1 ? _fx(x) : fx(x)))<<" ";
		cout<<fabs(reference-result)<<endl;
	}
	
	cout<<"#===================================================================================";
	ifs.close();
	return 0;
}