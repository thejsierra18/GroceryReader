#include <Python.h>
#include <iostream>
#define NOMINMAX
#include <Windows.h>
#include <cmath>
#include <string>
#include <vector>
#include <list>
#include <fstream>
#include <iomanip>

using namespace std;

/*
Description:
	To call this function, simply pass the function name in Python that you wish to call.
Example:
	callProcedure("printsomething");
Output:
	Python will print on the screen: Hello from python!
Return:
	None
*/
void CallProcedure(string pName)
{
	char* procname = new char[pName.length() + 1];
	std::strcpy(procname, pName.c_str());

	Py_Initialize();
	PyObject* my_module = PyImport_ImportModule("PythonCode");
	PyErr_Print();
	PyObject* my_function = PyObject_GetAttrString(my_module, procname);
	PyObject* my_result = PyObject_CallObject(my_function, NULL);
	Py_Finalize();

	delete[] procname;
}

/*
Description:
	To call this function, pass the name of the Python functino you wish to call and the string parameter you want to send
Example:
	int x = callIntFunc("PrintMe","Test");
Output:
	Python will print on the screen:
		You sent me: Test
Return:
	100 is returned to the C++
*/
int callIntFunc(string proc, string param)
{
	char* procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	char* paramval = new char[param.length() + 1];
	std::strcpy(paramval, param.c_str());


	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)"PythonCode");
	// Load the module object
	pModule = PyImport_Import(pName);
	// pDict is a borrowed reference 
	pDict = PyModule_GetDict(pModule);
	// pFunc is also a borrowed reference 
	pFunc = PyDict_GetItemString(pDict, procname);
	if (PyCallable_Check(pFunc))
	{
		pValue = Py_BuildValue("(z)", paramval);
		PyErr_Print();
		presult = PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else
	{
		PyErr_Print();
	}
	//printf("Result is %d\n", _PyLong_AsInt(presult));
	Py_DECREF(pValue);
	// Clean up
	Py_DECREF(pModule);
	Py_DECREF(pName);
	// Finish the Python Interpreter
	Py_Finalize();

	// clean 
	delete[] procname;
	delete[] paramval;


	return _PyLong_AsInt(presult);
}

/*
Description:
	To call this function, pass the name of the Python functino you wish to call and the string parameter you want to send
Example:
	int x = callIntFunc("doublevalue",5);
Return:
	25 is returned to the C++
*/
int callIntFunc(string proc, int param)
{
	char* procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)"PythonCode");
	// Load the module object
	pModule = PyImport_Import(pName);
	// pDict is a borrowed reference 
	pDict = PyModule_GetDict(pModule);
	// pFunc is also a borrowed reference 
	pFunc = PyDict_GetItemString(pDict, procname);
	if (PyCallable_Check(pFunc))
	{
		pValue = Py_BuildValue("(i)", param);
		PyErr_Print();
		presult = PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else
	{
		PyErr_Print();
	}
	//printf("Result is %d\n", _PyLong_AsInt(presult));
	Py_DECREF(pValue);
	// Clean up
	Py_DECREF(pModule);
	Py_DECREF(pName);
	// Finish the Python Interpreter
	Py_Finalize();

	// clean 
	delete[] procname;

	return _PyLong_AsInt(presult);
}
//Trying to create function to pass vector
int callIntFunc(string proc, list<string> param)
{
	char* procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)"PythonCode");
	// Load the module object
	pModule = PyImport_Import(pName);
	// pDict is a borrowed reference 
	pDict = PyModule_GetDict(pModule);
	// pFunc is also a borrowed reference 
	pFunc = PyDict_GetItemString(pDict, procname);
	
	if (PyCallable_Check(pFunc))
	{
		pValue = Py_BuildValue("[i]", param);
		PyErr_Print();
		presult = PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else
	{
		PyErr_Print();
	}
	//printf("Result is %d\n", _PyLong_AsInt(presult));
	Py_DECREF(pValue);
	// Clean up
	Py_DECREF(pModule);
	Py_DECREF(pName);
	// Finish the Python Interpreter
	Py_Finalize();

	// clean 
	delete[] procname;

	return _PyLong_AsInt(presult);
}


void DisplayMenu() {
	cout << "\n*********************** MENU ***********************\n";
	cout << "*                                                  *\n";
	cout << "* 1- Determine the frequency of each item.         *\n";
	cout << "* 2- Determine the frequency of a specific item.   *\n";
	cout << "* 3- Display frequency of each item as histogram.  *\n";
	cout << "* 4- Exit.                                         *\n";
	cout << "* Enter your selection as a number 1, 2, 3 or 4.   *\n";
	cout << "*                                                  *\n";
	cout << "****************************************************\n";
}

void GroceryHistogram()  {
	ifstream inFS;
	inFS.open("frequency.dat");

	if (!inFS) {
		cout << "Error. Cannot open the file." << endl;
	}
	
	else {
		string item;
		string frequency;
		while (getline(inFS, item, ' ')) {

			getline(inFS, frequency);
			cout << left << setfill(' ') << setw(15) << item << " ";
			int repeat = stoi(frequency);
			cout << string(repeat, '*') << endl;
			
		}
		inFS.close();
	}

}


void main()
{
	ifstream inFS;
	int choice = 0;
	vector<string> groceryItems;
	list<string> pyList;
	unsigned int i;
	string fileDir = "GroceryList.txt";
	string item;

	while (choice != 4) {
		
		DisplayMenu();
		cin >> choice;

		switch (choice) {
		case 1:
			callIntFunc("CountEachWordFrequency", fileDir);
			break;
		case 2:
			cout << "Please specify item to count.\n";
			cin >> item;
			cout << item << ": " << callIntFunc("CountOneWordFrequency", item) << endl;
			break;
		case 3:
			callIntFunc("CreateFile", fileDir);
			GroceryHistogram();
			break;
		case 4:
			cout << "Goodbye.\n";
			exit(0);
			break;
		default:
			while (!(cin >> choice) && (choice < 1 || choice > 3)) {						//While loop to validate user input and discard any invalid input
				cout << "Invalid option\nEnter your selection as a number 1, 2, or 3.\n";
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				DisplayMenu();
				cin >> choice;
			}
			break;
		}
	}
	

}