#include "intarray.h"

using namespace std;

IntArray& IntArray::operator=(const IntArray& a)
{

    if (&a != this) { //Avoids self-assignment
        delete[] p;
        const unsigned newSizeConst = a.size;
        const unsigned newCapConst = a.cap;
        p = new int[a.size];
        size = newSizeConst;
        cap = newCapConst;
        for (unsigned i = 0; i < size; i++) p[i] = a.p[i];
    }
    return *this;
}


void IntArray::resize(unsigned sz, int val)
{
    int* temp = new int[sz];
    unsigned i;

    if (sz > size) { //Array is increasing in size
        for (i = 0; i < size; i++) temp[i] = p[i];
        for (; i < sz; i++) 
            temp[i] = val;
    }
    else { //Array is decreasing in size
        for (i = 0; i < sz; i++) 
            temp[i] = p[i];
    }

    delete[] p;
    p = temp;
    determinecap(sz); //increase cap if size higher, lower or equal then stays the same.
    size = sz;
}

//I/O functions
ostream& operator<<(ostream& out, const IntArray& a)
{
    unsigned size = a.length();

    for (unsigned i = 0; i < size; i++)
        out << setw(6) << a[i]; //sets output to be spaced out by 6 spaces
    return out;
}

istream& operator>>(istream& in, IntArray& a)
{
    unsigned size = a.length();

    for (unsigned i = 0; i < size; i++)
        in >> a[i];
    return in;
}

//Relational operators
bool operator==(const IntArray& a1, const IntArray& a2)
{
    bool equal = false;

    if (a1.length() == a2.length()) {
        unsigned size = a1.length();
        unsigned i;

        for (i = 0; i < size && a1[i] == a2[i]; i++)
            ;
        if (i == size) equal = true;
    }
    return equal;
}

bool operator!=(const IntArray& a1, const IntArray& a2)
{
    return !(a1 == a2);
}

//move constructor/assignment

IntArray::IntArray(IntArray&& original) noexcept {
    //copying right hand side to left hand side
    this->size = original.size;
    this->p = &original[0];
    this->cap = original.cap;
    
    //delete right hand size  
    original.size = 0;
    original.p = nullptr;
    original.cap = 0;

}

IntArray& IntArray::operator=(IntArray&& original) noexcept {
    //copying right hand side to left hand side
    if (&original != this) {
        this->size = original.size;
        this->p = &original[0];
        this->cap = original.cap;
    }
    //delete right hand size  
    original.size = 0;
    original.p = nullptr;
    original.cap = 0;

    return *this;
}



IntArray::IntArray(initializer_list<int> passed_list) {
    p = new int[passed_list.size()]; 
    cap = size = (unsigned)passed_list.size();
    initializer_list<int>::iterator p_itr;   //can potentially use a size loop, however for the purposes
    // of this project, a iterator might be better as size in initializer list might be awkward. 
    unsigned i = 0;

    for (p_itr = passed_list.begin(); p_itr != passed_list.end(); p_itr++,i++)
        p[i] = *p_itr;
}

void IntArray::assign(const int* a, unsigned n) {
    //similar to assignment operators/constructors, without the issue of self assignment
    // or anything. 
    p = new int[n];
    cap = size = n;
    for (unsigned i = 0; i < size; i++) p[i] = a[i];
}

void IntArray::insert(unsigned pos, int x) {

    int* splitPtr = nullptr;
    //This function splits the array into before the 
    //inserted pos, the inserted pos, and end pos. 
    //Fills these values into the temp ptr, and assigns p that temporary pointer. 

    //size is a valid index since it's the end of the array, 
    //as otherwise it would be difficult to decide if the position inserted
    //is the end of the array, or the last element.
    //Hence, anything above size is past the new array. 
    if (pos > size) {
        throw (Array_Error("Index out of bounds: only insert elements from to 0 up to the back of the Array."));
    }
    
    //reserve and resizing is based upon vector class behavior in these two cases. 
    //Either the array being full or the position being at the end will cause this behavior.
    if (size == cap || pos == size) {
        reserve(size + 2);
        resize(size + 1);
    }

    else {
        resize(size + 1);
    }

    splitPtr = new int[int(size)];

    for (unsigned i = 0; i < pos; i++) //part of array prior to the passed position
        splitPtr[i] = p[i];
    
    splitPtr[pos] = x; //assign the position to the passed value x 
    
    for (unsigned i = pos + 1; i < size; i++) //part of array after passed position
        splitPtr[i] = p[i - 1];
    delete[] p; 

    //copying of the temporary pointer to p.
    p = new int[int(size)];
    for (unsigned i = 0; i < size; i++) {
        p[i] = splitPtr[i];
    }
    delete[] splitPtr;


}

void IntArray::insert(unsigned pos, unsigned n, int x) {
    //Similar to the above insert, however with the addition of how many n elements
    //to specify to be filled for the user. Since the position is multiple elements now,
    //its part of the splitting process will require it's own for loop. 


    if (pos > size) {
        throw (Array_Error("Index out of bounds: only insert elements from to 0 up to the back of the Array."));
    }

    //we now need to consider if the collection of numbers is larger than the size.
    //likewise, since there's multiple adds, we need to increment it by the n elements. 
    else if (size == cap || size + n > cap || pos == size) {
        reserve(size + n);
        size += n;
    }

    else {
        size += n;
    }

    int* splitPtr = new int[size];

    for (unsigned i = 0; i < size; i++)
        splitPtr[i] = 0; //prevents memory uninitalized error. Perhaps a false flag? 


    for (unsigned i = 0; i < pos; i++)
        splitPtr[i] = p[i];
    for (unsigned i = pos; i < n + pos; i++) //now requires loop due to have multiple elements.
        splitPtr[i] = unsigned(x);
    for (unsigned i = pos + n; i < size; i++)
        splitPtr[i] = p[i - n];
    delete p;


    p = new int[int(size)];
    for (unsigned i = 0; i < size; i++) {
        p[i] = splitPtr[i];
    }
    delete[] splitPtr;
}

void IntArray::push_back(int x) {
    insert(size, x);
}


void IntArray::erase(unsigned pos) {
    //similar to insert, but the inverse. Except now we are now shifting everything to the right
    //of the position to the left. 

    if (cap == 0 || size == 0)
        throw(Array_Error("Error: Try not to remove elements from an empty Array!"));
    else if (pos > size) {
        cout << pos << endl;
        throw(Array_Error("Error: Position that you're trying to remove is out of range!"));

    }

    else if (size == 1) {
        p = nullptr;
        size = 0;
    }

    //shifts every element above pos downward, overwriting the element at pos
    else {
        for (unsigned i = pos; i < size - 1; i++)
            p[i] = p[i + 1];

        size--;
    }
}


void IntArray::pop_back() {
    erase(size - 1); //we can use erase again, since like the single position version,
    //it's only getting rid of one element.
}

void IntArray::erase(unsigned first, unsigned last) {
    //Since there's no dynamic memory allocation, we can simply reuse erase 
    //as the operation is negligible each time.
    for (unsigned i = first; i < last; i++) 
        erase(first); 
}

void IntArray::clear() {
    size = 0; 
}



void IntArray::reserve(unsigned n) {
    determinecap(n);
}

unsigned IntArray::capacity() const {
    return cap;
}

void IntArray::swap(IntArray& a) {
    if (*this != a) { //prevents self assignment
        IntArray temp = a;
        a = *this;
        *this = temp;
    }
}

bool operator<(const IntArray& a1, const IntArray& a2) {
    if (a1 != a2) {
        if (a1[0] < a2[0] || a1.length() < a2.length())
            return true;
        else
            return false;
    }
    else
        return false;
}

bool operator<=(const IntArray& a1, const IntArray& a2) {
    if (a1 < a2 || a1 == a2)
        return true;
    else
        return false;

}


bool operator>(const IntArray& a1, const IntArray& a2) {
    if (a1 != a2) {
        if (a1[0] > a2[0] || a1.length() > a2.length())
            return true;
        else
            return false;
    }
    else
        return false;
}

bool operator>=(const IntArray& a1, const IntArray& a2) {
    if (a1 > a2 || a1 == a2)
        return true;
    else
        return false;

}

//Checks if arrays are the same and adds/multiplies by respective element. If not, throw an error.

IntArray add(const IntArray& a1, const IntArray& a2) {
    if (a1.length() == a2.length()) {
        IntArray temp(a1.length());

        for (unsigned i = 0; i < a2.length(); i++)
            temp[i] = addByElement(a1[i], a2[i]);
        return temp;
    }
    else
        throw(Array_Error("Arrays are not the same size!"));
}


IntArray multiply(const IntArray& a1, const IntArray& a2) {
    if (a1.length() == a2.length()) {
        IntArray temp(a1.length());

        for (unsigned i = 0; i < a2.length(); i++)
            temp[i] = multiplyByElement(a1[i], a2[i]);
        return temp;
    }
    else
        throw(Array_Error("Arrays are not the same size!"));
}





