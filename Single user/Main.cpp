/*
 * RemindMe!
 * Andy Lim
 * Started January 10, 2017
 */

#include <iostream>
#include <string>
#include <stdio.h>
#include "RemindMe.h"
using namespace std;

int main(int argc, const char**argv){
	//Depends on whether the user puts the name/counter or not in the initial input.
	if(argc > 1){
		perror("No need to have any arguments included. Program will exit.");
		return 0;
	}
	TheReminder();
	return 0;
}
