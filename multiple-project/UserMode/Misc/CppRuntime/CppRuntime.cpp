// CppRuntime.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
using namespace std;

class MyClass {       // The class
public:

    MyClass();
    ~MyClass();


    static int publicstaticint;// Access specifier
    int myNum;        // Attribute (int variable)
    string myString;  // Attribute (string variable)
    void myMethod() {  // Method/function defined inside the class
        cout << "Hello World!";
    }
};

MyClass::MyClass()
{
    cout << "Constructor";
}

MyClass::~MyClass()
{
    cout << "Dest";
}



template <typename T>
T myMax(T x, T y)
{
    return (x > y) ? x : y;
}


void print(int i) {
    cout << " Here is int " << i << endl;
}
void print(double  f) {
    cout << " Here is float " << f << endl;
}
void print(char const* c) {
    cout << " Here is char* " << c << endl;
}




#include <iostream>
using namespace std;


void fun(int* ptr, int x)
{
    if (ptr == NULL)
        throw ptr;
    if (x == 0)
        throw x;
 
}



// CPP program to illustrate
// working of Virtual Functions
#include <iostream>
using namespace std;

class base {
public:
    void fun_1() { cout << "base-1\n"; }
    virtual void fun_2() { cout << "base-2\n"; }
    virtual void fun_3() { cout << "base-3\n"; }
    virtual void fun_4() { cout << "base-4\n"; }
};

class derived : public base {
public:
    void fun_1() { cout << "derived-1\n"; }
    void fun_2() { cout << "derived-2\n"; }
    void fun_4(int x) { cout << "derived-4\n"; }
};

void VFDemo()
{
    base* p;
    derived obj1;
    p = &obj1;

    // Early binding because fun1() is non-virtual
    // in base
    p->fun_1();

    // Late binding (RTP)
    p->fun_2();

    // Late binding (RTP)
    p->fun_3();

    // Late binding (RTP)
    p->fun_4();

    // Early binding but this function call is
    // illegal(produces error) becasue pointer
    // is of base type and function is of
    // derived class
    // p->fun_4(5);
}


MyClass global_myObj;

int MyClass::publicstaticint = 100;

int main()
{

    MyClass myObj;  // Create an object of MyClass

    // Access attributes and set values
    myObj.myNum = 15;
    myObj.myString = "Some text";

    //static re init
    MyClass::publicstaticint = 200;
    // Print attribute values
    cout << myObj.myNum << "\n";
    cout << myObj.myString;
    int a = 0;
    std::cout << "Hello World!\n";

    myObj.myMethod();


    //new - del
    MyClass* pmyObj = new MyClass();
    delete (pmyObj);

    MyClass* pmyObjArry = new MyClass[10];
    delete[] pmyObjArry;


    //templates
    cout << myMax<int>(3, 7) << endl;
    cout << myMax<double>(3.0, 7.0) << endl;
    cout << myMax<char>('g', 'e') << endl;


    //function overloading
    print(10);
    print(10.10);
    print("ten");


    //VirtualFunction
    VFDemo();

    std::cin >> a;
}


