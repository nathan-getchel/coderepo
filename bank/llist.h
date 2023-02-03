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
//  FILE:        llist.h
//
//  DESCRIPTION:
//   Class definition of the linked list
//
//  REFERENCES:
//   none 
//
****************************************************************/

#include "record.h"

#ifndef LLIST_H
#define LLIST_H

class llist
{
private:
    record *    start;
    char        filename[20];
    int         readfile();
    int         writefile();
    void        cleanup();

public:
    llist();
    llist(char[]);
    ~llist();
    void addRecord(int, char [ ],char [ ]);
    int findRecord(int);
    void printAllRecords();
    int deleteRecord(int);
};

#endif