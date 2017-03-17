#include "help.h"

int main(int argc, char* argv[])
{
	Semaphore *sem = new Semaphore(2, 'B');
	SharedMemory *mem = new SharedMemory();
	File *input = new File("input.txt", "r");

	cout<<sem->getSemId()<<endl;

	cout<<"Producent zaczyna pracę."<<endl;

	while(1)
	{
		mem->write(input->read());
		sem->V(1);
		if(mem->read()==EOF)
			break;
		sem->P(0);
	}

	cout<<"Producent kończy pracę."<<endl;

	delete input;
	delete mem;
	delete sem;

	return 0;
}