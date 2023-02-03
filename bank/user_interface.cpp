/*****************************************************************
//
//  NAME:        Nathanial Getchel
//
//  HOMEWORK:    Project 2
//
//  CLASS:       ICS 212
//
//  INSTRUCTOR:  Ravi Narayan
//
//  DATE:        November 15, 2022
//
//  FILE:        user_interface.cpp
//
//  DESCRIPTION:
//   This file contains the code for the user interface of a
//   banking software.
//
//  REFERENCES:
//   
//
****************************************************************/

#include <iostream>
#include <cstring>
#include "llist.h"

using namespace std;

void getaddress (char [], int);

/*****************************************************************
//
//  Function name: main
//
//  DESCRIPTION:   This function starts the program and calls the
//                 functions needed to complete the user's request.
//
//  Parameters:    argc (int) : The number of elements in argv
//                 argv (char*[]) : An array of arguments passed
//                                  to the program.
//
//  Return values:  0 : default return value for main.
//
****************************************************************/

int main(int argc, char* argv[])
{
    char selection[16];
    char address[60];
    char name[30];
    int accountno;
    int maxLen = 60;
    int quit = 0;
    int valid = 0;
    
    #ifdef DEBUGMODE
        cout << "\n*****DEBUG*****\n";
        cout << "Debug mode has been activated\n";
        cout << "*****DEBUG*****\n";
    #endif
    
    llist bankList;
    
    cout << "\nWelcome to Bank-o-Matic 3001!";
    do
    {
        cout << "\nPlease choose an option from the list below by typing the name of the operation you wish to run.\n";
        cout << "add: create a new customer record\n";
        cout << "printall: display all customer records\n";
        cout << "find: display a single customer record\n";
        cout << "delete: remove a single customer record\n";
        cout << "quit: exit the program\n";
    
        cin.getline(selection, 16);
        
        if (strncmp("add", selection, strlen(selection)) == 0)
        {
            valid = 1;
            cout << "Please enter your account number:\n";
            cin >> accountno;
            while (cin.fail() || accountno <= 0)
            {
                cin.clear();
                cin.ignore(20, '\n');
                cout << "\nYou must enter a valid account number.\n";
                cout << "Please enter your account number:\n";
                cin >> accountno;
            }
            cin.ignore(20, '\n');
            cout << "Please enter your name:\n";
            cin.getline(name, 30);

            getaddress(address, maxLen);
            bankList.addRecord(accountno, name, address);
            strcpy(name, "\0");
            cout << "\n";
        }
        else if (strncmp("printall", selection, strlen(selection)) == 0)
        {
            bankList.printAllRecords();
            valid = 1;
        }
        else if (strncmp("find", selection, strlen(selection)) == 0)
        {
            valid = 1;
            cout << "Please enter your account number:\n";
            cin >> accountno;
            while (cin.fail() || accountno <= 0)
            {
                cin.clear();
                cin.ignore(20, '\n');
                cout << "\nYou must enter a valid account number.\n";
                cout << "Please enter your account number:\n";
                cin >> accountno;
            }
            cin.ignore(20, '\n');
            if (bankList.findRecord(accountno) == -1)
            {
                cout << "No such record exists.\n\n";
            }
        }
        else if (strncmp("delete", selection, strlen(selection)) == 0)
        {
            valid = 1;
            cout << "Please enter your account number:\n";
            cin >> accountno;
            while (cin.fail() || accountno <= 0)
            {
                cin.clear();
                cin.ignore(20, '\n');
                cout << "\nYou must enter a valid account number.\n";
                cout << "Please enter your account number:\n";
                cin >> accountno;
            }
            cin.ignore(20, '\n');
            if (bankList.deleteRecord(accountno) == -1)
            {
                #ifdef DEBUGMODE
                    cout << "\n";
                #endif
                cout << "No such record exists.\n";
            }
            cout << "\n";
        }
        else if (strncmp("quit", selection, strlen(selection)) == 0)
        {
            valid = 1;
            quit = 1;
        }
        else
        {
            valid = 0;
            cout << "Error: invalid. Please enter a valid input.\n";
        }
        
        if (quit ==1)
        {
            cout << "\nThank you for using Bank-o-Matic 3001. Goodbye!\n";
        }
        strcpy(selection, "\0");
    }
    while ((valid == 0) || (quit == 0));    
}

/*****************************************************************
//
//  Function name: getaddress
//
//  DESCRIPTION:   This function collects address information from
//                 the user.
//
//  Parameters:    address (char[]) : Pointer to the address string
//                 maxLen (int) : The max allowed length of the
//                                address string
//
//  Return values:  none
//
****************************************************************/

void getaddress (char address[], int maxLen)
{
    char input[200] = "\0";
    char temp[60] = "\0";
    int done = 0;
    
    #ifdef DEBUGMODE
        cout << "\n*****DEBUG*****\n";
        cout << "function called: getaddress\nparameters:\n";
        cout << "address:\n" << address << "\nmaxLen: " << maxLen << endl;
        cout << "*****DEBUG*****\n";
    #endif
    
    strcpy(address, "\0");
    
    cout << "\nPlease enter your address. When you have finished typing, press # and then <ENTER>.\n";
    
    do
    {
        cin.getline(temp, maxLen);
        strcat(input, temp);
        if (input[strlen(input) - 1] == 35)
        {
            done = 1;
        }
        if (done == 0)
        {
            strcat(input, "\n");
        }
    }
    while (done == 0);
    
    strcpy(address, input);
}