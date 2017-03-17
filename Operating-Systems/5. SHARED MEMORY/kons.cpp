#include "help.h"

int main(int argc, char* argv[])
{
	Semaphore *sem = new Semaphore(2, 'B');
	SharedMemory *mem = new SharedMemory();
	File *output = new File("output.txt", "w");
	
	cout<<sem->getSemId()<<endl;

	cout<<"Konsument zaczyna pracę."<<endl;

	while(1)
	{
		sem->P(1);
		if(mem->read()==EOF)
			break;
		output->write(mem->read());
		sem->V(0);
	}

	cout<<"Konsument kończy pracę."<<endl;

	delete output;
	delete mem;
	delete sem;

	return 0;
}