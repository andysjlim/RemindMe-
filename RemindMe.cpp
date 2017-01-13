#include <iostream>
#include <stdio.h>
#include <string>
#include <fstream>
#include "RemindMe.h"
using namespace std;

//Because I ask for answers too much
char answer;

bool is_name(const string &s){
    int i= 0;
    while(s[i]){
        if(!(isalpha(s[i]))) return false;
    }
    return true;
}

bool is_number(const string& s)
{
    int i = 0;
    while(s[i]){
        if(!(isdigit(s[i]))) return false;
    }
    return true;
}

bool foundUser(const string name){
    ifstream infile(name+".txt");
    if(infile.is_open()){
        infile.close();
        return true;
    }
    else{
        return false;
    }
}

void EditNameCount(const string name){

}

void NewReminder(const string name, const string counter){
    cout << "Creating a new reminder file for " << name << ".\n";
    cout << "File name will be " << name << counter << ".txt\n";
    ofstream outfile(name+counter+".txt");
    outfile.close();
    EditNameCount(name);
}

//Find the amount of times the name was used.
//Also edit the file so that the count is incremented.
string FindCounter(const string name){
    if(name == ""){
    ifstream infile("NameList.txt");
    infile.close();
    }
    return "";
}

//Create new user if not found in files.
void createNewUser(const string name, string& counter){
    if(foundUser(name+counter)){
        cout << "This user already exists. Are you sure you want to make a new file? (y/n)" << endl;
        cin >> answer;
        if(answer == 'y'){
            counter = FindCounter(name);
            NewReminder(name, counter);
        }
        else if(answer == 'n') {
            cout << "What is the number after your name in your file? (press Enter if no number) \n";
            getline(cin, counter);
            if(is_number(counter)){
                return;
            } else{
                perror("This user does not exist or you have inputted an invalid input. Program will exit");
                counter = "0";
                return;
            }
        }
        else{
            perror("Invalid input");
            counter = "0";
            return;
        }
    }
    else{
        NewReminder(name, counter);
        return;
    }
}

void TheReminder(const string name, const string counter){
    cout << "Would you like to review or edit your reminders? (y/n)" << endl;
	cin >> answer;
	if(answer == 'n'){
		cout << "WHY DID YOU RUN THIS PROGRAM ANYWAYS.";
		return 0;
    } else if(answer != 'y'){
		perror("Invalid answer. Program will exit.");
		return 0;
	}

    cout << "Now opening the file named: " << name<<counter<<".txt\n";
    ifstream infile(name+counter+".txt");
    EachPart[] TheList = new EachPart[20];
    int i = 0;
    int month, day, year;
    string category, assignment;
    while(infile >> month >> day >> year >> category >> assignment){
        TheList[i].month = month;
        TheList[i].day = day;
        TheList[i].year = year;
        TheList[i].category = category;
        TheList[i].assignment = assignment;
        i++;
    }

    infile.close();
    return;
}
