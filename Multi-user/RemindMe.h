#ifndef REMINDME_H
#define REMINDME_H
#include <string>
#include <fstream>
#include <stdio.h>
using namespace std;

struct EachPart {
    string day,month,year;
    string assignment;
    string category;
};

struct NameList {
    string name;
    int count;
};

string currentDate();
void deadline(string time, EachPart list[], int size);
void createNewUser(const string name, string& counter);
void TheReminder(const string name, const string counter);
void NewReminder(const string name, const string counter);
bool is_number(const string& s);
bool is_name(const string &s);
bool foundUser(NameList a[], const string name, int size);
bool foundUser(const string name);
string FindCounter(const string name);
void EditNameCount(const string);
void CheckReminder(EachPart list[], int& size);
void PrintReminder(EachPart one, int& order);
void AddReminder(EachPart list[], int& size);
void DeleteReminder(EachPart list[], int& size);
void SortReminder(EachPart list[], int size);
void Settings();
void EditContent(EachPart list[], ofstream& file, int size);
bool Confirm(EachPart &one);
void EditVariables(EachPart &one);
bool ValidDates(string month, string day, string year);
void Merge(EachPart list[], int l, int m, int r, int o);
void MergeSort(EachPart list[], int left, int right, int order);


#endif
