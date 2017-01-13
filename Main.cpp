/*
 * RemindMe.cpp 
 * Andy Lim
 * Started January 10, 2017
 */

#include <iostream>
#include <string>
#include <stdio.h>
#include "RemindMe.h"
using namespace std;

int main(int argc, const char**argv){
	string name, answer, counter = "";

	//Depends on whether the user puts the name/counter or not in the initial input.
	if(argc == 3){
		name = argv[1];
		counter = argv[2];
	}
	else if(argc == 2){
		name = argv[1];
	}
	else if(argc == 1){
		cout << "Are you a new user? (y/n)" << endl;
		getline(cin, answer);
		cout << "What is your name?" <<endl;
		getline(cin, name);
		cout << "Hello, " << name << endl;
		if(answer == "y"){
			createNewUser(name, counter);
		} else if(answer == "n"){
			string counter;
			cout << "What is the number after your name in your reminder file? (press Enter if no number) \n";
			getline(cin, counter);
			if(!(is_number(counter))){
				cout << "It seems like you did not put a correct input. Counter will be defaulted to nothing\n";
				counter = "";
			}
		} else{
			perror("Invalid answer. Program will exit.");
			return 0;
		}
	}
	else{
		perror("There is an invalid number of inputs");
		return 0;
	}

	//User did not want to cooperate so this program wants to leave!
	if(counter == "0" || !(is_number(counter))){
		perror("There was something wrong with your inputs along the way. Program will exit");
		return 0;
	}

	//I don't think names have numbers in them?
	if(!is_name(name)){
		perror("Is that your real name bruh?");
		return 0;
	}

	//Checks if the file name doesn't exists after ALL THAT CHECKING;
	if(!foundUser(name+counter)){
		cout << "It seems like this name does not exist in the file. Would you like to make a new file with the name, " << name << counter << "? (y/n)\n";
		cin >> answer;
		if(answer == "y"){
			NewReminder(name, counter);
		} else{
			cout << "Well then. The program will now exit.";
			return 0;
		}	
	}

	TheReminder(name, counter);
	return 0;
}
