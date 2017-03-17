//
//  list.h
//  Biblioteka
//
//  Created by Kamil Kosiński on 23/01/2017.
//  Copyright © 2017 Kamil Kosiński. All rights reserved.
//

template <typename T>
struct Node{
    T object;
    Node<T> *next;
    Node<T> *prev;
    
    Node(const T &obj) : object(obj), next(nullptr), prev(nullptr) {}
};

template <typename T>
class List{
    Node<T>* head;
    Node<T>* tail;
    int _size;
    
    Node<T> insertInternal(const T&, Node<T>*);
    void removeInternal(Node<T>*);
    
public:
    List(): _size(0), head(nullptr), tail(nullptr) {}
    ~List();
    
    class iterator{
        Node<T>* pos;
        
    public:
        typedef std::random_access_iterator_tag iterator_category;
        typedef T value_type;
        typedef T* pointer;
        typedef T& reference;
        typedef size_t size_type;
        typedef ptrdiff_t difference_type;
        
        friend void List<T>::erase(const iterator&);
        
        iterator(Node<T>* p=nullptr): pos(p) { }
        iterator(const iterator& it) { pos=it.pos; }
        ~iterator() {}
        
        iterator& operator=(const iterator& it){
            pos=it.pos;
            return *this;
        }
        
        iterator& operator++(){
            pos=pos->next;
            return *this;
        }
        
        iterator operator++(int){
            iterator tmp(*this);
            pos=pos->next;
            return tmp;
        }
        
        iterator& operator--(){
            pos=pos->prev;
            return *this;
        }
        
        iterator operator--(int){
            iterator tmp(*this);
            pos=pos->prev;
            return tmp;
        }
        
        //T operator*() const { return pos->object; }
        T* operator->() const { return &(pos->object); }
        T& operator*() const { return pos->object; }
        T& operator[](size_t s) const { return iterator(iterator()+s); }
        
        friend void swap(iterator& a, iterator& b){
            Node<T>* tmp_a=a.pos;
            Node<T>* tmp_b=b.pos;
            
            Node<T>* next=tmp_b->next;
            Node<T>* prev=tmp_a->prev;
            
            prev->next=tmp_b;
            next->prev=tmp_a;
            
            tmp_b->prev=prev;
            tmp_b->next=tmp_a;
            
            tmp_a->next=next;
            tmp_a->prev=tmp_b;
        }
        
        friend bool operator==(const iterator& a, const iterator& b){
            return a.pos==b.pos;
        }
        
        friend bool operator!=(const iterator& a, const iterator& b){
            return a.pos!=b.pos;
        }
        
        friend bool operator<(const iterator& a, const iterator& b){
            if((a.pos)->next==b.pos) return true;
            else return false;
        }
        friend bool operator>(const iterator& a, const iterator& b){
            if((b.pos)->prev==a.pos) return true;
            else return false;
        }
        friend bool operator<=(const iterator& a, const iterator& b){
            if((a.pos)->next==b.pos) return true;
            else if(a.pos==b.pos) return true;
            else return false;
        }
        friend bool operator>=(const iterator& a, const iterator& b){
            if((b.pos)->prev==a.pos) return true;
            else if(a.pos==b.pos) return true;
            else return false;
        }

        iterator& operator+=(size_t s){
            //if(s<0) return this;
            while(s--)
                ++(*this);
            return this;
        }
        
        iterator& operator-=(size_t s){
            //if(s<0) return this;
            while(s--)
                --(*this);
            return this;
        }
        
        friend iterator operator+(const iterator& it, size_t s){
            iterator tmp(it);
            //if(s<0) return tmp;
            while(s--)
                ++tmp;
            return tmp;
        }
        
        friend iterator operator+(size_t s, const iterator& it){
            iterator tmp(it);
            //if(s<0) return tmp;
            while(s--)
                ++tmp;
            return tmp;
        }
        
        friend ptrdiff_t operator-(iterator a, iterator b){
            ptrdiff_t diff=0;
            bool flag=false;
            iterator tmp=a;
            
            if(a.pos==nullptr){
          //      return List::size();
            }
            
            do{
                ++diff;
                if((a.pos)->next==nullptr){
                    flag=true;
                    break;
                }
            }while(++a.pos!=b.pos);
            
            if(flag){
                diff=0;
                do{
                    ++diff;
                }while(--tmp.pos!=b.pos);
            }

            return diff;
        }
        
        friend iterator operator-(const iterator& it, size_t s){
            iterator tmp=it;
            //if(s<0) return tmp;
            while(s--)
                --tmp;
            return tmp;
        }
    };
    
    int size() { return _size; }
    void push_back(const T&);
    void pop_back();
    void erase(const iterator&);
    void clear();
    T& front() { return head->object; }
    T& back() { return tail->object; }
    
    iterator begin() { return iterator(head); }
    iterator end() { return iterator(nullptr); }
};


template <typename T>
Node<T> List<T>::insertInternal(const T& obj, Node<T>* pos){
    Node<T> *tmp = new Node<T>(obj);
    tmp->next=pos;
    
    if(pos!=nullptr){
        tmp->prev=pos->prev;
        pos->prev=tmp;
    }else{
        tmp->prev=tail;
        tail=tmp;
    }
    
    if(tmp->prev!=nullptr){
        tmp->prev->next=tmp;
    }else{
        head=tmp;
    }
    
    _size++;
    return *tmp;
}

template <typename T>
void List<T>::removeInternal(Node<T>* pos){
    if(pos!=nullptr){
        if(pos->prev!=nullptr)
            pos->prev->next=pos->next;
        if(pos->next!=nullptr)
            pos->next->prev=pos->prev;
        if(pos==head)
            head=pos->next;
        if(pos==tail)
            tail=pos->prev;
        delete pos;
        _size--;
    }
}

template <typename T>
void List<T>::push_back(const T& obj){
    insertInternal(obj, nullptr);
}

template <typename T>
void List<T>::pop_back(){
    removeInternal(tail);
}

template <typename T>
void List<T>::erase(const iterator& it){
    removeInternal(it.pos);
}


template <typename T>
void List<T>::clear(){
    Node<T>* current(head);
    while(current){
        Node<T>* next(current->next);
        delete current;
        current=next;
    }
    head=nullptr;
    tail=nullptr;
}

template <typename T>
List<T>::~List(){
    clear();
}
