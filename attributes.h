//
// Created by Kyle Edgette on 11/13/16.
//

#ifndef RELATIONALDATAMODEL_ATTRIBUTES_H
#define RELATIONALDATAMODEL_ATTRIBUTES_H

#include <stdbool.h>

extern int TABLE_SIZE;

typedef struct C_S_G_Row{
    char course[6]; // These two rows combine
    int StudentId;	// to make the primary key
    char grade[3];
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
    char* course;//primary key
    char* room;
    struct CRRow* next;
} CRRow;

extern int stringToInt(char* string, int stringSize);

extern int hashIntAndString(char courseTitle[], int strSize, int id, int hashPrime);

extern int hashInt(int id, int hashPrime);

extern int hashTwoStrings(char str1[], int strSize1, char str2[],int strSize2, int hashPrime);

extern int hashOneString(char str[], int strSize, int hashPrime);

extern void printCSGRelation(C_S_G_Row* table[], bool debug);
extern C_S_G_Row* deleteCSG(C_S_G_Row row, C_S_G_Row* table[], bool debug);
extern void insertCSG(C_S_G_Row row, C_S_G_Row* table[], bool debug);
extern C_S_G_Row* lookupCSG(C_S_G_Row row, C_S_G_Row* table[], bool debug);

extern void insertSNAP(SNAPRow row, SNAPRow* table[], bool debug);
extern SNAPRow* deleteSNAP(SNAPRow row, SNAPRow* table[], bool debug);
extern SNAPRow* lookupSNAP(SNAPRow row, SNAPRow* table[], bool debug);
extern C_S_G_Row* lookupCSG(C_S_G_Row row, C_S_G_Row* table[], bool debug);

extern void printSNAPRelation(SNAPRow* table[], bool debug);
extern void printCPRelation(CPRow* table[], bool debug);
extern void printCRRelation(CRRow* table[], bool debug);
extern void printCDHRelation(CDHRow* table[], bool debug);

extern void insertCP(CPRow row, CPRow* table[], bool debug);
extern CPRow* deleteCP(CPRow row, CPRow* table[], bool debug);
extern CPRow* lookupCP(CPRow row, CPRow* table[], bool debug);
extern void insertCDH(CDHRow row, CDHRow* table[], bool debug);
extern CDHRow* lookupCDH(CDHRow row, CDHRow* table[], bool debug);
extern CDHRow* deleteCDH(CDHRow row, CDHRow* table[], bool debug);
extern SNAPRow* selectSNAPByName(char* name, SNAPRow* table[]);
extern int projectSId(SNAPRow* thisRow);

extern void insertCR(CRRow row, CRRow* table[], bool debug);
extern CRRow* lookupCR(CRRow row, CRRow* table[], bool debug);
extern CRRow* deleteCR(CRRow row, CRRow* table[], bool debug);
extern C_S_G_Row* selectCSGByIdAndCourse(int id, char* course, C_S_G_Row* table[], bool debug);

extern char* projectGrade(C_S_G_Row* row);
extern char* getGradeByName(char* name, char* course, SNAPRow* snapTable[], C_S_G_Row* csgTable[]);
extern int projectId(SNAPRow* row);

extern C_S_G_Row* selectCoursesById(C_S_G_Row* csgTable[], int studentId);
extern CDHRow* selectCDHByCourseAndDay(CDHRow* cdhTable[], char* course, char* day);

extern CRRow* selectCRByCourse(CRRow* crTable[], char* course);

extern char* getRoom(char*name, char* time, char* day, C_S_G_Row* csgTable[], CRRow* crTable[], SNAPRow* snapTable[], CDHRow* cdhTable[]);

extern C_S_G_Row** project(C_S_G_Row* table[], char* array_of_attributes[]);

#endif //RELATIONALDATAMODEL_ATTRIBUTES_H
