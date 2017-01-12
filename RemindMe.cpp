#include <iostream>
#include <stdio.h>
#include <string>
#include <fstream>
#include "RemindMe.h"
using namespace std;

//
string FindCounter(string name){
    ifstream infile("NameList.txt"){

    }
}

//Create new user if not found in files.
void createNewUser(string name){
    if(foundUser(name)){
        char answer;
        cout << "This user already exists. Are you sure you want to make a new file? (y/n)" << endl;
        cin >> answer;
        if(answer == 'y'){
            string counter = FindCounter(name);
            ofstream outfile(name+counter+".txt");
            outfile << name << endl;
            outfile.close();
        }
        else if(answer == 'n') {
            cout << "Well, the program will continue on as the existed user's name.";
            return 0;
        }
        else{
            
        }
    }
    else{
        cout << "Creating a new reminder file for " << name << ".\n";
        ofstream infile(name+".txt");
        infile.close();
        return 0;
    }
}

bool foundUser(string name){
    ifstream infile(name+".txt");
    if(infile.is_open()){
        infile.close();
        return true;
    }
    else{
        return false;
    }
}

void TheReminder(string name){
    ifstream infile(name+".txt");
    int month, day, year;
    string category, assignment, duetime;
    while(infile >> month >> day >> year >> duetime >> category >> assignment){

    }

    infile.close();
}
