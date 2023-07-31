// C++ program to delete array of 
// objects 
#include <iostream> 
using namespace std;

// Class 
class Student {

public:
	// Constructor 
	Student()
	{
		cout << "Constructor is called!\n";
	}

	// Destructor 
	~Student()
	{
		cout << "Destructor is called!\n";
	}

	// Function to display message 
	void write()
	{
		cout << "Writing!\n";
	}
};


//The program wont crash one con will be called.------------
//gfg is correct the program will crash
//program will crash but gfg is worng..
//compiler will make problem.---------------

// Driver Code 
int main()
{
	// Create an object dynamically 
	Student* student = new Student[3];

	// Function call to write() 
	student[0].write();
	student[1].write();
	student[2].write();

	// De-allocate the memory 
	// explicitly 
	delete student;

	return 0;
}
	