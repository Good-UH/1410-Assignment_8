/*COSC 1410, Assignment 8
Tuesday November 11, 2014
Write a  program that reads student records from a file. The student record contains the following information Student ID, Student First Name, Student Last Name, Student Exam Grade
i)		Define the student class
iI)		Read the number of records in the input file
iii)	Create a dynamic array of Student objects
iv)		Read the records from the file and store them in the dynamic array
v)		Print the records on the screen
vi)		Ask the user if s/he wants to delete any records. The user should enter the ID of the students to be deleted. Enter -1 to finish deleting records
vii)	Write the remaining records in the output file
*/
#include <iostream>
#include <fstream>
#include "Student.h"

using namespace std;

bool isFileNameValid(string fileName) //Checks if the file entered is valid
{
	fstream output(fileName, ios::in);

	bool isValid = output.fail();

	output.close();

	return isValid;
}

string getValidFileName() //gets and validates the file name
{
	string fileName = "";

	do
	{
		if (fileName != "")
		{
			system("cls");
			cout << "**************************************************" << endl
				<< "* ERROR: '" << fileName << "' is INVALID file name!\n"
				<< "**************************************************\n\n";
		}
		cout << "\n\tPlease enter file name to load your data (Example: input.txt)\n";
		cout << "\t\tFile Name: ";
		cin >> fileName;

	} while (isFileNameValid(fileName));

	return fileName;
}
void main()
{

	string fileName = getValidFileName();

	int size = 0;
	Student *students = new Student[size];

	string error = Student::loadData(fileName, students, size);

	int id = -1;

	do
	{
		system("cls");

		cout << error;

		Student::print("Records: ", students, size);
		if (size > 0)
		{
			cout << "\n    Please enter the ID of the student to be deleted or enter -1 to exit.\n\n";
			cout << "\tID: ";
			cin >> id;
			cout << "\n";

			error = Student::deleteStudent(id, students, size);
		}

	} while (id != -1);

	Student::print(Student::getModifiedFileName(fileName, "Output"), "Records", students, size);

	delete[] students;
	system("pause");
}