#include "intarray.h"

int main() {
    //to demonstrate initaliziation based upon a variety of different ways
    //to initialize.
    int arr[4] = { 1,6,3,5 };
    IntArray array_initalized(arr, 4);
    vector<int> vect = { 1,2,3,4 };
    int primArray[] = { 4, 3, 2, 1 };
    IntArray a = { 1,6,3,5 };
    IntArray b(6);
    for (int i = 0; i < 6; i++)
        b[i] = 3 * i * i - 4 * i + 2;
    IntArray c(b);

    cout << "Array a:" << a << endl;
    cout << "Array b:" << b << endl;
    cout << "Array c:" << c << endl;;

    //Demonstration of the move constructor and move assignment operator.
    cout << "Moving elements from a to d..." << endl;
    IntArray d = move(a);
    cout << "Array a:" << a << endl;
    cout << "Array d:" << d << endl;
    cout << "Moving elements from b to d..." << endl;
    d = move(b);
    cout << "Array d:" << d << endl;
    cout << "Array b:" << b << endl;

    //Demonstration of a range constructor and the .assign function. 
    IntArray e(vect.begin(), vect.end());
    cout << "Array e, created from a range constructor:" << e << endl;
    e.assign(primArray, 4);
    cout << "Array e, after assignment using prim array holding 1,2,3,4 in reverse: " << e << endl;

    //Demonstration of iterator capabilities.
    cout << endl;
    cout << "Printing e in reverse now..." << endl;
    for (auto i = e.rbegin(); i != e.rend(); i++)
        cout << *i << " ";
    cout << endl;

    cout << "The front of e is " << e.front() << " The back of e is " << e.back() << endl;
    e.front() = 777;
    cout << "Chaning e's front to 777" << endl;
    cout << "The front of e is  " << e.front() << endl;

    //Demonstrating use of insertion/deletion functions. 
    cout << endl;
    IntArray x = { 1,2,3 };
    cout << "The original array x is " << x << endl;
    x.insert(1, 1312);
    cout << "The result of inserting the number 1312 in pos one of x is " << x << endl;
    cout << "The result of x after a lot of additions including push_back line by line is: " << endl;
    x.insert(0, 11);
    cout << "After inserting 11 to the front: " << x << endl;
    x.push_back(777);
    cout << "After pushing 777 to the back: " << x << endl;
    x.insert(1, 2, 3);
    cout << "After inserting 2 instances of 3 in the second position: " << x << endl;

    cout << endl;
    cout << "Removing first and last element of x" << endl;
    x.pop_back();
    x.erase(0);
    cout << "The result after popping_back and removing first element:" << x << endl;
    x.clear();
    cout << "The result after clearing x :" << x << endl;

    IntArray y = { 1,2,3 };
    cout << "The original array y is " << y << endl;
    y.erase(0, 3);
    cout << "The result of y being erased is " << y << endl;

    //Demonstration of the swap function.
    cout << endl;
    IntArray swap1 = { 1,2,3 };
    IntArray swap2 = { 4,5,6 };
    cout << "The original arrays swap1 and swap 2 repectively are " << swap1 << " | " << swap2 << endl;
    swap1.swap(swap2);
    cout << "SWAP 1 after swap: " << swap1 << endl;
    cout << "SWAP 2 after swap: " << swap2 << endl;


    //Demonstration of the relational operators.
    cout << "Is array " << swap1 << " less than" << swap2 << "? The answer: " << (swap1 < swap2) << endl;
    cout << "Is array " << swap1 << " Greater than" << swap2 << "? The answer: " << (swap1 > swap2) << endl;
    cout << "Is array " << swap2 << " less than or equal to" << swap1 << "? The answer: " << (swap2 <= swap1) << endl;
    cout << "Is array " << swap2 << " Greater than or equal to" << swap1 << "? The answer: " << (swap2 >= swap1) << endl;

    cout << endl;
    IntArray same1 = { 1,1,1 };
    IntArray same2 = same1;

    cout << "Is array " << same1 << " less than or equal to" << same2 << "? The answer: " << (same1 <= same2) << endl;
    cout << "Is array " << same1 << " Greater than or equal to" << same2 << "? The answer: " << (same1 >= same2) << endl;
    cout << endl;


    //Demonstration of cpp functions.

    IntArray sample = { 2,1,3 };
    cout << "The original array sample is " << sample << endl;
    sort(sample.begin(), sample.end());
    cout << "Sample in descending order:" << endl;
    cout << sample << endl;

    sort(sample.begin(), sample.end(), std::greater<IntArray>());
    cout << "Sample in ascending order" << endl;
    cout << sample << endl;


    cout << endl;
    IntArray othersample = { 0,0,0 };
    IntArray othersample2 = { 0,0,0,0,0,0 };

    cout << "Copying sample to othersample: " << endl;
    copy(sample.begin(), sample.end(), othersample.begin());
    cout << othersample << endl;

    cout << "Copying sample to other sample but in reverse " << endl;
    reverse_copy(sample.begin(), sample.end(), othersample.begin());
    cout << othersample << endl;

    cout << "Consider IntArray othersample2" << othersample2 << endl;
    copy_backward(sample.begin(), sample.end(), othersample2.end());
    cout << "Adding sample to othersample2 but backwards: " << othersample2 << endl;

    cout << endl;
    fill(othersample.begin(), othersample.end(), 45);
    cout << "Other sample after being filled with #45: " << othersample << endl;

    cout << endl;
    IntArray result = { 0,0,0 };
    remove_copy(othersample.begin(), othersample.end(), result.begin(), 45); //note: desination range cannot be same as source range
    cout << "Removing copies of 45..." << endl;
    cout << "Results of operation: " << result << endl;

    cout << endl;
    cout << "Refilling othersample with a primitive array filled with 7s..." << endl;
    int testing[] = { 7, 7, 7 };
    copy_n(testing, 3, othersample.begin());
    cout << "Results of operation: " << othersample << endl;

    cout << endl;
    cout << "Multiplying " << sample << endl;
    cout << "And " << othersample << endl<<"Using std::transform" << endl;
    IntArray othersample3 = { 1,2,3 };
    std::transform(sample.begin(), sample.end(), othersample.begin(), othersample.begin(), multiplyByElement);
    cout << "Result stored in array 2: " << othersample << endl;

    cout << endl;
    cout << "Adding " << othersample << endl;
    cout << "And " << othersample3 << endl<<"Using std::transform" << endl;
    std::transform(othersample.begin(), othersample.end(), othersample3.begin(), othersample3.begin(), addByElement);
    cout << "Result stored in array 2: " << othersample3 << endl;

    //Demonstration of reserve and capacity functions.
    cout << endl;
    IntArray test = { 2,2,2 };
    IntArray test2 = { 1,2,3 };
    cout << "Consider the IntArray test" << test << endl;
    cout << "Consider the IntArray test2" << test2 << endl;
    cout << "The size and capacity of test is " << test.length() << ", " << test.capacity() << " respectively" << endl;
    test.reserve(5);
    cout << "And after reserving 5 elements, the capacity is now: " << test.capacity() << endl;

    //Demonstration of add and multiplication functions.
    cout << "The addition of test1 and test2 (using the add function) is " << add(test, test2) << endl;
    cout << "The multiplication of test1 and test2 is (using the multiply function) is" << multiply(test, test2) << endl;


}