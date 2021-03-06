#include <iostream>
#include <stdio.h>
#include <string>
#include <fstream>
#include <sstream>
#include <time.h>
#include "RemindMe.h"
using namespace std;

string n3 = "\n\n\n";

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

string currentDate(){
    time_t now = time(0);
    struct tm tstruct;
    char buf[7];
    tstruct = *localtime(&now);
    strftime(buf, 8, "%Y%m%d", &tstruct);
    return buf;
}

void deadline(string time, EachPart list[], int size){
    string date;
    int yeartoday = stoi(time.substr(0,4)), monthtoday = stoi(time.substr(4,2)), daytoday = stoi(time.substr(6));
    int year,month,day;
    cout << "Today is " << monthtoday << "/" << daytoday << "/" << yeartoday<<endl;
    cout << "The following assignments are past the deadline, if any:\n";
    for(int i = 0; i < size; i++){
        year = stoi(list[i].year);
        if(year < yeartoday){
            PrintReminder(list[i], dateorder);
            continue;
        }else if(year == yeartoday){
            month = stoi(list[i].month);
            if(month < monthtoday){
                PrintReminder(list[i], dateorder);
                continue;
            }else if(month == monthtoday){
                day = stoi(list[i].day);
                if(day < daytoday){
                    PrintReminder(list[i], dateorder);
                    continue;
                }
            }
        }
    }
    return;
}

bool is_number(const string& s){
    int i = 0;
    while(s[i]){
        if(!(isdigit(s[i]))) return false;
        i++;
    }
    return true;
}

bool ValidDates(string month, string day, string year){
    if(!(is_number(month) && is_number(day) && is_number(year))){
        return false;
    }
    int day1 = stoi(day), year1 = stoi(year), month1 = stoi(month);
    if(day1 < 0)
        return false;
    if(year1 < 0)
        return false;
    switch(month1){
        case 1: case 3: case 5:
        case 7: case 8: case 10:
        case 12:
            if(day1 > 31)
            return false;
            break;
        case 4: case 6:
        case 9: case 11:
            if(day1 > 30)
            return false;
            break;
        case 2:
            if(year1%4==0 && day1 > 29)
            return false;
            if(day1 > 28)
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
        << "\tMonth:" << one.month << "\tDay:" << one.day << "\tYear:" << one.year << "\n";
    getline(cin,ConfirmAnswer);
    if(ConfirmAnswer == "y")
    return true;
    else{
        return false;
    }
}

//Find the amount of times the name was used.
//Also edit the file so that the count is incremented.
string FindCounter(const string name){
    ifstream ListOfName("NameList.txt");
    NameList List[10];
    int size = 0;
    string nameOf;
    int count;
    while(ListOfName >> nameOf >> count){
        List[size].name = nameOf;
        List[size].count = count;
        size++;
    }
    int i = 0;
    while((List[i].name != name && i < size)){
        i++;
    }
    return to_string(List[i].count);
}

//Lied
bool foundUser(NameList a[], const string name, int size){
    int i = 0;
    while(i < size){
        if(a[i].name == name){
            return true;
        }
        i++;
    }
    return false;
}

bool foundUser(const string name){
    ifstream ListOfName("NameList.txt");
    NameList List[10];
    int size = 0;
    string nameOf;
    int count;
    while(ListOfName >> nameOf >> count){
        List[size].name = nameOf;
        List[size].count = count;
        size++;
    }
    return foundUser(List, name, size);
}

void EditNameCount(const string name){
    ifstream ListOfNames("NameList.txt");
    NameList List[10];
    int size = 0, count;
    string nameOf;
    while(ListOfNames >> nameOf >> count){
        List[size].name = nameOf;
        List[size].count = count;
        size++;
    }

    if(!foundUser(List, name, size)){
        List[size].name = name;
        List[size].count = 1;
        size++;
    } else {
        //Find location needed to be incremented.
        int counter = 0;
        while((List[counter].name != name) && (counter < size)){
            counter++;
        }
        List[counter].count++;
    }
    ListOfNames.close();
    
    //Rewrite
    ofstream NewCount("NameList.txt");
    int i = 0;
    while(i < size){
        NewCount << List[i].name << "\t" << List[i].count;
        i++;
    }
    NewCount.close();
    return;
}

void EditContent(EachPart list[], ofstream& file, int size){
    int i = 0;
    while(i < size){
        file << list[i].month << "\t" << list[i].day << "\t" << list[i].year 
        << "\t" << list[i].category << "\t" << list[i].assignment <<"\n";
        i++;
    }
}

void EditVariables(EachPart &one){
    string EditAnswer;
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
                getline(cin, one.month); getline(cin, one.day); getline(cin, one.year);
                while(!(ValidDates(one.month, one.day, one.year))){
                    cout << "You gave me a weird date." << one.month << one.day << one.year << "Do it again until it's right.\n";
              cout << "Enter your new date in these order: Month, day, year on EACH SEPARATE LINE\n";
              getline(cin, one.month); getline(cin, one.day); getline(cin, one.year);
            }
            break;
        case 2:{
            cout << "Enter your new category: \n";
            getline(cin, one.category);
            break;
        }
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
    }
}

void NewReminder(const string name, const string counter){
    cout << "Creating a new reminder file for " << name << ".\n";
    cout << "File name will be " << name << counter << ".txt\n\n\n\n\n";
    ofstream outfile(name+counter+".txt");
    outfile.close();
    EditNameCount(name);
    return;
}

void createNewUser(const string name, string& counter){
    if(foundUser(name+counter)){
        cout << "This user already exists. Are you sure you want to make a new file? (y/n)" << endl;
        getline(cin, answer);
        if(answer == "y"){
            counter = FindCounter(name);
            NewReminder(name, counter);
        }
        else if(answer == "n") {
            cout << "What is the number after your name in your file? (type 0 if no number) \n";
            getline(cin, counter);
            if(counter == "0"){
                counter = "";
            }
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
    return;
}

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
    string OneLine;
    while(getline(infile, OneLine)){
        istringstream TheLine(OneLine);
        getline(TheLine, TheList[size].month, '\t');
        getline(TheLine, TheList[size].day, '\t');
        getline(TheLine, TheList[size].year, '\t');
        getline(TheLine, TheList[size].category, '\t');
        getline(TheLine, TheList[size].assignment, '\t');
        size++;
    }
    cout << n3;
    string todaydate = currentDate();
    deadline(todaydate, TheList, size);

    int weirdanswer = 0;
    string ReminderAns;
    while(ReminderAns != "6"){
        cout << "\n\n\nWhat would you like to do, " << name << "?\n"
            << "1 = Check reminders.\n" << "2 = Add reminders.\n" 
            << "3 = Delete reminders.\n" << "4 = Sort reminders.\n" 
            << "5 = Date settings.\n" <<  "6 = Exit.\n";
        getline(cin, ReminderAns);
        if(!(is_number(ReminderAns))){
            ReminderAns = "7";
        }
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

void CheckReminder(EachPart list[], int& size){
    string checkAns;
    if(size == 0){
        cout << "You currently have no reminders! Would you like to add some?(y/n)\n";
        getline(cin, checkAns);
        if(checkAns == "y"){
            AddReminder(list, size);
        } else{
            return;
        }
    }

    cout << n3;
    int i = 0;
    while(i < size){
        PrintReminder(list[i], dateorder);
        i++;
    }
    return;
}

void PrintReminder(EachPart one, int& order){
    switch(order){
        case 1:{
            cout << one.month+"/"+one.day+"/"+one.year+"\t"+one.assignment+"\t"+one.category+"\n";
            break;
        }
        case 2:{
            cout << one.day+"/"+one.month+"/"+one.year+"\t"+one.assignment+"\t"+one.category+"\n";
            break;
        }
        case 3:{
            cout << one.year+"/"+one.month+"/"+one.day+"\t"+one.assignment+"\t"+one.category+"\n";
            break;
        }
        default: {
            cout << "How did you get here? Setting order to default: Month, Day, Year\n" << endl;
            order = 1;
            break;
        }
    }
    return;
}

void AddReminder(EachPart list[], int& size){
    EachPart New;
    cout << n3+"What is the name of this assignment?\n";
    getline(cin, New.assignment);
    cout << "What is the category of this assignment?\n";
    getline(cin, New.category);
    cout << "Month, day, year on EACH SEPARATE LINE\n";
    getline(cin, New.month); getline(cin, New.day); getline(cin, New.year);

    while(!(ValidDates(New.month, New.day, New.year))){
        cout << "You gave me a weird date." << New.month << "/"<<New.day << "/"<<New.year << "Do it again until it's right.\n";
        cout << "Enter your new date in these order: Month, day, year on EACH SEPARATE LINE\n";
        getline(cin, New.month); getline(cin, New.day); getline(cin, New.year);
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
        cout << n3+"There is nothing to delete. This function will stop";
        return;
    }
    string ItemToRemove;
    cout << n3+"Which reminder would you like to remove?\n";
    int i = 0;
    cout << "0.\tNot remove anything\n";
    while(i < size){
        cout << i+1 << ".\t";
        PrintReminder(list[i], dateorder);
        i++;
    }
    getline(cin, ItemToRemove);
    if(!(is_number(ItemToRemove))){
        cout << "Wrong input. Will not delete.";
        return;
    }
    int index = stoi(ItemToRemove);
    if(index == 0){
        cout << "Not removing anything\n";
        return;
    }
    for(int j = index-1; j < size-1; j++){
        list[j] = list[j+1];
    }
    size--;
    return;
}

void SortReminder(EachPart list[], int size){
    string SortAns;
    cout << n3+"How would you like to see the order of reminders?\n"
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
            break;
        }
    }
    return;
}

void MergeSort(EachPart list[], int left, int right, int order){
    if(left < right){
        int middle = (left + (right-1))/2;
        MergeSort(list, left, middle, order);
        MergeSort(list, middle+1, right, order);
        Merge(list, left, middle, right, order);
    }
    return;
}

void Merge(EachPart list[], int l, int m, int r, int o){
    int i,j,k;
    EachPart temp[20];
    i = l;
    k = l;
    j = m + 1;
    switch(o){
        //alphabetically
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
        //Chronologically
        case 2:{
            int left, right;
            while(i <= m && j <= r){
                left = stoi((list[i].year))*10000+stoi((list[i].month))*100+stoi((list[i].day));
                right = stoi((list[j].year))*10000+stoi((list[j].month))*100+stoi((list[j].day));
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
        //categorically
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
    return;
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
    return;
}
