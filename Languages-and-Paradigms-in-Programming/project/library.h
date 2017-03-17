#include <list>
#include <algorithm>
#include "list.h"

class Library
{
    int currentBookNumber;
    List<Book> lib;
    List<Book>::iterator it;
    
    List<Book>::iterator searchForBook(int i);
    void saveLibToFile();
    void readLibFromFile();
    void showLibrary();
    void addBook();
    void deleteBook();
    void lendBook();
    void returnBook();
    static bool sortByNumber(const Book& a, const Book& b);
    static bool sortByTitle(const Book& a, const Book& b);
    static bool sortByAuthor(const Book& a, const Book& b);
    void sortBooks();
    
public:
    Library() { readLibFromFile(); }
    ~Library() { saveLibToFile(); }
    void menu();
};

/*Library::Library(): currentBookNumber(1){
    lib.push_back(Book(currentBookNumber++, "Mistrz i Małgorzata", "Lew Tołstoj"));
    lib.push_back(Book(currentBookNumber++, "Hobbit, czyli tam i z powrotem", "J. R. R. Tolkien"));
    lib.push_back(Book(currentBookNumber++, "Gra o Tron", "George R. R. Martin"));
    lib.push_back(Book(currentBookNumber++, "Harry Potter i Insygnia Śmierci", "J. K. Rowling"));
    lib.push_back(Book(currentBookNumber++, "Rok 1984", "George Orwell"));
}*/

List<Book>::iterator Library::searchForBook(int i){
    if(i<1||i>=currentBookNumber)
        return lib.end();
    
    List<Book>::iterator tmp=lib.begin();
    while(tmp!=lib.end()&&tmp->getNumber()!=i)
        tmp++;
    
    return tmp;
}

void Library::saveLibToFile(){
    File* file = new File("data", "w");
    if(!file->open())
        return;
    
    file->writeStringToFile(lib.size());
    
    for(it=lib.begin(); it!=lib.end(); it++){
        file->writeStringToFile(it->getNumber());
        file->writeStringToFile(it->getTitle());
        file->writeStringToFile(it->getAuthor());
        if(it->IsLent())
            file->writeStringToFile(1);
        else
            file->writeStringToFile(0);
    }
}

void Library::readLibFromFile(){
    File* file = new File("data", "r");
    if(!file->open())
        return;
    
    string amount;
    file->readStringFromFile(amount);
    
    for(int i=0; i<atoi(amount.data()); i++){
        string str_number;
        file->readStringFromFile(str_number);
        
        string str_title;
        file->readStringFromFile(str_title);
        
        string str_author;
        file->readStringFromFile(str_author);
        
        string str_isLent;
        file->readStringFromFile(str_isLent);
        
        int number=atoi(str_number.data());
        string title=str_title;
        string author=str_author;
        bool isLent;
        if(atoi(str_isLent.data()))
            isLent=true;
        else isLent=false;
        
        lib.push_back(Book(number, title, author, isLent));
        if(number>currentBookNumber)
            currentBookNumber=number;
    }
    ++currentBookNumber;
    delete file;
}

void Library::menu(){
    string str;
    cout<<"=====BIBLIOTEKA====="<<endl;
    while(1){
        cout<<endl;
        cout<<"Co chciałbyś zrobić?"<<endl;
        cout<<"\t[q] wyjdź z biblioteki"<<endl;
        cout<<"\t[s] pokaż zawartość"<<endl;
        cout<<"\t[a] dodaj książkę"<<endl;
        cout<<"\t[d] usuń książkę"<<endl;
        cout<<"\t[b] wypożycz książkę"<<endl;
        cout<<"\t[r] oddaj książkę"<<endl;
        cout<<"\t[v] posortuj książki"<<endl;
        cout<<"\t[p] pożar!!!"<<endl;
        
        getline(cin, str);
        
        while(str.length()!=1||(str[0]!='s'&&str[0]!='a'&&str[0]!='d'&&str[0]!='b'&&str[0]!='r'&&str[0]!='v'&&str[0]!='p'&&str[0]!='q')){
            cout<<"Błędny argument."<<endl;
            getline(cin, str);
        }
        
        switch(str[0]){
            case 's': showLibrary(); break;
            case 'a': addBook(); break;
            case 'd': deleteBook(); break;
            case 'b': lendBook(); break;
            case 'r': returnBook(); break;
            case 'v': sortBooks(); break;
            case 'p':
                lib.clear();
                cout<<"POŻAR!!!!!!"<<endl<<"Niestey spaliły się wszystkie książki w bibliotece :((((("<<endl;
                break;
            case 'q':
                cout<<"Do zobaczenia wkrótce!"<<endl;
                return;
        }
        //saveLibToFile();
    }
}

void Library::showLibrary(){
    if(!lib.size()){
        cout<<"Brak książek w bibliotece"<<endl;
        return;
    }
    
    for(it=lib.begin(); it!=lib.end(); it++){
        cout<<*it<<endl;
    }
}

void Library::addBook(){
    Book *tmp = new Book(currentBookNumber++);
    cin>>*tmp;
    lib.push_back(*tmp);
    delete tmp;
}

void Library::deleteBook(){
    if(!lib.size()){
        cout<<"Brak książek w bibliotece."<<endl;
        return;
    }
    
    int i;
    
    cout<<"Podaj numer książki do usunięcia: ";
    cin>>i;
    
    if((it=searchForBook(i))==lib.end()){
        cout<<"Nie ma takiej książki."<<endl;
        return;
    }
    
    lib.erase(it);
    cout<<"Książka usunięta."<<endl;
}

void Library::lendBook(){
    if(!lib.size()){
        cout<<"Brak książek w bibliotece."<<endl;
        return;
    }
    
    int i;
    cout<<"Podaj numer książki do wypożyczenia: ";
    cin>>i;
    
    if((it=searchForBook(i))==lib.end()){
        cout<<"Nie ma takiej książki."<<endl;
        return;
    }
    
    if(it->IsLent()){
        cout<<"Książka już jest wypożyczona."<<endl;
        return;
    }
    
    it->lend();
}

void Library::returnBook(){
    if(!lib.size()){
        cout<<"Brak książek w bibliotece."<<endl;
        return;
    }
    
    int i;
    cout<<"Podaj numer książki do oddania: ";
    cin>>i;
    
    if((it=searchForBook(i))==lib.end()){
        cout<<"Nie ma takiej książki."<<endl;
        return;
    }
    
    if(!(it->IsLent())){
        cout<<"Książka nie jest wypożyczona."<<endl;
        return;
    }
    
    it->getBack();
}

bool Library::sortByNumber(const Book& a, const Book& b){
    return a.getNumber()<b.getNumber();
}

bool Library::sortByTitle(const Book& a, const Book& b){
    string aString=a.getTitle();
    string bString=b.getTitle();
    int i;
    for(i=0; aString[i]==bString[i]; i++);
    return aString[i]<bString[i];
}

bool Library::sortByAuthor(const Book& a, const Book& b){
    string aString=a.getAuthor();
    string bString=b.getAuthor();
    int i;
    for(i=0; aString[i]==bString[i]; i++);
    return aString[i]<bString[i];
}

void Library::sortBooks(){
    if(!lib.size()){
        cout<<"Brak książek w bibliotece."<<endl;
        return;
    }
    
    cout<<"Posortuj wg:"<<endl;
    cout<<"\t[n] numeru"<<endl;
    cout<<"\t[t] tytułu"<<endl;
    cout<<"\t[a] autora"<<endl;
    
    string str;
    getline(cin, str);
    
    while(str.length()!=1||(str[0]!='n'&&str[0]!='t'&&str[0]!='a')){
        cout<<"Błędny argument."<<endl;
        getline(cin, str);
    }
    
    switch(str[0]){
        case 'n':
            //lib.sort(sortByNumber);
            sort(lib.begin(), lib.end(), sortByNumber);
            break;
        case 't':
            //lib.sort(sortByTitle);
            sort(lib.begin(), lib.end(), sortByTitle);
            break;
        case 'a':
            //lib.sort(sortByAuthor);
            sort(lib.begin(), lib.end(), sortByAuthor);
            break;
    }
    
    cout<<"Posortowano."<<endl;
}
