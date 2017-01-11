#include <iostream>
#include <stdio.h>
#include <string>
#include <fstream>
#include "RemindMe.h"
using namespace std;

void createNewUser(string name){
    if(foundUser(name)){
        char answer;
        cout << "This user already exists. Are you sure you want to make a new file? (y/n)" << endl;
        cin >> answer;
        if(answer == 'y'){
            string counter;
            ifstream infile(name+".txt");
            infile >> counter >> counter;
            ofstream outfile(name+counter+".txt");
            outfile << name << endl;
            infile.close();
            outfile.close();
        }
        else if(answer == 'n') {
            cout << "Well";
        }
    }
    else{
        ofstream infile(name+".txt");
        infile << name << " 1" << endl;
        infile.close();
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
