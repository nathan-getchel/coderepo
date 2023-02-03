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
//  FILE:        llist.cpp
//
//  DESCRIPTION:
//   This file contains the member functions of the llist class
//
//  REFERENCES:
//   
//
****************************************************************/

#include "llist.h"
#include <fstream>
#include <cstring>
#include <cstdlib>
#include <iostream>

using namespace std;

/*****************************************************************
//
//  Function name: llist
//
//  DESCRIPTION:   Constructor for the linked list
//
//  Parameters:    None
//
//  Return values: None
//
****************************************************************/
llist::llist()
{
    #ifdef DEBUGMODE
        cout << "\n*****DEBUG*****\n";
        cout << "function called: llist (Constructor)\n";
        cout << "*****DEBUG*****\n";
    #endif
    strcpy(this->filename, "bankList.txt");
    this->start = NULL;
    readfile();
}

/*****************************************************************
//
//  Function name: llist
//
//  DESCRIPTION:   Parameterized constructor for the linked list
//
//  Parameters:    filename (char[]) : NAme of the file to be read
//
//  Return values: None
//
****************************************************************/
llist::llist(char filename[])
{
    #ifdef DEBUGMODE
        cout << "\n*****DEBUG*****\n";
        cout << "function called: llist (Constructor)\nparameters\n";
        cout << "filename: " << filename << endl;
        cout << "*****DEBUG*****\n";
    #endif
    strcpy(this->filename, filename);
    this->start = NULL;
    readfile();
}

/*****************************************************************
//
//  Function name: ~llist
//
//  DESCRIPTION:   Destructor for the linked list
//
//  Parameters:    None
//
//  Return values: None
//
****************************************************************/
llist::~llist()
{
    #ifdef DEBUGMODE
        cout << "\n*****DEBUG*****\n";
        cout << "function called: ~llist (Destructor)\n";
        cout << "*****DEBUG*****\n";
    #endif
    writefile();
    cleanup();
}

/*****************************************************************
//
//  Function name: addRecord
//
//  DESCRIPTION:   This function adds a new record to the linked list
//
//  Parameters:    accountno (int): The new account number
//                 name (char []): The new name
//                 address (char []): The new address
//
//  Return values: None
//
****************************************************************/
void llist::addRecord(int accountno, char name[],char address[])
{
    struct record* newRec;
    struct record* temp;
    struct record* follows;
    
    #ifdef DEBUGMODE
        cout << "\n*****DEBUG*****\n";
        cout << "function called: addRecord\nparameters:\n";
        cout << "accountno: " << accountno << "\nname: " << name << "\naddress:\n" << address << endl;
        cout << "*****DEBUG*****\n";
    #endif
    
    newRec = new record();
    temp = NULL;
    follows = NULL;

    if (start == NULL)
    {
        start = newRec;
        newRec->next = NULL;
    }
    else if (accountno > start->accountno)
    {
        newRec->next = start;
        start = newRec;
    }
    else
    {
        temp = start;
        follows = temp->next;
        
        if ((temp->next == NULL) || (follows->accountno < accountno))
        {
            newRec->next = temp->next;
            temp->next = newRec;
        }
        else
        {
            do
            {
                if (temp->next == NULL)
                {
                    temp->next = newRec;
                }
                else
                {
                    temp = temp->next;
                    follows = temp->next;
                }
            }
            while ((follows != NULL) && (follows->accountno >= accountno));
            
            newRec->next = temp->next;
            temp->next = newRec;
        }
    }

    newRec->accountno = accountno;
    strcpy(newRec->name, name);
    strcpy(newRec->address, address);
}

/*****************************************************************
//
//  Function name: findRecord
//
//  DESCRIPTION:   This function will print the account info of the
//                 specified account(s)
//
//  Parameters:    accountno (int): The number of the account(s)
//                 to be printed
//
//  Return values: 0: The specified account was found
//                 -1: The specified account was not found
//
****************************************************************/
int llist::findRecord(int accountno)
{
    char addrPrint[60];
    struct record* temp = start;
    int returnVal = -1;
    
    #ifdef DEBUGMODE
        cout << "\n*****DEBUG*****\n";
        cout << "function called: findRecord\nparameters:\n";
        cout << "accountno: " << accountno << endl;
        cout << "*****DEBUG*****\n";
    #endif
    
    cout << "\n";
    while (temp != NULL)
    {
        if (temp->accountno == accountno)
        {
            returnVal = 0;
            cout << "Account number: ";
            cout << temp->accountno << endl;
            cout << "Name: ";
            cout << temp->name << endl;
            cout << "Address:\n";            
            strcpy(addrPrint, temp->address);
            addrPrint[strlen(addrPrint) - 1] = '\0';
            cout << addrPrint << "\n\n";
            strcpy(addrPrint, "\0");
        }
        temp = temp->next;
    }
    return returnVal;
}

/*****************************************************************
//
//  Function name: printAllRecords
//
//  DESCRIPTION:   This function prints all the records in the list
//
//  Parameters:    None
//
//  Return values: None
//
****************************************************************/
void llist::printAllRecords()
{
    char addrPrint[60];
    struct record* temp = start;
    
    #ifdef DEBUGMODE
        cout << "\n*****DEBUG*****\n";
        cout << "function called: printAllRecords\n";
        cout << "*****DEBUG*****\n";
    #endif

    if (start == NULL)
    {
        cout << "\nThere are no records to print.\n\n";
    }
    else
    {
        cout << "\n";
        while (temp != NULL)
        {
            cout << "Account number: ";
            cout << temp->accountno << endl;
            cout << "Name: ";
            cout << temp->name << endl;
            cout << "Address:\n";
            strcpy(addrPrint, temp->address);
            addrPrint[strlen(addrPrint) - 1] = '\0';
            cout << addrPrint << "\n\n";
            strcpy(addrPrint, "\0");
            temp = temp->next;
        }
        cout << "End of records list.\n\n";
    }
}

/*****************************************************************
//
//  Function name: deleteRecord
//
//  DESCRIPTION:   This function removes the specified account(s)
//                 from the list
//
//  Parameters:    accountno (int): The account number to be deleted
//
//  Return values: 0: The account(s) was successfully deleted
//                 -1: No account with that number could be found
//
****************************************************************/
int llist::deleteRecord(int accountno)
{
    int returnVal;
    struct record* temp;
    struct record* follows;
    returnVal = -1;
    temp = start;
    
    #ifdef DEBUGMODE
        cout << "\n*****DEBUG*****\n";
        cout << "function called: deleteRecord\nparameters:\n";
        cout << "accountno: " << accountno << endl;
        cout << "*****DEBUG*****\n";
    #endif
    
    if (start != NULL)
    {
        while ((start->next != NULL) && (start->accountno == accountno))
        {
            start = temp->next;
            delete temp;
            temp = start;
            returnVal = 0;
        }
        
        if ((start->accountno == accountno) && (start->next == NULL))
        {
            delete temp;
            start = NULL;
            returnVal = 0;
        }
        
        if (returnVal == -1)
        {
            follows = temp->next;
            while ((follows != NULL) && (accountno <= follows->accountno))
            {
                if (follows->accountno == accountno)
                {
                    temp->next = follows->next;
                    delete follows;
                    follows = temp->next;
                    returnVal = 0;
                }
                else
                {
                    temp = temp->next;
                    follows = temp->next;
                }
            }
        }
    }
    return returnVal;
}

/*****************************************************************
//
//  Function name: readfile
//
//  DESCRIPTION:   This function reads in data from a file and
//                 makes it into a linked list of accounts
//
//  Parameters:    None
//
//  Return values: 0: The file was successfully opened
//                 -1: The file could not be opened
//
****************************************************************/
int llist::readfile()
{
    int intAccNo;
    int done;
    char tempStr[60];
    char input[60];
    char strAccNo[20];
    struct record* prev;
    struct record* temp = new record();
    int empty = 1;
    
    #ifdef DEBUGMODE
        cout << "\n*****DEBUG*****\n";
        cout << "function called: readfile\n";
        cout << "*****DEBUG*****\n\n";
    #endif
    
    ifstream myfile(filename);
    
    if (myfile.is_open())
    {
        start = temp;
        
        while (myfile.getline(strAccNo, 20))
        {
            empty = 0;
            done = 0;
            intAccNo = atoi(strAccNo);
            strcpy(strAccNo, "\0");
            temp->accountno = intAccNo;
            myfile.getline(temp->name, 30);
            
            do
            {
                myfile.getline(tempStr, 60);
                strcat(input, tempStr);
                strcpy(tempStr, "\0");
                
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
            
            strcpy(temp->address, input);
            strcpy(tempStr, "\0");
            strcpy(input, "\0");
            
            prev = temp;
            temp->next = new record();
            temp = temp->next;
        }
        if (empty == 1)
        {
            start = NULL;
        }
        else
        {
            prev->next = NULL;
        }
        delete temp;
        temp = NULL;        
        myfile.close();
    }
    else
    {
        start = NULL;
        return -1;
    }
    return 0;
}

/*****************************************************************
//
//  Function name: writefile
//
//  DESCRIPTION:   This function writes the data in the linked list
//                 into a file
//
//  Parameters:    None
//
//  Return values: 0: The file was successfully opened
//                 -1: The file could not be opened
//
****************************************************************/
int llist::writefile()
{
    struct record* record = start;
    
    #ifdef DEBUGMODE
        cout << "\n*****DEBUG*****\n";
        cout << "function called: writefile\n";
        cout << "*****DEBUG*****\n";
    #endif
    
    ofstream myfile(filename);
    
    if (myfile.is_open())
    {
        while (record != NULL)
        {
            myfile << record->accountno << endl;
            myfile << record->name << endl;
            myfile << record->address << endl;
            record = record->next;
        }
        
        myfile.close();
        
        return 0;
    }
    else
    {
        return -1;
    }
    return 0;
}

/*****************************************************************
//
//  Function name: cleanup
//
//  DESCRIPTION:   This function frees all the space allocated to 
//                 the data in the list
//
//  Parameters:    None
//
//  Return values: None
//
****************************************************************/
void llist::cleanup()
{
    struct record* temp;
    struct record* prev;
    temp = start;
    
    #ifdef DEBUGMODE
        cout << "\n*****DEBUG*****\n";
        cout << "function called: cleanup\n";
        cout << "*****DEBUG*****\n\n";
    #endif
    
    while (temp != NULL)
    {
        prev = temp;
        temp = temp->next;
        delete prev;
    }
    
    start = NULL;
}