#include <iostream>
#include <cmath>

using namespace std;

class rect;
class circle;
class triangle;
int comp(rect kw, circle ko, triangle tr);

class shape_geom
{
	double area;

public:
	void setArea(double ar)
	{
		area=ar;
	}
	double getArea()
	{
		return area;
	}
};

class rect : public shape_geom
{
	double a, b, ar;
	friend int comp(rect kw, circle ko, triangle tr);
public:
	void setAr()
	{
		ar = a*b;
	}
	rect(double x = 0, double y = 0)
	{
		a = x;
		b = y;
		setAr();
		setArea(ar);
	}
};

class circle : public shape_geom
{
	double r, ar;
	friend int comp(rect kw, circle ko, triangle tr);
public:
	void setAr()
	{
		ar = r*r*3.14;
	}
	circle(double pr = 0)
	{
		r = pr;
		setAr();
		setArea(ar);
	}
};


class triangle : public shape_geom
{
	double a, b, c, ar;
	friend int comp(rect kw, circle ko, triangle tr);
public:
	void setAr()
	{
		double p = (a + b + c) / 2;
		ar = sqrt(p*(p - a)*(p - b)*(p - c));
	}
	triangle(double x = 0, double y = 0, double z = 0)
	{
		a = x;
		b = y;
		c = z;
		setAr();
		setArea(ar);
	}
};

int main()
{
	rect kw(5.3, 4.8);
	circle ko(2.34);
	triangle tr(3, 4, 5);
	cout << "Pole kwadratu: " << kw.getArea() << "\nPole kola: " << ko.getArea() << "\nPole trojkąta: " << tr.getArea() << endl;
	cout << "sparawdzenie: " << comp(kw, ko, tr) << endl;
	return 0;
}

int comp(rect kw, circle ko, triangle tr)
{
	switch (ko.getArea() > kw.getArea())
	{
	case true:
		return 0;
	case false:
		switch (kw.getArea() > tr.getArea())
		{
		case true:
			return 1;
		case false:
			return 2;
		}
	}
}