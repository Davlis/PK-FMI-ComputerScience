#include <cstdio>
#include <cstdlib>
#include <string>
#include <sstream>

class File
{
	FILE *file;
    std::string name;
    std::string accessType;
    
    void write(char c){
        putc(c, file);
    }
    
    void read(char& c){
        c=getc(file);
    }
    
public:
    File(std::string _name, std::string _accessType): name(_name), accessType(_accessType){
	}

	~File(){
		if(fclose(file)==EOF){
			perror("ERROR: fclose");
			exit(EXIT_FAILURE);
		}
	}
    
    bool open(){
        if((file=fopen(name.data(), accessType.data()))==NULL)
            return false;
        else return true;
    }
    
    void readStringFromFile(string& str){
        char c;
        do{
            read(c);
            if(c=='|')
                break;
            str+=c;
        }while(c!=EOF);
    }
    
    template<typename T>
    std::string to_string(T value){
        std::ostringstream oss;
        oss << value;
        return oss.str();
    }
    
    template <typename T>
    void writeStringToFile(const T& var){
        string str=to_string(var);
        
        for(int i=0; i<str.length(); i++)
            write(str[i]);
        write('|');
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
