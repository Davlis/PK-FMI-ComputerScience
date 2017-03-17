class Book{
    const int number;
	string title;
	string author;
    bool isLent;

public:
	Book(int _number, string _title="no title", string _author="no author", bool _isLent=false): number(_number), title(_title), author(_author), isLent(_isLent) {}
    Book(const Book& book): Book(book.number, book.title, book.author, book.isLent) {}

    int getNumber() const { return number; }
	string getTitle() const { return title; }
	string getAuthor() const { return author; }
    bool IsLent() const { return isLent; }
    void lend(){ isLent=true; }
    void getBack(){ isLent=false; }
    
    Book& operator=(const Book& book){
        Book *tmp = new Book(book.number, book.title, book.author, book.isLent);
        return *tmp;
    }
    
    friend istream& operator>>(istream& in, Book& self){
        cout<<"Podaj nazwę książki: ";
        cin.ignore();
        getline(cin, self.title);
        cout<<"Podaj autora książki: ";
        getline(cin, self.author);
        return in;
    }
    
    friend ostream& operator<<(ostream& out, Book& self){
        cout<<"Numer książki: "<<self.number<<endl;
        cout<<"Nazwa książki: "<<self.title<<endl;
        cout<<"Autor książki: "<<self.author<<endl;
        if(self.isLent) cout<<"Wypożyczona"<<endl;
        return out;
    }
};
