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
    for (int i = 0; i < 6; i++) {
        C_S_G_Row* returned = deleteCSG(toFill, CSGtable, true);
    }

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

    SNAPRow* returned = deleteSNAP(snapRow, SNAPtable, true);
    returned = deleteSNAP(snapRow, SNAPtable, true);



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

    CPRow* deletedCP = deleteCP(cpRow, CPtable, true);
    deletedCP = deleteCP(cpRow, CPtable, true);


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

    CDHRow* CDHDelete = deleteCDH(cdhRow, CDHTable, true);
    CDHDelete = deleteCDH(cdhRow, CDHTable, true);

    cdhRow.course = "EE400";
    cdhRow.day = "Th";
    cdhRow.hour = "10AM";

    CDHInsert = lookupCDH(cdhRow, CDHTable, true);
    CDHDelete = deleteCDH(cdhRow, CDHTable, true);

    printf("\n\t *** TESTING CR *** \n\n");

    CRRow* CRTable[TABLE_SIZE];


    for(int i = 0;i<TABLE_SIZE; i++){
        CRTable[i] = (CDHRow*)malloc(sizeof(CDHRow));
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
    CRRow* deleteCRTest = deleteCR(crRow, CRTable, true);

    lookCR = lookupCR(crRow, CRTable, true);

    crRow.course = "PH100";
    crRow.room = "Dewey 1101";

    lookCR = lookupCR(crRow, CRTable, true);
    deleteCRTest = deleteCR(crRow, CRTable, true);

    printf("\n\n *** END OF PROGRAM ***\n");

    return 0;


    //PART 2 TEST
    char* grade = getGradeByName("C.Brown", "CS101", SNAPtable, CSGtable);
    printf("grade: %s ", grade);

}