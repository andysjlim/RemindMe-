#ifndef REMINDME_H
#define REMINDME_H
#include <string>
using namespace std;
void createNewUser(string name);
bool foundUser(string name);
void TheReminder(string name);
void NewReminder();
string FindCounter(string name);

struct EachPart {
    int counter;
    int day,month,year;
    string assignment;
    string category;
};

#endif
