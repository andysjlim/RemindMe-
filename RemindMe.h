#ifndef REMINDME_H
#define REMINDME_H
#include <string>
using namespace std;
void createNewUser(const string name, string& counter);
void TheReminder(const string name, const string counter);
void NewReminder(const string name, const string counter);
bool is_number(const string& s);
bool foundUser(const string name);
string FindCounter(const string name);
void EditNameCount(const string);

struct EachPart {
    int day,month,year;
    string assignment, category;
};

#endif
