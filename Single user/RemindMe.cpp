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

/*
 * 0 = none
 * 1 = alphabeticaly
 * 2 = chronologically
 * 3 = category
 */
 int reminderorder = 0;

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

bool Confirm(EachPart &one){
    string ConfirmAnswer;
    cout << "Are you satisfied with the following: (y/n)\nAssignment:"
        << one.assignment << "\tCategory:" << one.category 
        << "\tMonth:" << one.month << "\tDay:" << one.day << "\tYear:20" << one.year << "\n";
    getline(cin,ConfirmAnswer);
    if(ConfirmAnswer == "y")
    return true;
    else{
        return false;
    }
}

//
void EditContent(EachPart list[], ofstream& file, int size){
    int i = 0;
    while(i < size){
        file << list[i].month << "\t" << list[i].day << "\t" << list[i].year 
        << "\t" << list[i].category << "\t" << list[i].assignment <<"\n";
        i++;
    }
}

//Done
void EditVariables(EachPart &one){
    string EditAnswer,month,day,year;
    while(EditAnswer != "4"){
    cout << "Which part would you like to edit?\n"
        << "1. Date\n"
        << "2. Category\n"
        << "3. Assignment details\n"
        << "4. Nothing. I'm done.\n";
    getline(cin, EditAnswer);
    switch(stoi(EditAnswer)){
        case 1:
            cout << "Enter your new date in these order: Month, day, year on EACH SEPARATE LINE\n";
            getline(cin, month);
            getline(cin, day);
            getline(cin, year);
            one.month = stoi(month);
            one.day = stoi(day);
            one.year = stoi(year);
            one.year = (one.year%1000)%100;
            while(!(ValidDates(one.month, one.day, one.year))){
              cout << "You gave me a weird date." << one.month << one.day << one.year << "Do it again until it's right.\n";
              cout << "Enter your new date in these order: Month, day, year on EACH SEPARATE LINE\n";
              getline(cin, month);
              getline(cin, day);
              getline(cin, year);
              one.month = stoi(month);
              one.day = stoi(day);
              one.year = stoi(year);
              one.year = (one.year%1000)%100;
            }
            break;
        case 2:
            cout << "Enter your new category: \n";
            getline(cin, one.category);
        break;
        case 3:{
            cout << "Edit your assignment details\n";
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
    if(Confirm(one)){
        return;
    }
    }
}

//Done
void TheReminder(const string name, const string counter){
    string ReminderAns1;
    cout << "Would you like to review or edit your reminders? (y/n)" << endl;
    getline(cin,ReminderAns1);
	if(ReminderAns1 == "n"){
		cout << "WHY DID YOU RUN THIS PROGRAM ANYWAYS.";
		return;
    } else if(ReminderAns1 != "y"){
		perror("Invalid answer. Program will exit.");
		return;
	}
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

    string ReminderAns;
    while(ReminderAns != "6"){
        cout << "\n\n\nWhat would you like to do, " << name << "?\n"
            << "1 = Check reminders.\n" << "2 = Add reminders.\n" 
            << "3 = Delete reminders.\n" << "4 = Sort reminders.\n" 
            << "5 = Date settings.\n" <<  "6 = Exit.\n";
        getline(cin, ReminderAns);
        
        switch(stoi(ReminderAns)){
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
                    ReminderAns = "6";
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
void CheckReminder(EachPart list[], int& size){
    if(size == 0){
        cout << "You currently have no reminders! Would you like to add some?(y/n)\n";
        getline(cin, answer);
        if(answer == "y"){
            AddReminder(list, size);
        } else{
            return;
        }
    }

    cout << "\n\n";
    int i = 0;
    while(i < size){
        PrintReminder(list[i], dateorder);
        i++;
    }
    cout << "\n\n\n";
}

//Done
void PrintReminder(EachPart one, int& order){
    switch(order){
        case 1:{
            cout << one.assignment << "\t" << one.category << "\t" << one.month << "/" << one.day << "/" << one.year << endl;
            break;
        }
        case 2:{
            cout << one.assignment << "\t" << one.category << "\t" << one.day << "/" << one.month << "/" << one.year << endl;
            break;
        }
        case 3:{
            cout << one.assignment << "\t" << one.category << "\t" << one.year << "/" << one.month << "/" << one.day << endl;
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
void AddReminder(EachPart list[], int& size){
    EachPart New;
    string month1,day1,year1;
    cout << "\n\n\nWhat is the name of this assignment?\n";
    getline(cin, New.assignment);
    cout << "What is the category of this assignment?\n";
    getline(cin, New.category);
    cout << "Month, day, year on EACH SEPARATE LINE\n";
    getline(cin, month1);
    getline(cin, day1);
    getline(cin, year1);
    New.month = stoi(month1);
    New.day = stoi(day1);
    New.year = stoi(year1);
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
            cout << "Make up your mind!! I'm not putting this.\n";
            return;
        }
        EditVariables(New);
        correctioncounter++;
    }

    list[size] = New;
    size++;
    return;
}

void DeleteReminder(EachPart list[], int& size){
    if(size == 0){
        cout << "There is nothing to delete. This function will stop";
        return;
    }
    cout << "Which reminder would you like to remove?\n";
    int i = 0;
    cout << "0. Not remove anything\n";
    while(i < size){
        cout << i+1 << ".\t";
        PrintReminder(list[i], dateorder);
        i++;
    }
    int ItemToRemove = 0;
    cin >> ItemToRemove;
    if(ItemToRemove == 0){
        cout << "Not removing anything\n";
        return;
    }
    for(int j = ItemToRemove-1; j < size-1; j++){
        list[j] = list[j+1];
    }
    size--;
}

void SortReminder(EachPart list[], int size){
    string SortAns;
    cout << "How would you like to see the order of reminders?\n"
        << "0 = I don't care\n"
        << "1 = Alphabetically\n"
        << "2 = Chronologically\n"
        << "3 = Categorically\n";
    getline(cin, SortAns);
    if(!is_number(SortAns)){
        cout << "Weird input there. Will cancel this instruction.\n";
        return;
    }
    switch(stoi(SortAns)){
        case 0:{
            return;
            break;
        }
        case 1:{
            MergeSort(list, 0, size-1, 1);
            break;
        }
        case 2:{
            MergeSort(list, 0, size-1, 2);
            break;
        }
        case 3:{
            MergeSort(list, 0, size-1, 3);
            break;
        }
        default:{
            cout << "Not a valid answer. Will cancel this instruction.\n";
            return;
            break;
        }
    }
}

void MergeSort(EachPart list[], int left, int right, int order){
    if(left < right){
        int middle = left + (right-1)/2;
        MergeSort(list, left, middle, order);
        MergeSort(list, middle+1, right, order);
        Merge(list, left, middle, right, order);
    }
}

void Merge(EachPart list[], int l, int m, int r, int o){
    int i,j,k;
    EachPart temp[20];
    i = l;
    k = l;
    j = m + 1;
    switch(o){
        //alphabetically; done
        case 1:{
            char left, right;
            while(i <= m && j <= r){
                left = (list[i].assignment)[0];
                right = (list[j].assignment)[0];
                if(left < right){
                    temp[k] = list[i];
                    k++;
                    i++;
                } else{
                    temp[k] = list[j];
                    k++;
                    j++;
                }
            }
            break;
        }
        //Chronologically; not done
        case 2:{
            int left, right;
            string stringleft, stringright;
            cout << "I'm here\n";
            while(i <= m && j <= r){
                stringleft = (list[i].year)+(list[i].month)+(list[i].day);
                stringright = (list[j].year)+(list[j].month)+(list[j].day);
                cout << "I'm here\n" << stringleft << endl << stringright<<endl;
                left = stoi(stringleft);
                right = stoi(stringright);
                cout << "I'm here\n";
                if(left < right){
                    temp[k] = list[i];
                    k++;
                    i++;
                }else{
                    temp[k] = list[j];
                    k++;
                    j++;
                }
            }
            break;
        }
        //categorically; done
        case 3:{
            char left, right;
            while(i <= m && j <= r){
                left = (list[i].category)[0];
                right =(list[j].category)[0];
                if(left < right){
                    temp[k] = list[i];
                    k++;
                    i++;
                }
                else{
                    temp[k] = list[j];
                    k++;
                    j++;
                }
            }
            break;
        }
        default:{
            //It should never get here..?
            cout << "How are you here?\n";
            break;
        }
    }
    while(i <= m){
        temp[k] = list[i];
        k++;
        i++;
    }
    while(j <= r){
        temp[k] = list[j];
        k++;
        j++;
    }
    for(i = l; i < k; i++){
        list[i] = temp[i];
    }
}

void Settings(){
    string SettingAns;
    cout << "How would you like to see the order of the dates?\n"
        << "1 = month, day, year\n"
        << "2 = day, month, year\n"
        << "3 = year, month, day\n";
    getline(cin, SettingAns);
    if(is_number(SettingAns)){
        dateorder = stoi(SettingAns);
    }else{
        cout << "You inputted a weird number/non-number. Will set to default (m,d,y)\n";
        dateorder = 1;
    }
}
