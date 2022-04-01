#pragma once


#ifndef __INTARRAY__
#define __INTARRAY__

#include <iostream>
#include <iomanip> //For output formatting
#include <vector>
#include <algorithm>
#include <iterator>

using namespace std;


class Array_Error {
private:
    string err_msg;
public:
    Array_Error(const string& s) : err_msg(s) {}
    string get_message() { return err_msg; }
};

class IntArray {
    typedef int* iterator;
    typedef const int* const_iterator;
    typedef reverse_iterator<iterator> r_iterator;
    typedef reverse_iterator<const_iterator> const_reverse_iterator;
private:
    int* p; //pointer to int array data
    unsigned size; //size of the array
    unsigned cap; //capacity of the array

public:
    //Constructors
    IntArray(); //Default constructor
    IntArray(unsigned n, int val = 0);
    IntArray(const int* a, unsigned n);
    IntArray(const IntArray& a); //Copy constructor
    IntArray(IntArray&& original) noexcept; //Move constructor
    IntArray(initializer_list<int> passed_list); //intializer list constructor
    template <typename forIterator>//template necessary for initializer ctor to handle multiple types of lists
    IntArray(forIterator begin, forIterator end);

    //Destructor
    ~IntArray();

    //Assignment operators
    IntArray& operator=(const IntArray& a); //standard assignment constructor, takes another IntArray
    IntArray& operator=(IntArray&& a) noexcept; //move assignment constructor, moves values from a
    //to present object.
    void assign(const int* a, unsigned n); //.assign function which assigns 

    //Subscript operators
    int& operator[](unsigned pos);
    const int& operator[](unsigned pos) const;

    //reporters 
    iterator begin();
    iterator end();
    const_iterator begin() const;
    const_iterator end() const;
    r_iterator rbegin(); //returns the end 
    r_iterator rend(); //returns the beginning
    const_reverse_iterator rbegin() const;
    const_reverse_iterator rend() const;
    int& front();
    int& front() const;
    int& back();
    int& back() const;

    //Size functions
    unsigned length() const { return size; } //name to avoid function variable mismatch
    bool empty() const { return size == 0; }
    void resize(unsigned sz, int val = 0);  ////Resize array, initialize new elements to val
    void determinecap(unsigned dsize); //used in functions when size is passed to determine
    //capacity. If greater, increase to that size. Otherwise, keep the capacity the same. 

    //modifier functions 
    void insert(unsigned pos, int x); //inserts a number of value x to index pos.
    void insert(unsigned pos, unsigned n, int x); //inserts n numbers of value x to index pos.
    void push_back(int x); 
    void pop_back();
    void erase(unsigned pos); 
    void erase(unsigned first, unsigned last); 
    void clear();

    void reserve(unsigned n); //for increasing capacity.
    unsigned capacity() const;

    void swap(IntArray& a);
};

//I/O functions
ostream& operator<<(ostream& out, const IntArray& a);
istream& operator>>(istream& in, IntArray& a);

//Relational operators
bool operator==(const IntArray& a1, const IntArray& a2);
bool operator!=(const IntArray& a1, const IntArray& a2);
bool operator<(const IntArray& a1, const IntArray& a2);
bool operator<=(const IntArray& a1, const IntArray& a2);
bool operator>=(const IntArray& a1, const IntArray& a2);
bool operator>(const IntArray& a1, const IntArray& a2);


//inline functions to pass to std::transform, as the function works iteratively
//also ulitized by functions multiply and add in a similar fashion. Additionally,
//the full function prototypes are also located here. 
inline unsigned multiplyByElement(unsigned element1, unsigned element2) {
    return element1 * element2;
}

inline unsigned addByElement(unsigned element1, unsigned element2) {
    return element1 + element2;
}


IntArray add(const IntArray& a1, const IntArray& a2);
IntArray multiply(const IntArray& a1, const IntArray& a2);

//need the template once more to distinguish types.
template <typename forIterator>
IntArray::IntArray(forIterator begin, forIterator end) {
    //gathers size from difference of the beginning and end of list
    size_t newsize = std::distance(begin, end); 
    p = new int[newsize];
    cap = size = unsigned(newsize);
    unsigned i = 0;

    for (forIterator p_itr = begin; p_itr != end; p_itr++, i++)
        p[i] = *p_itr;
}


//Default constructor, creates array of size 0
inline
IntArray::IntArray() : p(0), size(0), cap(0) {}

//Creates array of n elements all initialized to val
inline
IntArray::IntArray(unsigned n, int val) : p(new int[n]), size(n), cap(n)
{
    for (unsigned i = 0; i < n; i++) p[i] = val;
}

//Creates a copy of integer array a
inline
IntArray::IntArray(const int* a, unsigned n) :
    p(new int[n]), size(n), cap(n)
{
    for (unsigned i = 0; i < n; i++) p[i] = a[i];
}

//Creates a copy of IntArray a
inline
IntArray::IntArray(const IntArray& a) :
    p(new int[a.size]), size(a.size), cap(a.size)
{
    for (unsigned i = 0; i < size; i++) p[i] = a.p[i];
}

//Destructor
inline IntArray::~IntArray()
{
    delete[] p;
}


//Subscript operators
//The following works for const arrays
inline
const int& IntArray::operator[](unsigned pos) const
{
    if (pos >= size)
        throw(Array_Error("Out of range"));
    return(p[pos]);
}

//The following works for non-const arrays
inline int& IntArray::operator[](unsigned pos)
{
    return const_cast<int&>(static_cast<const IntArray&>(*this)[pos]);
}

//used in functions when cap is passed as parameter for decisions, inline due to brevity
inline void IntArray::determinecap(unsigned dsize) {
    if (dsize > cap)
        cap = dsize;
}


//Iterator and their returns
inline IntArray::iterator IntArray::begin() {
    return p;
}

inline IntArray::const_iterator IntArray::begin() const {
    return p;
}

inline IntArray::iterator IntArray::end() {
    return p+size;
}

inline IntArray::const_iterator IntArray::end() const {
    return p+size;
}

//r_iterators and their const variants need an explicit type cast
inline IntArray::r_iterator IntArray::rbegin() {
    return r_iterator(end());
}

inline IntArray::r_iterator IntArray::rend() {
    return r_iterator(begin());
}

inline IntArray::const_reverse_iterator IntArray::rbegin() const {
    return const_reverse_iterator(end());
}

inline IntArray::const_reverse_iterator IntArray::rend() const {
    return const_reverse_iterator(begin());
}

inline int& IntArray::front() {
    return *p;
}

inline int& IntArray::back() {
    return p[size - 1];
}


#endif