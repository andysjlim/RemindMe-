#include <iostream>
#include <stdio.h>
#include <string>
#include <fstream>
using namespace std;

void createNewUser(string name){
    ofstream file;
    file.open(name+".txt");
    file << name << endl;
    file.close();
}

bool foundUser(string name){

}
