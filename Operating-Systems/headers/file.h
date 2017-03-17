class File
{
	FILE *file;
public:
	File(char* name, char* accessType){
		if((file=fopen(name, accessType))==NULL){
 			perror("ERROR: fopen");
 			exit(errno);
 		}
	}

	~File(){
		if(fclose(file)==EOF){
			perror("ERROR: fclose");
			exit(EXIT_FAILURE);
		}
	}

	void write(char c){
		putc(c, file);
	}

	char read(){
		return getc(file);
	}	
};

/*class File
 {
	fstream f;
	const string name;
 public:
	File(string _name, char howtoaccess): name(_name)
	{
 switch(howtoaccess)
 {
 case 'w':
 f.open(name, fstream::out);
 break;
 
 case 'r':
 f.open(name, fstream::in);
 break;
 
 default:
 perror("ERROR: type of file access");
 exit(EXIT_FAILURE);
 }
	}
	~File() { f.close(); }
 
	void write(char c){
 f<<c;
	}
 
	char read()
	{
 char c;
 f>>c;
 return c;
	}
 };*/
