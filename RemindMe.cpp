#include <iostream>
#include <stdio.h>
#include <string>
#include <fstream>
#include "RemindMe.h"
using namespace std;

//Because I ask for answers too much
string answer;

/*
 * 1 = month, day, year (default)
 * 2 = day, month, year
 * 3 = year, month, day
 */
int dateorder = 1;

//Done
bool is_name(const string &s){
    int i= 0;
    while(s[i]){
        if(!(isalpha(s[i]))) return false;
        i++;
    }
    return true;
}

//Done
bool is_number(const string& s){
    int i = 0;
    while(s[i]){
        if(!(isdigit(s[i]))) return false;
        i++;
    }
    return true;
}

//Done
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

//Done
void EditNameCount(const string name){
    ifstream Names("NameList.txt");
    NameList List[10];
    int size = 0;
    while(Names >> names >> count){
        List[size].name = names;
        List[size].count = count;
        size++;
    }

    if(!foundUser(name)){
        List[count].name = name;
        List[size].count = 1;
    } else {
        //Find location needed to be incremented.
        int counter = 0;
        while((List[counter].name != name) && (counter < size)){
            counter++;
        }
        List[counter].count++;
    }
    Names.close();
    
    //Rewrite
    ofstream NewCount("NameList.txt");
    int i = 0;
    while(i < size){
        NewCount << List[i].name << List[i].count;
        i++;
    }
    NewCount.close();
    return;
}

void NewReminder(const string name, const string counter){
    cout << "Creating a new reminder file for " << name << ".\n";
    cout << "File name will be " << name << counter << ".txt\n\n\n\n\n";
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
//Done I hope
void createNewUser(const string name, string& counter){
    if(foundUser(name+counter)){
        cout << "This user already exists. Are you sure you want to make a new file? (y/n)" << endl;
        getline(cin, answer);
        if(answer == "y"){
            counter = FindCounter(name);
            NewReminder(name, counter);
        }
        else if(answer == "n") {
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

//Done
void TheReminder(const string name, const string counter){
    cout << "Would you like to review or edit your reminders? (y/n)" << endl;
    getline(cin,answer);
	if(answer == "n"){
		cout << "WHY DID YOU RUN THIS PROGRAM ANYWAYS.";
		return;
    } else if(answer != "y"){
		perror("Invalid answer. Program will exit.");
		return;
	}

    cout << "\n\n\n\n\n\n\n\n\nNow opening the file named: " << name<<counter<<".txt\n";
    ifstream infile(name+counter+".txt");
    EachPart TheList[20];
    int size = 0;
    int month, day, year;
    string category, assignment;
    while(infile >> month >> day >> year >> category >> assignment){
        TheList[size].month = month;
        TheList[size].day = day;
        TheList[size].year = year;
        TheList[size].category = category;
        TheList[size].assignment = assignment;
        size++;
    }

    int weirdanswer = 0;

    while(answer != "6"){
        cout << "What would you like to do, " << name << "?\n"
            << "1 = Check reminders.\n" << "2 = Add reminders.\n" 
            << "3 = Delete reminders.\n" << "4 = Sort reminders.\n" 
            << "5 = Date settings.\n" <<  "6 = Exit.\n";
        getline(cin, answer);
        
        switch(stoi(answer)){
            case 1:{
                CheckReminder(TheList, size);
                weirdanswer = 0;
                break;
            }
            case 2:{
                AddReminder(TheList, size);
                weirdanswer = 0;
                break;
            }
            case 3:{
                DeleteReminder(TheList, size);
                weirdanswer = 0;
                break;
            }
            case 4:{
                SortReminder(TheList, size);
                weirdanswer = 0;
                break;
            }
            case 5:{
                Settings();
                break;
            }
            case 6:{
                cout << "Program will now exit.\n";
                break;
            }
            default:{
                weirdanswer++;
                if(weirdanswer == 3){
                    cout << "You gave me too much weird answers. I'm gonna exit.\n";
                    answer = "6";
                    break;
                }
                cout << "You gave a weird answer. Asking you the question again.\n";
                break;
            }
    }

    }
    infile.close();

    //Save the content!
    ofstream outfile(name+counter+".txt");
    EditContent(TheList, outfile, size);
    outfile.close();
    return;
}

//Done
void CheckReminder(EachPart list[], int size){
    if(size == 0){
        cout << "You currently have no reminders! Would you like to add some?(y/n)\n";
        getline(cin, answer);
        if(answer == "y"){
            AddReminder(list, 0);
        } else{
            return;
        }
    }

    int i = 0;
    while(i < size){
        PrintReminder(list[i], dateorder);
        i++;
    }
}

//Done
void PrintReminder(EachPart one, int& order){
    switch(order){
        case 1:{
            cout << one.assignment << "\t" << one.category << "\t" << one.month << one.day << one.year << endl;
            break;
        }
        case 2:{
            cout << one.assignment << "\t" << one.category << "\t" << one.day << one.month << one.year << endl;
            break;
        }
        case 3:{
            cout << one.assignment << "\t" << one.category << "\t" << one.year << one.month << one.year << endl;
            break;
        }
        default: {
            cout << "How did you get here? Setting order to default: Month, Day, Year\n" << endl;
            order = 1;
            break;
        }
    }
}

//I think I'm done
void AddReminder(EachPart list[], int size){
    EachPart New;
    cout << "What is the name of this assignment?\n";
    getline(cin, New.assignment);
    cout << "What is the category of this assignment?\n";
    getline(cin, New.category);
    cout << "Month, day, year on EACH SEPARATE LINE\n";
    cin >> New.month;
    cin >> New.day;
    cin >> New.year;
    New.year = (New.year%1000)%100; //Let's just hope no one uses this in 22nd century

    while(!(ValidDates(New.month, New.day, New.year))){
        cout << "You gave me a weird date." << New.month << New.day << New.year << ".\nWould you like to edit?(y/n)\n";
        getline(cin, answer);
        if(answer == "y"){
            EditVariables(New);
        }
    }

    //If user is a girl and takes millions of thoughts to make a correct input. Will not accept more than 3 corrections.
    int correctioncounter = 0;
    while(!(Confirm(New))){
        if(correctioncounter>3){
            cout << "Make up your mind!! I'm not putting this.\n"
            return;
        }
        EditVariables(New);
        correctioncounter++;
    }

    list[size] = New;
    size++;
    return;
}

//Done
bool ValidDates(int month, int day, int year){
    if(day < 0)
        return false;
    if(year < 0)
        return false;
    switch(month){
        case 1: case 3: case 5:
        case 7: case 8: case 10:
        case 12:
            if(day > 31)
            return false;
            break;
        case 4: case 6:
        case 9: case 11:
            if(day > 30)
            return false;
            break;
        case 2:
            if(year%4==0 && day > 29)
            return false;
            if(day > 28)
            return false;
            break;
        default:
            cout<<"What month is this??????\n";
            return false;
            break;
    }
    return true;
}

//
void EditContent(EachPart list[], ofstream& file, int size){
    int i = 0;
    while(i < size){
        file << list[i].month << list[i].day << list[i].year << list[i].category << list[i].assignment;
        i++;
    }
}

void SortReminder(EachPart list[], int size){

}

//Done
void EditVariables(EachPart one){
    while(answer != "4"){
    cout << "Which part would you like to edit?"
        << "1. Date\n"
        << "2. Category\n"
        << "3. Assignment details\n"
        << "4. Nothing. I changed my mind.\n";
    getline(cin, answer);
    switch(stoi(answer)){
        case 1:
            cout << "Enter your new date in these order: Month, day, year on EACH SEPARATE LINE\n";
            cin >> one.month >> one.day >> one.year;
            while(!(ValidDates(one.month, one.day, one.year))){
              cout << "You gave me a weird date." << one.month << one.day << one.year << "Do it again until it's right.\n";
              cout << "Enter your new date in these order: Month, day, year on EACH SEPARATE LINE\n";
              cin >> one.month >> one.day >> one.year;
            }
            break;
        case 2:
            cout << "Enter your new category: \n";
            getline(cin, one.category);
        break;
        case 3:{
            cout << "Edit your assignment details\n"
            getline(cin, one.assignment);
            break;
        }
        case 4:
        return;
        break;
        default:
            cout << "Wrong input. Asking again.\n";
        break;
    }
    }
}

void DeleteReminder(EachPart list[], int size){
    size--;
}

bool Confirm(EachPart one){
    cout << "Are you satisfied with the following: (y/n)\nAssignment:"
        << one.assignment << "\tCategory:" << one.category 
        << "\tMonth:" << one.month << "\tDay:" << one.day << "\tYear:20" << one.year << endl;
    getline(cin,answer);
    if(answer != "y")
    return false;
}

void Settings(){
    cout << "How would you like to see the order of the dates?"
        << "1 = month, day, year\n"
        << "2 = day, month, year\n"
        << "3 = year, month, day\n";
    getline(cin, answer);
    if(is_number(answer)){
        dateorder = stoi(answer);
    }else{
        cout << "You inputted a weird number/non-number. Will set to default (m,d,y)\n";
        dateorder = 1;
    }
}
