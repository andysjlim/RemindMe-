#include <iostream>
#include <string>
#include <stdio.h>
#include "RemindMe.h"
using namespace std;

int main(int argc, const char**argv){
	string name;
	char answer;
	if(argc == 2)
		name = argv[1];
	if(argc == 1){
		cout << "Are you a new user? (y\n)" << endl;
		getline(cin, answer);
		answer = tolower(answer);
		cout << "What is your name?" << endl;
		getline(cin, name);
		if(answer == 'y'){
			createNewUser(name);
		} else if(answer == 'n'){
			break;
		} else{
			perror("Invalid answer. Program will exit.");
			return 0;
		}
	}

	cout << "Hello, " << name << endl;
	if(foundUser(name)){
		cout << "Welcome. Would you like to check your reminders?" << endl;
		getline(cin, answer);
		answer = tolower(answer);
			if(answer == 'y'){
				
			} else if(answer == 'n'){
			cout << "Alright; program will now exit.";
			return 0;
		}
	}
	else{
		cout << "It seems like this name does not exist in the file. Would you like to make a new file with the name, " << name << "?" << endl;
		getline(cin, answer);
		if(answer == 'y'){
			createNewUser(name);
		}
	}
	
	perror("There is an invalid number of inputs");
	return 0;
}
