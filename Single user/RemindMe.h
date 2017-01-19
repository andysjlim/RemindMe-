#ifndef REMINDME_H
#define REMINDME_H
#include <string>
#include <fstream>
#include <stdio.h>
using namespace std;

struct EachPart {
    string day,month,year;
    string assignment, category;
};

void TheReminder(const string name, const string counter);
bool is_number(const string& s);
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
