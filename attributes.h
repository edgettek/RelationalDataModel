//
// Created by Kyle Edgette on 11/13/16.
//

#ifndef RELATIONALDATAMODEL_ATTRIBUTES_H
#define RELATIONALDATAMODEL_ATTRIBUTES_H

#include <stdbool.h>

extern int TABLE_SIZE;

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
    char* prereq;
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

extern int stringToInt(char* string, int stringSize);

extern int hashIntAndString(char courseTitle[], int strSize, int id, int hashPrime);

extern int hashInt(int id, int hashPrime);

extern int hashTwoStrings(char str1[], int strSize1, char str2[],int strSize2, int hashPrime);

extern int hashOneString(char str[], int strSize, int hashPrime);

extern void insertCSG(C_S_G_Row row, C_S_G_Row* table[], bool debug);
extern void insertSNAP(SNAPRow row, SNAPRow* table[], bool debug);
extern SNAPRow* deleteSNAP(SNAPRow row, SNAPRow* table[], bool debug);
extern SNAPRow* lookupSNAP(SNAPRow row, SNAPRow* table[], bool debug);

extern void insertCP(CPRow row, CPRow* table[], bool debug);
extern CPRow* deleteCP(CPRow row, CPRow* table[], bool debug);
extern CPRow* lookupCP(CPRow row, CPRow* table[], bool debug);



#endif //RELATIONALDATAMODEL_ATTRIBUTES_H
