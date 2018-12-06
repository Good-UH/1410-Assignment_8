#include <iostream>
#include <sstream>
#include <fstream>
#include "Student.h"

#pragma region Constructors

Student::Student()
{

}

Student::Student(int id, string firstName, string lastName, double examGrade)
{
	string error = setStudent(id, firstName, lastName, examGrade);

	displayError(error);
}
#pragma endregion Constructors

#pragma region Setters

string Student::setStudent(int id, string firstName, string lastName, double examGrade)
{
	string errors = "";

	errors = addError(errors, setLastName(lastName));
	errors = addError(errors, setFirstName(firstName));
	errors = addError(errors, setID(id));
	errors = addError(errors, setExamGrade(examGrade));

	return errors;
}

string Student::setID(int id)
{
	string errors = isIDValid(id);

	if (errors == "")
		_id = id;

	return errors;
}

string Student::setFirstName(string firstName)
{
	string errors = isNameValid(firstName, "First Name");

	if (errors == "")
		_firstName = firstName;

	return errors;
}

string Student::setLastName(string lastName)
{
	string errors = isNameValid(lastName, "Last Name");

	if (errors == "")
		_lastName = lastName;

	return errors;
}

string Student::setExamGrade(double examGrade)
{
	string errors = isExamGradeValid(examGrade);

	if (errors == "")
		_examGrade = examGrade;

	return errors;
}

#pragma endregion Setters

#pragma region Delete

string Student::deleteStudent()
{
	string error = "";

	if (!_isDeleted)
		_isDeleted = true;
	else
		error = getErrorHeader("Delete", "") + "	Reason: Already deleted!\n";

	return error;
}

string Student::deleteStudent(int id)
{
	stringstream errors;

	if (id == getID())
		return deleteStudent();
	else
	{
		errors << getErrorHeader("Delete", "")
			<< "	Reason: IDs do NOT match!\n"
			<< "		Given ID: " << id << endl
			<< "		Actual ID: " << getID() << endl;
	}

	return errors.str();
}

bool Student::isDeleted()
{
	return _isDeleted;
}

string Student::deleteStudent(int idToBeDeleted, Student *students, int size) //deleting student records
{
	string errors = "";
	bool found = false;

	for (int index = 0; index < size; index++)
	{
		if (idToBeDeleted == students[index].getID())
		{
			errors = addError(errors, students[index].deleteStudent(idToBeDeleted));
			found = true;
		}
	}

	if (!found)
	{
		stringstream error;
		error << "*** Error: Failed to Delete!\n	Reason: ID:" << idToBeDeleted << " does NOT exist!\n";
		errors = error.str();
	}

	return errors;
}

#pragma endregion Delete

#pragma region Getters 
//getters to help access private variables
int Student::getID()
{
	return _id;
}

string Student::getFirstName()
{
	return _firstName;
}

string Student::getLastName()
{
	return _lastName;
}

double Student::getExamGrade()
{
	return _examGrade;
}

#pragma endregion Getters

#pragma region Errors

void Student::displayError(string error) //Display the error
{
	if (error != "")
		cout << endl << error << endl;
}

string Student::addError(string errors, string newError) //Adding errrors
{
	if (newError != "")
		errors += "\n" + newError;

	return errors;
}

string Student::getErrorHeader(string action, string errorTitle) //Showing the error
{
	stringstream errors;

	errors << "*** Error -> Failed to " << action << " " << errorTitle << " for Student: "
		<< _id << ": " << _firstName << " " << _lastName << endl;

	return errors.str();
}

#pragma endrigion Errors

#pragma region Validations

string Student::isIDValid(int id) //Validating student ID
{
	stringstream errors;
	string error = "";

	if (id == 0)
	{
		error = "		0 IDs are NOT allowed!\n";
	}
	else if (id < 0)
	{
		error = "		Negative IDs are NOT allowed!\n";
	}

	if (error != "")
	{
		errors << getErrorHeader("Set", "ID");
		errors << "		ID must be greater than 0!\n";
		errors << error;
		errors << "			'" << id << "'	is INVALID ID!\n";
	}

	return errors.str();
}

string Student::isNameValid(string name, string errorTitle) //Validate Student Name
{
	stringstream errors;
	string error = "";

	if (name.length() < 2) //Name must be at least 2 letters 
		errors << "			'" << name.length() << "' is INVALID length!\n";
	else
	{
		if (!isalpha(name[0]))
			errors << "			'" << name[0] << "' is INVALID starting character!\n";
		if (!isalpha(name[name.length() - 1]))
			errors << "			'" << name[0] << "' is INVALID ending character!\n";
	}

	for (int index = 0; index < name.length(); index++)
	{
		if (!(isalpha(name[index]) || name[index] == '-' || name[index] == ' '))
		{
			errors << "			'" << name[index] << "' is INVALID character!\n";
		}
	}

	if (errors.str() != "")
	{
		error = getErrorHeader("Set", "First Name");
		error += errors.str();
		error += "	Rules: \n";
		error += "		1. Must start with alpha character!\n";
		error += "		2. Must end with alpha character!\n";
		error += "		3. ONLY alpha, space and dash are acceptable characters!\n";
		error += "		4. Length must be 3 or more characters!\n";

	}

	return error;
}

string Student::isExamGradeValid(double examGrade) //Validate Exam Grade
{
	stringstream errors;
	string error = "";

	if (examGrade > 100)
	{
		error = "		Exam Grades greater than 100 are NOT allowed!\n";
	}
	else if (examGrade < 0)
	{
		error = "		Negative Exam Grades are NOT allowed!\n";
	}

	if (error != "")
	{
		errors << getErrorHeader("Set", "Exam Grade");
		errors << "		Exam Grade must be between 0 and 100!\n";
		errors << error;
		errors << "		'" << examGrade << "' is INVALID Exam Grade!\n";
	}

	return errors.str();
}

#pragma endregion Validations

#pragma region Display

string Student::toString(bool isListStyle) //Display on console
{
	stringstream output;

	if (isListStyle)
		output << getID()
		<< "\t" << getExamGrade()
		<< "\t" << getLastName() << ", " << getFirstName() << endl;
	else
		output << "\t" << "		ID: " << getID() << endl
		<< "\t" << "First Name: " << getFirstName() << endl
		<< "\t" << "Last Name: " << getLastName() << endl
		<< "\t" << "Exam Grade: " << getExamGrade() << endl;

	return output.str();

}

void Student::print(bool isListStyle)
{
	cout << toString(isListStyle);
}

void Student::print(string title, Student *students, int size) //priniting the info to the output screen
{
	cout << "\n" << title << endl;

	int counter = 0;

	for (int index = 0; index < size; index++)
	{
		if (!students[index].isDeleted())
			cout << "\t" << ++counter << ". " << students[index].toString(true);
	}

	if (size <= 0)
		cout << "\t" << "NO DATA!\n";
}

void Student::print(string fileName, string title, Student* students, int size) //printing the info to an output file
{
	int counter = 0;

	stringstream fileData;

	for (int index = 0; index < size; index++)
	{
		if (!students[index].isDeleted())
			fileData << "\t" << ++counter << ". " << students[index].toString(true);
	}

	if (size <= 0)
		fileData << "\t" << "NO DATA!\n";

	fstream file(fileName, ios::out);

	if (!file.fail())
	{
		file << counter << endl;
		file << fileData.str();

	}

	file.close();
}

#pragma endregion Display

string Student::loadData(string fileName, Student* &students, int &size) //loading the data
{
	int numberOfLines = 0;
	int numberOfStoredStudents = 0;
	int numberOfIgnoredStudents = 0;

	stringstream errors;

	fstream input(fileName, ios::in); //reading the input file

	if (input.fail()) //if there is a error with the input file
	{
		errors << "*** Error: Failed to load the data!\n"
			<< "    Reason: Failed to open file ('" << fileName << "')!\n";
	}
	else
	{
		stringstream inputStream = getNextStream(input);
		numberOfLines++;
		int errorCount = 0;

		bool isNumeric = true;

		for (int index = 0; index < inputStream.str().length(); index++)
		{
			if (!isalnum(inputStream.str()[index]))
			{
				isNumeric = false;
				break;
			}
		}

		if (isNumeric) //Reading in the size and records 
		{
			inputStream >> size;

			if (size < 0)
				size = 0;

			delete[] students;
			students = new Student[size];

			while (!input.eof())
			{
				inputStream = getNextStream(input);
				string line = inputStream.str();

				numberOfLines++;

				if (line != "\n" && line != "" && line != "\0") //reading the strings and ignoring not valid info
				{
					try
					{
						int id = 0;
						string firstName = "";
						string lastName = "";
						double examGrade = 0.0;

						inputStream >> id >> firstName >> lastName >> examGrade;

						Student student;

						string error = student.setStudent(id, firstName, lastName, examGrade);

						if (error != "")
						{
							errors << "*************\n"
								<< "* Error " << ++errorCount << ":\n"
								<< "*************\n"
								<< "    Failed to store Line " << numberOfLines << " successfully!\n"
								<< "      Line: " << line << endl
								<< "      Reason: INVALID Student!" << endl;
							errors << error;
							numberOfIgnoredStudents++;
						}
						else
						{
							if (numberOfStoredStudents < size)
							{
								students[numberOfStoredStudents++] = student;
							}
							else
							{
								numberOfIgnoredStudents++;
								errors << "*************\n"
									<< "* Error " << ++errorCount << ":\n"
									<< "*************\n"
									<< "    Failed to store Line " << numberOfLines << " successfully!\n"
									<< "      Line: " << line << endl
									<< "      Reason: NOT enough space!" << endl;
							}
						}
					}
					catch (int e)
					{
						errors << "*************\n"
							<< "* Error " << ++errorCount << ":\n"
							<< "*************\n"
							<< "    Failed to read Line " << numberOfLines << "successfully!\n"
							<< "      Line: " << line << endl;
						numberOfIgnoredStudents++;
					}

				}

			}
		}
		else
			errors << "    Failed to read size '" << inputStream.str() << "' successfully!\n" << endl;
	}
	//Output file called messages that points out the student records that were not read due to errors
	string file = getModifiedFileName(fileName, "Messages");

	errors << "**************************************************" << endl
		<< "* Number of Stored  Students: " << numberOfStoredStudents << endl
		<< "* Number of Ignored Students: " << numberOfIgnoredStudents << endl
		<< "* System messages are stored in " << file << endl
		<< "**************************************************" << endl;

	fstream output(file, ios::out);

	if (!output.fail()) {
		output << errors.str();
	}

	output.close();

	size -= numberOfIgnoredStudents;

	return errors.str();
}

stringstream Student::getNextStream(fstream &inputFile) //reading information from the input file
{
	stringstream inputStream;

	if (!inputFile.fail() && !inputFile.eof())
	{
		string line;

		getline(inputFile, line);

		inputStream.str("");
		inputStream.clear();

		inputStream << line;
	}

	return inputStream;
}

string Student::getModifiedFileName(string fileName, string modification) //used to make an updated(output file)
{
	string file = "";

	for (int index = 0; index < fileName.length(); index++)
	{
		if (fileName[index] == '.')
			break;

		file += fileName[index];
	}

	file += modification + ".txt";

	return file;
}