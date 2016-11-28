//
// Created by Kyle Edgette on 11/19/16.
//

#include "attributes.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char const *argv[])
{
    printf("\n\t *** TESTING CSG *** \n\n");

    // Initialize table
    C_S_G_Row* CSGtable[TABLE_SIZE];
    for (int i = 0; i < TABLE_SIZE; i++) {
        CSGtable[i] = (C_S_G_Row*) malloc(sizeof(C_S_G_Row));
        CSGtable[i]->next = NULL;
    }

    // Inserting tuples into CSG Relation
    C_S_G_Row toFill;

    strcpy(toFill.course, "CS101");
    toFill.StudentId = 12345;
    strcpy(toFill.grade, "A");
    insertCSG(toFill, CSGtable, true);
    insertCSG(toFill, CSGtable, true);
    insertCSG(toFill, CSGtable, true);

    strcpy(toFill.course, "CS101");
    toFill.StudentId = 67890;
    strcpy(toFill.grade, "B");
    insertCSG(toFill, CSGtable, true);

    strcpy(toFill.course, "EE200");
    toFill.StudentId = 12345;
    strcpy(toFill.grade, "C");
    insertCSG(toFill, CSGtable, true);

    strcpy(toFill.course, "EE200");
    toFill.StudentId = 22222;
    strcpy(toFill.grade, "B+");
    insertCSG(toFill, CSGtable, true);

    strcpy(toFill.course, "CS101");
    toFill.StudentId = 33333;
    strcpy(toFill.grade, "A-");
    insertCSG(toFill, CSGtable, true);

    strcpy(toFill.course, "PH100");
    toFill.StudentId = 67890;
    strcpy(toFill.grade, "C+");
    insertCSG(toFill, CSGtable, true);

    // Printing relation to file
    printCSGRelation(CSGtable, true);



    C_S_G_Row* lookedup = lookupCSG(toFill, CSGtable, true);

    C_S_G_Row* CSGNewTable[TABLE_SIZE];
    for (int i = 0; i < TABLE_SIZE; i++) {
        CSGNewTable[i] = (C_S_G_Row*) malloc(sizeof(C_S_G_Row));
        CSGNewTable[i]->next = NULL;
    }

    readFromFileCSG(CSGNewTable, "CSGInput.txt", true);

    printCSGToConsole(CSGNewTable, true);

    printf("\n\t *** TESTING SNAP *** \n\n");

    SNAPRow* SNAPtable[TABLE_SIZE];
    for (int i = 0; i < TABLE_SIZE; i++) {
        SNAPtable[i] = (SNAPRow*) malloc(sizeof(SNAPRow));
        SNAPtable[i]->name=NULL;
        SNAPtable[i]->StudentId = 0;
        SNAPtable[i]->next = NULL;
        SNAPtable[i]->address = NULL;
        SNAPtable[i]->phone = NULL;
    }
    SNAPRow snapRow;
    snapRow.name = "C.Brown";
    snapRow.StudentId = 12345;
    snapRow.address = "12 Apple St.";
    snapRow.phone = "555-1234";
    snapRow.next = NULL;

    insertSNAP(snapRow, SNAPtable, true);

    SNAPRow row2;
    row2.name = "Raina Langevin";
    row2.StudentId = 12335;
    row2.address = "Burlington Street, Burlington, VT";
    row2.phone = "555-3334";
    row2.next = NULL;

    for(int i = 0; i<2; i++){
        insertSNAP(row2, SNAPtable, true);
    }

    snapRow.name = "L. Van Pelt";
    snapRow.StudentId = 67890;
    snapRow.address = "34 Pear Ave";
    snapRow.phone = "555-5678";
    snapRow.next = NULL;

    insertSNAP(snapRow, SNAPtable, true);

    snapRow.name = "P. Patty";
    snapRow.StudentId = 22222;
    snapRow.address = "56 Grape Blvd.";
    snapRow.phone = "555-9999";
    snapRow.next = NULL;

    insertSNAP(snapRow, SNAPtable, true);

    printSNAPRelation(SNAPtable, true);

    SNAPRow* thisRow = lookupSNAP(snapRow, SNAPtable, true);
    thisRow = lookupSNAP(row2, SNAPtable, true);



    SNAPRow* SNAPtable2[TABLE_SIZE];
    for (int i = 0; i < TABLE_SIZE; i++) {
        SNAPtable2[i] = (SNAPRow*) malloc(sizeof(SNAPRow));
        SNAPtable2[i]->name=NULL;
        SNAPtable2[i]->StudentId = 0;
        SNAPtable2[i]->next = NULL;
        SNAPtable2[i]->address = NULL;
        SNAPtable2[i]->phone = NULL;
    }

    readFromFileSNAP(SNAPtable2, "SNAPInput.txt", true);

    snapRow.name = "A. Brown";
    snapRow.StudentId = 12344;
    snapRow.address = "444 Birch Lane";
    snapRow.phone = "654-2341";
    snapRow.next = NULL;

    thisRow = lookupSNAP(snapRow, SNAPtable, true);

    printSNAPToConsole(SNAPtable2, true);

    printf("\n\t *** TESTING CP *** \n\n");
    //3) CP
    CPRow* CPtable[TABLE_SIZE];

    for(int i = 0;i<TABLE_SIZE; i++){
        CPtable[i] = (CPRow*)malloc(sizeof(CPRow));
        CPtable[i]->next = NULL;
        CPtable[i]->course = NULL;
        CPtable[i]->prereq = NULL;
    }
    CPRow cpRow;
    cpRow.course = "CS101";
    cpRow.prereq = "CS100";

    insertCP(cpRow, CPtable, true);
    CPRow cpRow2;
    cpRow2.course = "EE200";
    cpRow2.prereq = "EE005";

    insertCP(cpRow2, CPtable, true);

    cpRow.course = "EE200";
    cpRow.prereq = "CS100";

    insertCP(cpRow, CPtable, true);

    cpRow.course = "CS120";
    cpRow.prereq = "CS101";

    insertCP(cpRow, CPtable, true);

    cpRow.course = "CS121";
    cpRow.prereq = "CS120";

    insertCP(cpRow, CPtable, true);

    cpRow.course = "CS205";
    cpRow.prereq = "CS101";

    insertCP(cpRow, CPtable, true);

    cpRow.course = "CS206";
    cpRow.prereq = "CS121";

    insertCP(cpRow, CPtable, true);

    cpRow.course = "CS206";
    cpRow.prereq = "CS205";

    insertCP(cpRow, CPtable, true);

    printCPRelation(CPtable, true);


    CPRow* findCPRow1 = lookupCP(cpRow, CPtable, true);
    CPRow* findCPRow2 = lookupCP(cpRow2, CPtable, true);

    CPRow* CPtable2[TABLE_SIZE];
    for(int i = 0;i<TABLE_SIZE; i++){
        CPtable2[i] = (CPRow*)malloc(sizeof(CPRow));
        CPtable2[i]->next = NULL;
        CPtable2[i]->course = NULL;
        CPtable2[i]->prereq = NULL;
    }

    readFromFileCP(CPtable2, "CPInput.txt", true);

    printCPToConsole(CPtable2, true);

    //4) CDH

    printf("\n\t *** TESTING CDH *** \n\n");

    CDHRow* CDHTable[TABLE_SIZE];


    for(int i = 0;i<TABLE_SIZE; i++){
        CDHTable[i] = (CDHRow*)malloc(sizeof(CDHRow));
        CDHTable[i]->next = NULL;
        CDHTable[i]->course = NULL;
        CDHTable[i]->day = NULL;
        CDHTable[i]->hour = NULL;
    }
    CDHRow cdhRow;
    cdhRow.course = "CS101";
    cdhRow.day = "M";
    cdhRow.hour = "9AM";

    insertCDH(cdhRow, CDHTable, true);
    CDHRow cdhRow1;
    cdhRow1.course = "CSC101";
    cdhRow1.day = "W";
    cdhRow1.hour = "9AM";

    insertCDH(cdhRow1, CDHTable, true);

    cdhRow.course = "CS101";
    cdhRow.day = "F";
    cdhRow.hour = "9AM";

    insertCDH(cdhRow, CDHTable, true);

    cdhRow.course = "EE200";
    cdhRow.day = "Tu";
    cdhRow.hour = "10AM";

    insertCDH(cdhRow, CDHTable, true);

    cdhRow.course = "EE200";
    cdhRow.day = "W";
    cdhRow.hour = "1PM";

    insertCDH(cdhRow, CDHTable, true);

    cdhRow.course = "EE200";
    cdhRow.day = "Th";
    cdhRow.hour = "10AM";

    insertCDH(cdhRow, CDHTable, true);

    printCDHRelation(CDHTable, true);

    CDHRow* CDHInsert = lookupCDH(cdhRow, CDHTable, true);
    CDHInsert = lookupCDH(cdhRow1, CDHTable, true);

    cdhRow.course = "EE400";
    cdhRow.day = "Th";
    cdhRow.hour = "10AM";

    CDHInsert = lookupCDH(cdhRow, CDHTable, true);


    CDHRow* CDHTable2[TABLE_SIZE];


    for(int i = 0;i<TABLE_SIZE; i++){
        CDHTable2[i] = (CDHRow*)malloc(sizeof(CDHRow));
        CDHTable2[i]->next = NULL;
        CDHTable2[i]->course = NULL;
        CDHTable2[i]->day = NULL;
        CDHTable2[i]->hour = NULL;
    }

    readFromFileCDH(CDHTable2, "CDHInput.txt", true);

    printCDHToConsole(CDHTable2, true);


    printf("\n\t *** TESTING CR *** \n\n");

    CRRow* CRTable[TABLE_SIZE];


    for(int i = 0;i<TABLE_SIZE; i++){
        CRTable[i] = (CRRow*)malloc(sizeof(CRRow));
        CRTable[i]->next = NULL;
        CRTable[i]->course = NULL;
        CRTable[i]->room = NULL;
    }
    CRRow crRow;

    crRow.course = "CS101";
    crRow.room = "Turing Aud.";

    insertCR(crRow, CRTable ,true);

    crRow.course = "EE200";
    crRow.room = "25 Ohm Hall";

    insertCR(crRow, CRTable ,true);

    crRow.course = "PH100";
    crRow.room = "Newton Lab.";

    insertCR(crRow, CRTable ,true);

    printCRRelation(CRTable, true);

    CRRow* lookCR = lookupCR(crRow, CRTable, true);


    lookCR = lookupCR(crRow, CRTable, true);

    crRow.course = "PH100";
    crRow.room = "Dewey 1101";

    lookCR = lookupCR(crRow, CRTable, true);

    CRRow* CRTable2[TABLE_SIZE];


    for(int i = 0;i<TABLE_SIZE; i++){
        CRTable2[i] = (CRRow*)malloc(sizeof(CRRow));
        CRTable2[i]->next = NULL;
        CRTable2[i]->course = NULL;
        CRTable2[i]->room = NULL;
    }

    readFromFileCR(CRTable2, "CRInput.txt", true);

    printCRToConsole(CRTable2, true);

    //PART 2 TEST

    printf("\n\t *** PART 2: \"What grade did StudentName get in CourseName?\"  *** \n\n");

    char* grade = getGradeByName("C.Brown", "CS101", SNAPtable, CSGtable);
    printf("C.Brown got a grade of %s in CSC101\n", grade);

    grade = getGradeByName("L. Van Pelt", "PH100", SNAPtable, CSGtable);
    printf("L. Van Pelt got a grade of %s in PH100\n", grade);

    grade = getGradeByName("A. Lincoln", "PH100", SNAPtable, CSGtable);
    printf("A. Lincoln got a grade of %s in PH100\n", grade);


    printf("\n\t *** PART 2: \"Where is StudentName at Time on Day?\"  *** \n\n");

    char* roomResult = getRoom("C.Brown", "9AM", "F", CSGtable, CRTable, SNAPtable, CDHTable);
    printf("C.Brown is in Room %s at %s on %s\n", roomResult, "9AM", "F");

    roomResult = getRoom("P. Patty", "1PM", "W", CSGtable, CRTable, SNAPtable, CDHTable);
    printf("P. Patty is in Room %s at %s on %s\n", roomResult, "1PM", "W");

    roomResult = getRoom("C.Brown", "11AM", "F", CSGtable, CRTable, SNAPtable, CDHTable);
    printf("C.Brown is in Room %s at %s on %s\n", roomResult, "11AM", "F");

    //PART 3 TEST:

    char* array[] = {"Course", "Grade"};
    C_S_G_Row* projectRow = project(CSGtable, array);
    printProjectedCSGToConsole(projectRow, true);

    CRDHrow* joinedRows = join(CRTable, CDHTable);
    printCDHRToConsole(joinedRows, true);

    printf("TESTING SELECT OPs\n");
    C_S_G_Row* selectedRows = selectCoursesById(CSGtable, 12345);
    while(selectedRows!=NULL){
        printf("selected Row course = %s  \n", selectedRows->course);
        selectedRows=selectedRows->next;
    }
    printf("\n");

    CDHRow* selectedRows2 = selectCDHByCourseAndDay(CDHTable, "CS101", "M");
    while(selectedRows2!=NULL){
        printf("selected Row course = %s, selected Row time = %s  \n", selectedRows2->course, selectedRows2->hour);
        selectedRows2=selectedRows2->next;
    }


    // Testing Part 1 Delete Operations

    printf("\n\t *** PART 1: TESTING DELETE OPERATIONS *** \n\n");


    C_S_G_Row* returnedCSG = deleteCSG(toFill, CSGtable, true);

    snapRow.name = "C.Brown";
    snapRow.StudentId = 12345;
    snapRow.address = "12 Apple St.";
    snapRow.phone = "555-1234";
    snapRow.next = NULL;


    SNAPRow* returnedSNAP = deleteSNAP(snapRow, SNAPtable, true);
    returnedSNAP = deleteSNAP(snapRow, SNAPtable, true);

    CPRow* deletedCP = deleteCP(cpRow, CPtable, true);
    deletedCP = deleteCP(cpRow, CPtable, true);

    cdhRow.course = "CS101";
    cdhRow.day = "M";
    cdhRow.hour = "9AM";

    CDHRow* CDHDelete = deleteCDH(cdhRow, CDHTable, true);
    CDHDelete = deleteCDH(cdhRow, CDHTable, true);

    CDHDelete = deleteCDH(cdhRow, CDHTable, true);

    crRow.course = "CS101";
    crRow.room = "Turing Aud.";

    CRRow* deleteCRTest = deleteCR(crRow, CRTable, true);
    deleteCRTest = deleteCR(crRow, CRTable, true);


    return 0;

    printf("\n\n *** END OF PROGRAM ***\n");

}