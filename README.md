This repo contains the directory software being created by me. Two versions are uploaded so far

Version 1:
Functionality: Read in csv file and store in a vector in memory called directory, add worker into directory by making new object and pushing into directory, searches directory based off string with keywords by parsing the string and using string function find().

Options:
1. Read in csv file and store in a vector in memory called directory
2. Prompts for first and last name of a perosn and the adds person into directory
3. Search based off string of keywords provided by user

Version 2:
Functionality: similar as v1 but with more options for reading data with csv.h and more data fields to enter in for option 2. Major change in class structure (one class vs 5 classes). Directory now is specific to a school system. Now can determine who is involved in a course, list out all courses without instructors that students are taking, print out all instructors and the courses they are teaching, pay all staff members, and display if person has permisson to e-mail based on list.

Options:
Same 3 from v1
4. Prompt user for a course, and will display Instructors and TAs teaching that course with students that are enrolled in that course.
5. Prints out all enrolled courses without instructors and all intrustors with courses they are teaching
6. Pays all staff. Instuctors are paid by courses time salary. Staff is paid by salary. TA is paid by hours times salary. No info is displayed.
7. Prompts name from user. The prompts user for a list of e-mails. Program will display which e-mails that named person can sent an e-mail to.

Note: If your csv file is badly formatted, the csv reader will not be able to read it and program will prompt an error
