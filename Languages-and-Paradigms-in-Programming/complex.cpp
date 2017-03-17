#include <iostream>
#include <errno.h>

using namespace std;

template <typename Type>
class Complex
{
	Type re, im;

public:
	Complex(Type re=0, Type im=0): re(re), im(im) {}
	Complex(const Complex& copy, int n): re(n*copy.re), im(n*copy.im) {}
	~Complex() {}

	Complex<Type>& operator=(const Complex& r)
	{
		re=r.re;
		im=r.im;
		return *this;
	}

	template <typename L, typename R>
	friend const bool operator==(const Complex<L>& l, const Complex<R>& r)
	{
		if(l.re==r.re&&l.im==r.im)
			return true;
		else
			return false;
	}

	template <typename L, typename R>
	friend const bool operator!=(const Complex<L>& l, const Complex<R>& r)
	{
		if(l.re==r.re&&l.im==r.im)
			return false;
		else
			return true;
	}

	template <typename L, typename R>
	friend const bool operator<=(const Complex<L>& l, const Complex<R>& r)
	{
		if(l.re<=r.re&&l.im<=r.im)
			return true;
		else
			return false;
	}

	template <typename L, typename R>
	friend const bool operator>=(const Complex<L>& l, const Complex<R>& r)
	{
		if(l.re>=r.re&&l.im>=r.im)
			return true;
		else
			return false;
	}

	template <typename L, typename R>
	friend const bool operator<(const Complex<L>& l, const Complex<R>& r)
	{
		if(l.re<r.re&&l.im<r.im)
			return true;
		else
			return false;
	}

	template <typename L, typename R>
	friend const bool operator>(const Complex<L>& l, const Complex<R>& r)
	{
		if(l.re>r.re&&l.im>r.im)
			return true;
		else
			return false;
	}

	Complex<Type>& operator+()
	{
		return *this;
	}

	Complex<Type>& operator-()
	{
		Complex<Type> *temp = new Complex<Type>(*this, -1);
		return *temp;
	}

	template <typename L, typename R>
	friend void operator+=(Complex<L>& l, const Complex<R>& r)
	{
		l.re+=r.re;
		l.im+=r.im;
	}

	template <typename L, typename R>
	friend void operator-=(Complex<L>& l, const Complex<R>& r)
	{
		l.re-=r.re;
		l.im-=r.im;
	}

	template <typename L, typename R>
	friend void operator*=(Complex<L>& l, const Complex<R>& r)
	{
		Type re, im;
		re=(l.re*r.re)-(l.im*r.im);
		im=(l.re*r.im)+(l.im*r.re);
		l.re=re;
		l.im=im;
	}

	template <typename L, typename R>
	friend void operator/=(Complex<L>& l, const Complex<R>& r)
	{
		if(r.re==0&&r.im==0)
		{
			perror("ERROR: DIVIDE_BY_0");
			return;
		}

		Type re, im, divider;

		divider=(r.re*r.re)+(r.im*r.im);
		re=((l.re*r.re)+(l.im*r.im))/divider;
		im=((l.im*r.re)-(l.re*r.im))/divider;
		l.re=re;
		l.im=im;
	}

	template <typename L, typename R>
	friend const Complex<Type>& operator+(const Complex<L>& l, const Complex<R>& r)
	{
		Complex *temp = new Complex<Type>(l.re+r.re, l.im+r.im);
		return *temp;
	}

	template <typename L, typename R>
	friend const Complex<Type>& operator-(const Complex<L>& l, const Complex<R>& r)
	{
		Complex *temp = new Complex<Type>(l.re-r.re, l.im-r.im);
		return *temp;
	}

	template <typename L, typename R>
	friend const Complex<Type>& operator*(const Complex<L>& l, const Complex<R>& r)
	{
		Complex *temp = new Complex<Type>((l.re*r.re)-(l.im*r.im), (l.re*r.im)+(l.im*r.re));
		return *temp;
	}

	template <typename L, typename R>
	friend const Complex<Type>& operator/(const Complex<L>& l, const Complex<R>& r)
	{
		if(r.re==0&&r.im==0)
		{
			perror("ERROR: DIVIDE_BY_0");
			exit(0);
		}

		Type divider=((r.re*r.re)+(r.im*r.im));

		Complex *temp = new Complex<Type>(((l.re*r.re)+(l.im*r.im))/divider, ((l.im*r.re)-(l.re*r.im))/divider);
		return *temp;
	}

	friend ostream& operator<<(ostream& out,const Complex<Type>& self)
	{
		char znak;
		if(self.im<0)
			znak='\0';
		else
			znak='+';
		out<<self.re<<znak<<self.im<<"i";
		return out;
	}

	friend istream& operator>>(istream& in, Complex<Type>& self)
	{
		in>>self.re>>self.im;
		return in;
	}
};

int main()
{
	Complex<double> a(1.5, 3.0), b(1.2, 2.6), c;
	cout<<"A="<<a<<"  B="<<b<<endl;
	a=b;
	cout<<"A=B    "<<a<<endl;
	a+=b;
	cout<<"A+=B   "<<a<<endl;
	c=a+b;
	cout<<"C=A+B  "<<c<<endl;
	c=a*b;
	cout<<"C=A*B  "<<c<<endl;
	b*=a;
	cout<<"B*=A   "<<b<<endl;
	c=b/a;
	cout<<"C=B/A  "<<c<<endl;
	b/=a;
	cout<<"B/=A   "<<b<<endl<<endl;

	Complex<int> d(1, 2), e(1, 2);
	Complex<double> f(1.0, 3.0);

	cout<<"D="<<d<<"  E="<<e<<"  F="<<f<<endl;

	if (d==e) cout<<"D=E"<<endl;
	else cout<<"D!=E"<<endl;

	if (d!=f) cout<<"D!=F"<<endl;
	else cout<<"D=F"<<endl;

	cout<<"-F     "<<-f<<endl;

	cout<<a<<endl;

	cin>>f;

	cout<<"F after cin: "<<+f<<endl;

	if (a!=f) cout<<"A!=F"<<endl;
	else cout<<"A=F"<<endl;

	return 0;
}