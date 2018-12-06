#pragma once
#ifndef __STUDENT_H__
#define __STUDENT_H__

#include <string>

using namespace std;

class Student
{
public:
#pragma region Constructors
	//Default Constructor
	Student();
	/*
	ID:
		ID must be greater than 0:
			1. Negative IDs are NOT valid.
			2. 0 IDs are NOT valid.

	Exam Grade:
		Acceptable Range of Exam Grades between 0 and 100:
			1. Negative Exam Grades are NOT valid.
			2. Exam Grades greater than 100 are NOT valid.

	Function will display error if encountered!
	*/
	//Constructor with 4 arguements
	Student(int id, string firstName, string lastName, double examGrade);
#pragma endregion Constructors

#pragma region Setters
	//Defining the member functions (setters) to help access member variables and create validations
	/*
	ID:
		ID must be greater than 0:
			1. Negative IDs are NOT valid.
			2. 0 IDs are NOT valid.

	Exam Grade:
		Acceptable Range of Exam Grades between 0 and 100:
			1. Negative Exam Grades are NOT valid.
			2. Exam Grades greater than 100 are NOT valid.

	Function will return error if encountered!
	*/
	string setStudent(int id, string firstName, string lastName, double examGrade);

	/*
	ID must be greater than 0:
		1. Negative IDs are NOT valid.
		2. 0 IDs are NOT valid.
	Function will return error if encountered!
	*/
	string setID(int id);

	string setFirstName(string firstName);

	string setLastName(string lastName);

	/*
	Acceptable Range of Exam Grades between 0 and 100:
		1. Negative Exam Grades are NOT valid.
		2. Exam Grades greater than 100 are NOT valid.
	Function will return error if encountered!
	*/
	string setExamGrade(double examGrade);
#pragma endregion  Setters

#pragma region Delete
	
	string deleteStudent();

	string deleteStudent(int id);

	bool isDeleted();

	static string deleteStudent(int idToBeDeleted, Student *students, int size);

#pragma endregion Delete

#pragma region Getters
	//Defining the member functions (getters) to help access member variables and create validations
	int getID();
	string getFirstName();
	string getLastName();
	double getExamGrade();

#pragma endregion Getters

#pragma region Errors

	static void displayError(string error);
	static string addError(string errors, string newError);
	string getErrorHeader(string action, string errorTitle);

#pragma endregion Errors

#pragma region Display

	string toString(bool isListStyle);
	void print(bool isListStyle);
	static void print(string title, Student *students, int size);
	static void print(string fileName, string title, Student *students, int size);

#pragma endregion Display

	static string loadData(string fileName, Student* &students, int &size);
	static string getModifiedFileName(string fileName, string modification);

private:
	//Initialize member variables
	int _id = 0;
	string _firstName = "";
	string _lastName = "";
	double _examGrade = 0.0;
	bool _isDeleted = false;

	string isIDValid(int id);
	string isNameValid(string name, string errorTitle);
	string isExamGradeValid(double examGrade);

	static stringstream getNextStream(fstream &inputFile);
};
#endif // !__STUDENT_H__
