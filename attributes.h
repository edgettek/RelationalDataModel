//
// Created by Kyle Edgette on 11/13/16.
//

#ifndef RELATIONALDATAMODEL_ATTRIBUTES_H
#define RELATIONALDATAMODEL_ATTRIBUTES_H


typedef struct C_S_G_Row{
    char Course[6]; // These two rows combine
    int StudentId;	// to make the primary key
    char Grade[3];
    struct C_S_G_Row* next;
} C_S_G_Row;

typedef struct SNAPRow{
    int StudentId;
    char* name;
    char* address;
    char* phone;
    struct SNAPRow* next;
} SNAPRow;

typedef struct CPRow{
    char* course;//primary key
    char* day;
    struct CPRow* next;
} CPRow;


typedef struct CDHRow{
    char* course;//primary key- course and day together
    char* day;
    char* hour;
    struct CDHRow* next;
} CDHRow;


typedef struct CRRow{
    char* name;//primary key
    char* room;
    struct CRRow* next;
} CRRow;






#endif //RELATIONALDATAMODEL_ATTRIBUTES_H
