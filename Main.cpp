#include <iostream>
#include <string>
#include <stdio.h>
#include "RemindMe.h"
using namespace std;

int main(int argc, const char**argv){
	string name;
	string answer;
	if(argc == 2)
		name = argv[1];
	else if(argc == 1){
		cout << "Are you a new user? (y/n)" << endl;
		getline(cin, answer);
		cout << "What is your name?" <<endl;
		getline(cin, name);
		cout << "Hello, " << name << endl;
		if(answer=="y"){
			createNewUser(name);
		} else if(answer=="n"){
			perror("Invalid answer. Program will exit.");
			return 0;
		}
	}
	else{
		perror("There is an invalid number of inputs");
		return 0;
	}
	if(foundUser(name)){
		cout << "Would you like to review your reminders? (y/n)" << endl;
		getline(cin, answer);
		if(answer == "y"){
			TheReminder(name);
		} else if(answer == "n"){
			cout << "Alright; program will now exit.";
			return 0;
		} else{
			perror("Invalid answer. Program will exit.");
			return 0;
		}
	}
	else{
		cout << "It seems like this name does not exist in the file. 
				Would you like to make a new file with the name, " << name << "?" << endl;
		cin >> answer;
		if(answer == "y"){
			createNewUser(name);
		} else{
			cout << "Well then. The program will now exit.";
			return 0;
		}
	}
	return 0;
}
