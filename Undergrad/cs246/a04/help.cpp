// Instructions for binary setal calculator
#include <iostream>
#include "help.h"
using namespace std;

void help ()
{
    cout << "Commands for set calculator:\n";
    cout << "d  Declare a set (to be empty)\n";
    cout << "s  Declare a set (to be a singleton)\n";
    cout << "b  Declare a set (build with members)\n";
    cout << "=  Assign one set to another\n";
    cout << "+  Assign union of two sets to another\n";
    cout << "-  Assign subtraction of two sets to another\n";
    cout << "*  Assign intersection of two sets to another\n";
    cout << "o  Output a set\n";
    cout << "v  Toggle verbal or not verbal\n";
    cout << "p  Print a string\n";
    cout << "q  Quit\n";
}
