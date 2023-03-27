//
// Created by Mateusz on 13.03.2022.
//

#ifndef UNTITLED6_MYVECTOR_H
#define UNTITLED6_MYVECTOR_H

#include <initializer_list>

using std::initializer_list;

const int STARTING_CAPACITY = 10;

template <typename T>
class MyVector {
    struct MyIterator;
public:
    //konstruktory i destruktor
    MyVector();
    MyVector(initializer_list<T> list);
    ~MyVector(){ delete[] array;}

    //zarzadzanie zawartoscia
    void push_back(T elem);
    bool empty(){return free_index==0;};
    void remove(int position);
    void clear();

    //iteratory
    MyIterator begin(){return MyIterator(array);};
    MyIterator end(){return MyIterator(array+free_index);};
    MyIterator last(){return MyIterator(array+free_index-1);};
    MyIterator at(int position){return MyIterator(array+position);};

    //przeciazone operatory
    T* operator[](int position){return array+position;};
    T* operator[](MyIterator position){return array+position;};
    T* operator[](T* position){return position;};

    //inne
    inline int get_size(){return free_index;};

private:
    //zmienne
    int free_index, capacity;               //free_index to pierwsze wolne miejsce w wektorze, capacity to jego rozmiar
    T* array;

    //zarzadzanie pamiecia
    void ensure_capacity();

    //budowa iteratora
    struct MyIterator{
        using pointer = T*;
        using reference = T&;

        explicit MyIterator(pointer p) : current(p){};

        T* current;

        MyIterator& next(){
            current++;
            return *this;
        };

        MyIterator& prev(){
            current--;
            return *this;
        };

        bool has_next(){return (current+1)==nullptr;};
        bool has_prev(){return (current-1)== nullptr;};

        //operatory
        reference operator*(){return *current;}
        pointer operator->(){return current;}
        MyIterator& operator++(){return next();}
        MyIterator& operator++(int a){return next();}
        MyIterator& operator--(){return prev();}
        MyIterator& operator+(int i){current+=i; return *this;}
        MyIterator& operator-(int i){current-=i; return *this;}
        friend int operator-(const MyIterator& a, const MyIterator& b){return a.current - b.current;}
        friend bool operator==(const MyIterator& a, const MyIterator& b){return a.current == b.current;}
        friend bool operator==(const MyIterator& a, reference b){return a.current == b;}
        friend bool operator!=(const MyIterator& a, const MyIterator& b){return a.current != b.current;}
        friend bool operator<(const MyIterator& a, const MyIterator& b){return (a.current - b.current)<0;}
        friend bool operator>(const MyIterator& a, const MyIterator& b){return !operator<(a,b);}
        friend bool operator<=(const MyIterator& a, const MyIterator& b){return (a.current - b.current)<=0;}
        friend bool operator>=(const MyIterator& a, const MyIterator& b){return !operator<=(a,b);}
    };
};

template<typename T>
MyVector<T>::MyVector() {
    free_index = 0;
    capacity = STARTING_CAPACITY;
    array = new T[capacity];
}

template<typename T>
MyVector<T>::MyVector(initializer_list<T> list) {
    free_index = 0;
    capacity = STARTING_CAPACITY;
    array = new T[capacity];
    for(T elem: list)
        push_back(elem);
}

template<typename T>
void MyVector<T>::push_back(T elem) {
    ensure_capacity();
    array[free_index] = elem;
    free_index++;
}

template<typename T>
void MyVector<T>::remove(int position) {
    T* new_array = new T[free_index-1];
    for(int i=0; i<position;i++)                  //przepisz wszystko do position
        new_array[i]=array[i];
    for(int i=position; i<get_size()-1;i++)         //przepisz i przesuń o 1 wszystko po position
        new_array[i] = array[i + 1];
    free_index--;
    delete[] array;
    array = new_array;
}

template<typename T>
void MyVector<T>::clear() {
    delete[] array;
    capacity = STARTING_CAPACITY;
    T* new_array = new T[capacity];
    array = new_array;
    free_index=0;
}

template<typename T>
void MyVector<T>::ensure_capacity() {
    if(free_index == capacity){                 //zwiększ tablice jeśli jest pełna
        capacity = capacity * 3 / 2 + 1;
        T* newArr = new T[capacity];
        for(int i=0; i<free_index;i++)
            newArr[i] = array[i];
        delete[] array;
        array = newArr;
    }
}

#endif //UNTITLED6_MYVECTOR_H
