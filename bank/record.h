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
//  FILE:        record.h
//
//  DESCRIPTION:
//   Defines the structure of a customer record
//
//  REFERENCES:
//    none
//
****************************************************************/
#ifndef RECORD_H
#define RECORD_H

struct record
{
    int                accountno;
    char               name[30];
    char               address[60];
    struct record*     next;
};

#endif