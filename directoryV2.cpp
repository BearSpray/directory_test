//Version 2

#include "csv.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <vector>
#include <sstream>
#include<limits> 
#include <algorithm>
using namespace std;

//Person class to represent a person (could have been abstract)
class Person {

protected:
	int userID;
	string firstName;
	string lastName;
	string eMail;
	string role;

public:
	Person() {
	}

	Person(int a, string b, string c, string d, string e) {
		userID = a;
		firstName = b;
		lastName = c;
		eMail = d;
		role = e;
	}

	virtual void fillInfo(string fName, string lName, string r) {
		firstName = fName;
		lastName = lName;
		role = r;
		
		cout << "\nEnter the User ID for the "<< role << ": ";
		cin >> userID;
		cin.clear();
		cin.ignore(10000, '\n');

		cout << "\nEnter the e-mail for the "<< role << ": ";
		getline(cin, eMail);
	}

	virtual void printAll() {
		cout << "User ID: " << userID << endl;
		cout << "Name: " << combineNames() << endl;
		cout << "E-mail: " << eMail << endl;
		cout << "Role: " << role << endl;
	}

	string combineNames() {
		return (firstName + " " + lastName);
	}

	bool nameComparison(string x, string a, string b) {

		transform(firstName.begin(), firstName.end(), a.begin(), ::toupper);
		transform(lastName.begin(), lastName.end(), b.begin(), ::toupper);
		transform(x.begin(), x.end(), x.begin(), ::toupper);
		cout << a << b << endl;
		if (a.find(x) != string::npos || b.find(x) != string::npos)
			return true;
		else
			return false;
	}

	virtual void copyVector(vector<string>*v) {}

	virtual void printCourse() {}

	virtual void getPaid() {}
	
	virtual bool checkCourse(string course){
		return false;
	}

	string returnEmail() {
		return eMail;
	}

	string returnRole() {
		return role;
	}

};

class Student : virtual public Person {
private:
	int GPA;
	vector <string> courseTaken;
	vector <string> courseTaking;

public:
	Student() : Person(){}

	Student(int a, string b, string c, string d, string e, int gpa, vector <string> a2, vector <string> b2)
		: Person(a,b,c,d,e), GPA(gpa), courseTaken(move(a2)), courseTaking(move(b2)) {}

	virtual void fillInfo(string fName, string lName, string r) override {
		Person::fillInfo(fName, lName, r);
		string aClass;

		cout << "\nEnter the GPA for the student: ";
		cin >> GPA;
		cin.clear();
		cin.ignore(10000, '\n');

		cout << "\nEnter the class(es) the "<< role << " is taking: ";
		getline(cin, aClass);
		istringstream iss2(aClass);
		string token;
		while (getline(iss2, token, ',')) {
			token.erase(remove_if(token.begin(), token.end(), isspace), token.end());
			transform(token.begin(), token.end(), token.begin(), ::toupper);
			courseTaking.push_back(token);
		}
		aClass.clear();
		cout << "\nEnter the class(es) the " << role << " has taken: ";
		getline(cin, aClass);
		istringstream iss3(aClass);
		while (getline(iss3, token, ',')) {
			token.erase(remove_if(token.begin(), token.end(), isspace), token.end());
			transform(token.begin(), token.end(), token.begin(), ::toupper);
			courseTaken.push_back(token);
		}
		iss2.clear();
	}

	virtual void printAll() override {
		Person::printAll();
		cout << this->combineNames() << "'s GPA: " << GPA << endl;
		
		cout << "List of courses " << this->combineNames() << " has taken: ";
		for (unsigned int i = 0; i < courseTaken.size(); i++) {
			cout << courseTaken[i] << endl;
		}		

		cout << "List of courses " << this->combineNames() << " is taking: ";
		for (unsigned int i = 0; i < courseTaking.size(); i++) {
			cout << courseTaking[i] << endl;
		}
	}

	virtual bool checkCourse(string course) override {
		for (unsigned int i = 0; i < courseTaking.size(); i++) {
			if (courseTaking[i].compare(course) == 0)
				return true;
		}
	}

	virtual void copyVector(vector <string> *v) override{
		for (unsigned int i = 0; i < courseTaking.size(); i++) {
			v->push_back(courseTaking[i]);
		}
	}
};

class Staff : virtual public Person {
protected:
	int salary;
	int pay;

public:
	Staff() :Person() {}
	
	Staff(int a, string b, string c, string d, string e, int money) : Person(a, b, c, d, e), salary(money), pay(0){}

	virtual void fillInfo(string fName, string lName, string r) override{
		Person::fillInfo(fName, lName, r);
		cout << "\nEnter the salary for the " << role << ": ";
		cin >> salary;
		cin.clear();
		cin.ignore(10000, '\n');
	}
	
	virtual void printAll() override {
		Person::printAll();
		cout << this->combineNames() << "'s salary: " << salary << endl;
		cout << this->combineNames() << " earned $" << this->pay<< " from working" << endl;
	}
	
	virtual bool checkCourse(string course) override{
		return false;
	}

	virtual void getPaid()override {
		pay += salary;
	}
};

class TA : virtual public Staff, virtual public Student {
private:
	int hoursWorked;
	vector <string> courseTeaching;

public:
	TA() :Staff(), Student() {}
	
	TA(int a, string b, string c, string d, string e, int gpa, vector <string> a2, vector <string> b2, int money, int hours, vector <string> c2) 
		: Staff(a, b, c, d, e, money), Student(a, b, c, d, e, gpa, a2, b2), hoursWorked(hours), courseTeaching(move(c2)){}

	virtual void fillInfo(string fName, string lName, string r)override {
		string aClass;
		Student::fillInfo(fName, lName, r);
		
		cout << "\nEnter the salary for the " << role <<  ": ";
		cin >> salary;
		cin.clear();
		cin.ignore(10000, '\n');;
		
		cout << "\nEnter the class the " << role << " is teaching: ";
		getline(cin, aClass);
		istringstream iss4(aClass);
		string token;
		while (getline(iss4, token, ',')) {
			token.erase(remove_if(token.begin(), token.end(), isspace), token.end());
			transform(token.begin(), token.end(), token.begin(), ::toupper);
			courseTeaching.push_back(token);
		}
		iss4.clear();
	}

	virtual void printAll() override {
		Student::printAll();
		cout << "List of courses " << this->combineNames() << " is teaching: ";
		for (unsigned int i = 0; i < courseTeaching.size(); i++) {
			cout << courseTeaching[i] << endl;
		}
		cout << this->combineNames() << "'s salary: " << this->salary << endl;
		cout << this->combineNames() << " has worked for " << hoursWorked << " hour(s) " << endl;
		cout << this->combineNames() << " earned $" << this->pay << " from working" << endl;
	}

	virtual bool checkCourse(string course) override{
		for (unsigned int i = 0; i < courseTeaching.size(); i++) {
			if (courseTeaching[i].compare(course) == 0)
				return true;
		}
	}

	virtual void getPaid() {
		pay = hoursWorked * salary;
	}
};

class Instructor : virtual public Staff {
private:
	vector <string> courseTeaching;

public:
	Instructor() : Staff() {}

	Instructor(int a, string b, string c, string d, string e, int money, vector <string> a2) : Staff(a, b, c, d, e, money), courseTeaching(move(a2)) {}

	virtual void fillInfo(string fName, string lName, string r)override{
		string aClass;
		Staff::fillInfo(fName, lName, r);

		cout << "\nEnter the class the " << role << " is teaching: ";
		getline(cin, aClass);
		istringstream iss2(aClass);
		string token;
		while (getline(iss2, token, ',')) {
			token.erase(remove_if(token.begin(), token.end(), isspace), token.end());
			transform(token.begin(), token.end(), token.begin(), ::toupper);
			courseTeaching.push_back(token);
		}
		iss2.clear();
	}

	virtual void printAll() override {
		Staff::printAll();
		cout << "List of courses " << this->combineNames() << " is teaching: ";
		for (unsigned int i = 0; i < courseTeaching.size(); i++) {
			cout << courseTeaching[i] << endl;
		}
		cout << this->combineNames() << "'s salary: " << this->salary << endl;
	}

	virtual bool checkCourse(string course) override{
		for (unsigned int i = 0; i < courseTeaching.size(); i++) {
			if (courseTeaching[i].compare(course) == 0)
				return true;
		}
	}

	virtual void printCourse() {
		for (unsigned int i = 0; i < courseTeaching.size(); i++) {
			cout << courseTeaching[i] << endl;
		}
	}
	
	virtual void getPaid() {
		pay = courseTeaching.size() * salary;
	}
};


int main() {
	vector <Person*> directory;
	int userOption;
	bool opened = false;

	while (1) {
		cout << "Enter action number [0, 1, 2, 3, 4 ,5 , 6, or 7]: ";
		//Checks if the input is a int
		if (!(cin >> userOption)) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Invalid input, try again \n";
			continue;
		}

		//Option that reads in csv file using csv.h
		else if (userOption == 1) {

			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			string fileName;
			cout << "\nEnter name of .csv file: ";
			cin >> fileName;

			//Checks if the file is a csv file
			if (fileName.find(".csv") == string::npos) {
				cout << "This file is not a .csv, please enter in a csv file next time. \n";
				continue;
			}

			io::CSVReader<11> in(fileName);
			in.read_header(io::ignore_extra_column | io::ignore_missing_column, "First Name", "Last Name", "Email", "User ID"
				, "Role", "Course Teaching", "Courses Taken", "Courses Taking", "GPA", "Salary", "Hours Worked");
			string fName = ""; string lName = ""; string email = ""; int id = 0; string role = ""; string cTeaching = "";
			string cTaken = ""; string cTaking = ""; int gpa = 0; int salary = 0; int hours = 0;
			while (in.read_row(fName, lName, email, id, role, cTeaching, cTaken, cTaking, gpa, salary, hours)) {
				if (role == "student") {
					vector <string> taking, taken;
					string token;
					istringstream iss(cTaking);
					while (getline(iss, token, ',')) {
						token.erase(remove_if(token.begin(), token.end(), isspace), token.end());
						transform(token.begin(), token.end(), token.begin(), ::toupper);
						taking.push_back(token);
					}
					istringstream iss2(cTaken);
					while (getline(iss2, token, ',')) {
						token.erase(remove_if(token.begin(), token.end(), isspace), token.end());
						transform(token.begin(), token.end(), token.begin(), ::toupper);
						taken.push_back(token);
					}
					Student *s = new Student(id, fName, lName, email, role, gpa, taken, taking);
					directory.push_back(s);
				}
				else if (role == "staff") {
					Staff *s = new Staff(id, fName, lName, email, role, salary);
					directory.push_back(s);
				}
				else if (role == "instructor") {
					vector <string> cTeach;
					string token;
					istringstream iss(cTeaching);
					while (getline(iss, token, ',')) {
						token.erase(remove_if(token.begin(), token.end(), isspace), token.end());
						transform(token.begin(), token.end(), token.begin(), ::toupper);
						cTeach.push_back(token);
					}
					Instructor *i = new Instructor(id, fName, lName, email, role, salary, cTeach);
					directory.push_back(i);
				}
				else if (role == "TA") {
					vector <string> cTeach, taking, taken;
					string token;
					istringstream iss(cTaking);
					while (getline(iss, token, ',')) {
						token.erase(remove_if(token.begin(), token.end(), isspace), token.end());
						transform(token.begin(), token.end(), token.begin(), ::toupper);
						taking.push_back(token);
					}
					istringstream iss2(cTaken);
					while (getline(iss2, token, ',')) {
						token.erase(remove_if(token.begin(), token.end(), isspace), token.end());
						transform(token.begin(), token.end(), token.begin(), ::toupper);
						taken.push_back(token);
					}
					istringstream iss3(cTeaching);
					while (getline(iss3, token, ',')) {
						token.erase(remove_if(token.begin(), token.end(), isspace), token.end());
						transform(token.begin(), token.end(), token.begin(), ::toupper);
						cTeach.push_back(token);
					}
					TA *t = new TA(id, fName, lName, email, role, gpa, taken, taking, salary, hours, cTeach);
					directory.push_back(t);
				}
				else{
					Person *p = new Person(id, fName, lName, email, role);
					directory.push_back(p);
				}
			}
			opened = true;
		}

		//Option that allows the user to add in people to the directory
		else if (userOption == 2) {
			//Clear cin and check if a file is opened
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			if (opened == false) {
				cout << "Please open a csv file first" << endl;
				continue;
			}
			//Declare variables to store user input and 
			string userInput;
			int id;
			string fName, lName, role;

			//Ask for input
			cout << "\nEnter name of new employee (FirstName LastName): ";
			getline(cin, userInput);

			//Copies the string contents
			istringstream iss(userInput);
			iss >> fName;
			if (iss.good()) {
				iss >> lName;
			}

			//Prompts for the role
			cout << "\nEnter the role of this person: ";
			getline(cin, role);
			istringstream iss2(role);
			iss2 >> role;
			//Fills in information based on the role. Each class will fill by itself and will prompt further user input
			if (role.compare("student") == 0) {
				Student *s = new Student();
				s->fillInfo(fName, lName, role);
				directory.push_back(s);
			}
			else if (role.compare("staff") == 0) {
				Staff *s = new Staff();
				s->fillInfo(fName, lName, role);
				directory.push_back(s);
			}
			else if (role.compare("TA") == 0) {
				TA *t = new TA();
				t->fillInfo(fName, lName, role);
				directory.push_back(t);
			}
			else if (role.compare("instructor") == 0) {
				Instructor *i = new Instructor();
				i->fillInfo(fName, lName, role);
				directory.push_back(i);
			}
			else {
				cout << "Invalid role entered. Valid roles are: student, staff, TA, instructor." << endl;
			}
		}

		//Option that searches through the directory based of key words that are seperated by spaces. More info in the conditional statment
		else if (userOption == 3) {
			//Clear cin and check if a file is opened
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			if (opened == false) {
				cout << "Please open a csv file first" << endl;
				continue;
			}
			//Declare variables for user input and storing parsed strings
			string userInput;
			//Fake strings are empty and is used in transform function for comparsion
			string parsed, fakeStr1, fakeStr2 = "";
			//string combinedName;
			//Vector to store our results
			vector <Person*> parsedInput;

			//Get the strings from user for our search
			cout << "\nEnter search query: ";
			getline(cin, userInput);

			//Loop through the vector and check if to find if the user's string matches the directory's names
			istringstream iss(userInput);
			iss >> parsed;

			//init loop for the starting input, if the user puts in multiple inputs, this will be handled in another loop
			for (unsigned int i = 0; i < directory.size(); i++) {
				if (directory[i]->nameComparison(parsed, fakeStr1, fakeStr2) == true) {
					//combinedName = directory[i].combineNames();
					parsedInput.push_back(directory[i]);
				}
			}

			//This loop is to handle extra search input by user. Ex: "ic el" Above loop looks for ic in the directory
			//and puts it in the parsedInput. This loop will look for el in the parsedInput vector and will remove
			//strings without containing what the user wanted, so words need to contain ic and el.
			while (iss.good()) {
				iss >> parsed;
				//transform(parsed.begin(), parsed.end(), parsed.begin(), ::toupper);
				for (unsigned int i = 0; i < parsedInput.size();) {
					//transform(parsedInput[i].combineNames().begin(), parsedInput[i].combineNames().end(), compareVec[i].begin(), ::toupper);
					fakeStr1.clear();
					fakeStr2.clear();
					if (parsedInput[i]->nameComparison(parsed, fakeStr1, fakeStr2) == false) {
						parsedInput.erase(parsedInput.begin() + i);
					}
					else
						i++;
				}
			}

			//Now print out the results
			for (unsigned int i = 0; i < parsedInput.size(); i++) {
				parsedInput[i]->printAll();
				cout << "======================================" << endl;
			}
		}

		//Option to tell which Instructors, TAs, and students are involved in a course
		else if (userOption == 4) {
			//Clear cin and check if a file is opened
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			if (opened == false) {
				cout << "Please open a csv file first" << endl;
				continue;
			}

			//String to store the class the user will enter
			string course;
			vector <Person*> instructors, TAs, students;

			cout << "Enter the course to search for it's student enrollment and Instructors + TAs: ";
			getline(cin, course);

			//Checks the directory and allociate the appropiate vectors if a person is associated with the course
			for (unsigned int i = 0; i < directory.size(); i++) {
				if (directory[i]->checkCourse(course) == true) {
					if (directory[i]->returnRole() == "student")
						students.push_back(directory[i]);
					else if (directory[i]->returnRole() == "TA")
						TAs.push_back(directory[i]);
					else if (directory[i]->returnRole() == "instructor")
						instructors.push_back(directory[i]);
				}
			}

			//Prints out the Instructors, TAs, and students that are involved with the course
			cout << "List of Instructors that teach " << course << ":" << endl;
			for (unsigned int i = 0; i < instructors.size(); i++) {
				cout << instructors[i]->combineNames() << endl;
			}
			cout << "====================================" << endl;
			cout << "List of TAs that teach " << course << ":" << endl;
			for (unsigned int i = 0; i < TAs.size(); i++) {
				cout << TAs[i]->combineNames() << endl;
			}
			cout << "====================================" << endl;
			cout << "List of students that are currently enrolled in " << course << ":" << endl;
			for (unsigned int i = 0; i < students.size(); i++) {
				cout << students[i]->combineNames() << endl;
			}
		}

		//Lists all the courses students are taking without a instructor in the directory and all the instructors with the courses they are teaching
		else if (userOption == 5) {
			//Clear cin and check if a file is opened
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			if (opened == false) {
				cout << "Please open a csv file first" << endl;
				continue;
			}

			//Vector to store the total courses students are taking
			vector <string>	studentCourses;
			for (unsigned int i = 0; i < directory.size(); i++) {
				if (directory[i]->returnRole() == "student") {
					directory[i]->copyVector(&studentCourses);
				}
			}

			//Now iterate the courses and remove courses that do not have instructors based on directory
			for (unsigned int i = 0; i < directory.size(); i++) {
				if (directory[i]->returnRole() == "instructor") {
					for (unsigned int j = 0; j < studentCourses.size(); j++) {
						if (directory[i]->checkCourse(studentCourses[j]) == true)
							studentCourses.erase(studentCourses.begin() + j);
					}
				}
			}

			//Now to print everything out
			cout << "Enrolled classes without instructors: " << endl;
			for (unsigned int i = 0; i < studentCourses.size(); i++) {
				cout << studentCourses[i] << endl;
			}

			cout << "====== List of Instructors and Classes they teach =========" << endl;
			for (unsigned int i = 0; i < directory.size(); i++) {
				if (directory[i]->returnRole() == "instructor") {
					cout << directory[i]->combineNames() << " teaches: ";
					directory[i]->printCourse();
				}
			}

		}

		//This option will increase the payment of each staff member (PAYDAY for everybody except students)
		else if (userOption == 6) {
			//Short code to pay everybody. Specifics on how each person is paid is in the class' function
			for (unsigned int i = 0; i < directory.size(); i++) {
				if (directory[i]->returnRole() != "student")
					directory[i]->getPaid();
			}
		}

		//Option will allow user to enter a name then a list of e-mails. Then will display if the e-mails can be sent by that person
		//in directory
		else if (userOption == 7) {
			//Clear cin and check if a file is opened
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			if (opened == false) {
				cout << "Please open a csv file first" << endl;
				continue;
			}

			//Declare variables for user input and storing parsed strings
			string userInput;
			//Fake strings are empty and is used in transform function for comparsion
			string fName, lName, fakeA, fakeB, r, line, token;

			//Get the strings from user for our search
			cout << "\nEnter name of person: ";
			getline(cin, userInput);

			//Loop through the vector and check if to find if the user's string matches the directory's names
			istringstream iss(userInput);
			iss >> fName;
			if (iss.good()) {
				iss >> lName;
			}


			//Store e-mail list and specific lists
			vector <string> list, inList, taList, stuList, staList;

			//Get the string of e-mails
			cout << "\nList of e-mails (seperate by commas): ";
			getline(cin, line);
			istringstream iss3(line);
			while (getline(iss3, token, ',')) {
				list.push_back(token);
			}

			//Returns the role of the person + checks the e-mail list and sees if anyone owns that e-mail and pushes to
			//appropriate vector list. Pretty long runtime, kinda.
			for (unsigned int i = 0; i < directory.size(); i++) {
				if (directory[i]->nameComparison(fName, fakeA, fakeB) == true && directory[i]->nameComparison(lName, fakeA, fakeB) == true) {
					r = directory[i]->returnRole();
				}
				for (unsigned j = 0; j < list.size(); j++) {
					if (directory[i]->returnEmail() == list[j]) {
						if (directory[i]->returnRole() == "student")
							stuList.push_back(directory[i]->returnEmail());
						else if (directory[i]->returnRole() == "TA")
							taList.push_back(directory[i]->returnEmail());
						else if (directory[i]->returnRole() == "staff")
							staList.push_back(directory[i]->returnEmail());
						else if (directory[i]->returnRole() == "instructor")
							inList.push_back(directory[i]->returnEmail());
					}
				}
			}

			//Already have all the e-mails sorted and know the role of the person, just printing now
			//Pretty lazy implementation
			if (r == "student") {
				cout << "Can e-mail the following: " << endl;
				for (unsigned i = 0; i < taList.size(); i++) {
					cout << taList[i] << endl;
				}
				cout << "--------------------------------" << endl;
				cout << "CANNOT e-mail the following: " << endl;
				for (unsigned i = 0; i < inList.size(); i++) {
					cout << inList[i] << endl;
				}
				for (unsigned i = 0; i < staList.size(); i++) {
					cout << staList[i] << endl;
				}
				for (unsigned i = 0; i < stuList.size(); i++) {
					cout << stuList[i] << endl;
				}
			}
			else if (r == "TA") {
				for (unsigned i = 0; i < stuList.size(); i++) {
					cout << taList[i] << endl;
				}
				for (unsigned i = 0; i < taList.size(); i++) {
					cout << stuList[i] << endl;
				}
				for (unsigned i = 0; i < inList.size(); i++) {
					cout << inList[i] << endl;
				}
				cout << "--------------------------------" << endl;
				cout << "CANNOT e-mail the following: " << endl;
				for (unsigned i = 0; i < staList.size(); i++) {
					cout << staList[i] << endl;
				}
			}
			else if (r == "instructor") {
				for (unsigned i = 0; i < inList.size(); i++) {
					cout << inList[i] << endl;
				}
				cout << "CANNOT e-mail the following: " << endl;
				for (unsigned i = 0; i < staList.size(); i++) {
					cout << staList[i] << endl;
				}
				cout << "--------------------------------" << endl;
				for (unsigned i = 0; i < stuList.size(); i++) {
					cout << taList[i] << endl;
				}
				for (unsigned i = 0; i < taList.size(); i++) {
					cout << stuList[i] << endl;
				}
			}
			else if (r == "staff") {
				for (unsigned i = 0; i < stuList.size(); i++) {
					cout << taList[i] << endl;
				}
				for (unsigned i = 0; i < taList.size(); i++) {
					cout << stuList[i] << endl;
				}
				for (unsigned i = 0; i < staList.size(); i++) {
					cout << staList[i] << endl;
				}
				cout << "--------------------------------" << endl;
				cout << "CANNOT e-mail the following: " << endl;
				for (unsigned i = 0; i < inList.size(); i++) {
					cout << inList[i] << endl;
				}
			}

		}

		//Error check if input is beyond the available options
		else if (userOption > 7 || userOption < 0) {
			cout << "Invalid input, try again \n";
			continue;
		}

		//else if (userOption == 8) {
		//	for (unsigned int i = 0; i < directory.size(); i++) {
		//		directory[i]->printAll();
		//	}

		//}

		//Exits the program
		else if (userOption == 0)
			break;
	}

	return 0;
}
