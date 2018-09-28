//Verison 1 of directory software

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <vector>
#include <sstream>
#include<limits> 
#include <algorithm>
using namespace std;

//Worker class to represent a worker
class Worker {

private:
	string firstName;
	string lastName;

public:
	Worker() {
	}

	void displayName() {
		cout << firstName << " " << lastName << endl;
	}

	void setFirstName(string name) {
		firstName = name;
	}

	void setLastName(string name) {
		lastName = name;
	}

	string combineNames() {
		return (firstName + " " + lastName);
	}

	bool nameComparison(string x) {

		transform(firstName.begin(), firstName.end(), firstName.begin(), ::toupper);
		transform(lastName.begin(), lastName.end(), lastName.begin(), ::toupper);
		transform(x.begin(), x.end(), x.begin(), ::toupper);
		if (firstName.find(x) != string::npos || lastName.find(x) != string::npos)
			return true;
		else
			return false;
	}
};


int main()
{
	vector <Worker> directory;
	int userOption;
	ifstream csvFile;
	while (1) {
		cout << "Enter action number [0, 1, 2, or 3]: ";
		if (!(cin >> userOption)){
			
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Invalid input, try again \n";
			continue;
		}

		if (userOption == 1) {
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			string fileName;
			cout << "\nEnter name of .csv file: ";
			cin >> fileName;

			//Checks if the file is a csv file
			if (fileName.find(".csv") == string::npos) {
				cout << "This file is not a .csv, please enter in a csv file next time. \n";
				continue;
			}
			else {
				csvFile.open(fileName);
			}

			//Checks to see if file can be opened
			if (!csvFile.is_open())
				cout << "The file enter could not be opened, please try again. \n";

			string fName, lName;

			//Read in contents in the file and puts it in the vector
			while (getline(csvFile, lName, ',')) {
				getline(csvFile, fName);
				//Error checking
				cout << fName << lName << endl;

				Worker newWorker;
				newWorker.setFirstName(fName);
				newWorker.setLastName(lName);
				directory.push_back(newWorker);
			}

		}
		else if (userOption == 2) {
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			if (!csvFile.is_open()) {
				cout << "Please open a csv file first" << endl;
				continue;
			}
			string userInput;
			Worker userEntry;
			string fName, lName;

			//Ask for input
			cout << "\nEnter name of new employee (FirstName LastName): ";
			getline(cin, userInput);

			//Copies the string contents
			istringstream iss(userInput);
			iss >> fName;
			userEntry.setFirstName(fName);
			iss >> lName;
			userEntry.setLastName(lName);

			directory.push_back(userEntry);

		}
		else if (userOption == 3) {
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			if (!csvFile.is_open()) {
				cout << "Please open a csv file first" << endl;
				continue;
			}
			string userInput;
			string parsed;
			string combinedName;
			vector <string> parsedInput;

			cout << "\nEnter search query: ";
			getline(cin, userInput);

			//Loop through the vector and check if to find if the user's string matches the directory's names
			istringstream iss(userInput);
			iss >> parsed;

			//init loop for the starting input, if the user puts in multiple inputs, this will be handled in another loop
			for (unsigned int i = 0; i < directory.size(); i++) {
				if (directory[i].nameComparison(parsed) == true) {
					combinedName = directory[i].combineNames();
					parsedInput.push_back(combinedName);
				}
			}

			//This loop is to handle extra search input by user. Ex: "ic el" Above loop looks for ic in the directory
			//and puts it in the parsedInput. This loop will look for el in the parsedInput vector and will remove
			//strings without containing what the user wanted, so words need to contain ic and el.
			while (iss.good()) {
				iss >> parsed;
				transform(parsed.begin(), parsed.end(), parsed.begin(), ::toupper);
				for (unsigned int i = 0; i < parsedInput.size();) {
					transform(parsedInput[i].begin(), parsedInput[i].end(), parsedInput[i].begin(), ::toupper);
					if (parsedInput[i].find(parsed) == string::npos) {
						parsedInput.erase(parsedInput.begin() + i);
					}
					else
						i++;
				}
			}
			
			//Now print out the results
			for (unsigned int i = 0; i < parsedInput.size(); i++) {
				cout << parsedInput[i] << endl;
			}
		}
		else if (userOption == 0)
			break;
	}
	cout << "Program will now exit\n";
    return 0;
}

