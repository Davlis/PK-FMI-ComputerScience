#include <iostream>

template <typename T>
class Node
{
	T variable;
	Node<T> *next;

public:
	Node(T var=NULL, Node<T> *nx=nullptr): variable(var) { next=nx; }
	T getVar(){ return variable; }
	Node<T>* getPtr() { return next; }
};


template <typename T>
class LIFO
{
	int size;
	Node<T>* top;

public:
	LIFO(): size(0) {}

	LIFO<T>& push(T var)
	{
		Node<T> *ptr = nullptr;

		if(size>0) 
			ptr = top;

		top = new Node<T>(var, ptr);

		size++;

		return *this;
	}

	LIFO<T>& pop()
	{
		if(size<=0)
			return *this;

		Node<T> *ptr = top;
		
		top = top->getPtr();
		
		delete ptr;

		size--;	

		return *this;
	}

	void peek()
	{
		if(!size)
			return;

		std::cout<<top->getVar()<<std::endl;
	}
	


};

int main()
{
	LIFO<int> kolejka;
	kolejka.push(1);
	kolejka.peek();
	kolejka.push(2);
	kolejka.peek();
	kolejka.pop();
	kolejka.peek();
	kolejka.pop();
	kolejka.peek();
	kolejka.pop();

	return 0;
}