//
// Created by Manan hora on 11/19/16.
//

#include "attributes.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

SNAPRow* selectSNAPByName(char* name, SNAPRow* table[]){
//assuming one entry per name
//
    SNAPRow *thisRow;
    for(int i = 0; i<TABLE_SIZE; i++){
        thisRow = table[i];

        if(thisRow->name != NULL) {
            if (table[i]->name == name) {
                return table[i];
            }

            while (thisRow->next != NULL) {
                thisRow = thisRow->next;
                if (thisRow->name == name) {
                    return thisRow;
                }
            }
        }
    }
    return NULL;
}

void printCDHRToConsole(CRDHrow* table, bool debug) {

    printf("Printing Out CRDH Table\n\n");

    CRDHrow currentRow;

    for(int i = 0; i < TABLE_SIZE; i++) {

        currentRow = table[i];

        if(strcmp(currentRow.course, "") != 0) {

            printf("%s\t%s\t%s\t%s\n", currentRow.course, currentRow.room, currentRow.day, currentRow.hour);

            while (currentRow.next != NULL) {
                currentRow = *currentRow.next;
                printf("%s\t%s\t%s\t%s\n", currentRow.course, currentRow.room, currentRow.day, currentRow.hour);

            }
        }

    }

    printf("\n");

}

void printProjectedCSGToConsole(C_S_G_Row* table, bool debug) {

    printf("Printing Out Projected CSG Table\n\n");

    C_S_G_Row currentRow;

    C_S_G_Row* listOfSeen = (C_S_G_Row*) (malloc(sizeof(C_S_G_Row)));
    listOfSeen->next = NULL;

    for(int i = 0; i < TABLE_SIZE; i++) {

        currentRow = table[i];
        bool anythingPrinted = false;
        bool seenBefore = false;

        if (strcmp(currentRow.course, "CS101") == 0) {
            printf("");
        }

        C_S_G_Row* walker = listOfSeen;
        while (walker != NULL) {
            if (strcmp(currentRow.course, walker->course) == 0 && 
                currentRow.StudentId == walker->StudentId &&
                (strcmp(currentRow.grade, walker->grade) == 0)) {
                    seenBefore = true;
                    break;
                }
            walker = walker->next;
        } 

        if (seenBefore) {continue;}

        if (strcmp(currentRow.course, "") != 0) {
            printf("%s\t", currentRow.course);
            anythingPrinted = true;
        }
        if (currentRow.StudentId != -1 && currentRow.StudentId != 0) {
            printf("%d\t", currentRow.StudentId);
            anythingPrinted = true;
        }
        if (strcmp(currentRow.grade, "") != 0) {
            printf("%s\t", currentRow.grade);
            anythingPrinted = true;
        }

        while (currentRow.next != NULL) {
            currentRow = *currentRow.next;
            if (strcmp(currentRow.course, "") != 0) {
                printf("%s\t", currentRow.course);
                anythingPrinted = true;
            }
            if (currentRow.StudentId != -1 && currentRow.StudentId != 0) {
                printf("%d\t", currentRow.StudentId);
                anythingPrinted = true;
            }
            if (strcmp(currentRow.grade, "") != 0) {
                printf("%s\t", currentRow.grade);
                anythingPrinted = true;
            }
            printf("\n");
        }

        if (anythingPrinted) {
            printf("\n");
            walker = listOfSeen;
            while (walker->next != NULL) {
                walker = walker->next;
            }
            C_S_G_Row* newSeen = (C_S_G_Row*) malloc(sizeof(C_S_G_Row));
            strcpy(newSeen->course, currentRow.course);
            newSeen->StudentId = currentRow.StudentId;
            strcpy(newSeen->grade, currentRow.grade);
            walker->next = newSeen;
        }
    }

    printf("\n");

}

int projectId(SNAPRow* row){
    return row->StudentId;
}

C_S_G_Row* selectCSGByIdAndCourse(int id, char* course, C_S_G_Row* table[], bool debug){
    int index = hashIntAndString(course, 6, id, TABLE_SIZE);
    C_S_G_Row* this = table[index];
    while ((this->next) != NULL) {
        if (strcmp(this->course, course) == 0 &&
            this->StudentId == id){
            if (debug) {
                printf("Successfully found matching row at hashtable index %i\n", index);
            }
            return this;
        }
        this = this->next;
    }

    if (strcmp(this->course, course) == 0 && this->StudentId == id) {
        if (debug) {
            printf("Successfully found matching row at hashtable index %i\n", index);
        }
        return this;

    }

    if (this->course == course && this->StudentId == id) {
        if (debug) {
            printf("Successfully found matching row at hashtable index %i\n", index);
        }
        return this;
    } else {
        if (debug) {
            printf("Could not find matching row at hashtable index %i, returning null\n", index);
        }
        return NULL;
    }
}

char* projectGrade(C_S_G_Row* row){
    return row->grade;
}

C_S_G_Row* selectCoursesById(C_S_G_Row* csgTable[], int studentId){
    //NOTE - INEFFICIENT APPROACH- Should use secondary indexes if we have time..
    C_S_G_Row* row = (C_S_G_Row*) malloc(sizeof(C_S_G_Row));
    C_S_G_Row* tempRow = (C_S_G_Row*) malloc(sizeof(C_S_G_Row));
    for(int i = 0; i<TABLE_SIZE; i++){
        if(strcmp(csgTable[i]->course, "") != 0){
            C_S_G_Row* thisRow = csgTable[i];
            if(thisRow->StudentId == studentId){
                if(strcmp(row->course, "") == 0){
                    memcpy(row, thisRow, sizeof(C_S_G_Row));
                    row->next = (C_S_G_Row*) malloc(sizeof(C_S_G_Row));
                    tempRow = row->next;
                }
                else{
                    if(strcmp(tempRow->course, "") == 0){
                        memcpy(tempRow, thisRow, sizeof(C_S_G_Row));
                        tempRow->next = (C_S_G_Row*) malloc(sizeof(C_S_G_Row));
                        tempRow = tempRow->next;
                    }
//                    else{
//                        while(tempRow->next!=NULL){
//                            tempRow = tempRow->next;
//                        }
//                        tempRow->next = thisRow;
//                    }
                }
            }
            else {

            }
        }
    }
    return row;
}


CDHRow* selectCDHByCourseAndDay(CDHRow* cdhTable[], char* course, char* day){
    int index = hashTwoStrings(course, 6, day, 6, TABLE_SIZE);

    CDHRow* this = cdhTable[index];

    if(this->course == NULL) {
        return NULL;
    }

    while ((this->next) != NULL) {
        if (strcmp(this->course, course) == 0 && strcmp(this->day, day) == 0){
            return this;
        }
        this = this->next;
    }

    if(strcmp(this->course, course) == 0 && strcmp(this->day, day) == 0 ) {

        return this;
    }


    if (this->course == course && this->day == day) {

        return this;
    } else {

        return NULL;
    }
}

CRRow* selectCRByCourse(CRRow* crTable[], char* course){
    int index = hashOneString(course, 6, TABLE_SIZE);

    CRRow* this = crTable[index];

    if(this->course == NULL) {
        return NULL;
    }

    while ((this->next) != NULL) {
        if (strcmp(this->course, course) == 0){

            return this;
        }
        this = this->next;
    }

    if(strcmp(this->course, course) == 0 ) {

        return this;
    }

    if (this->course == course) {

        return this;
    } else {

        return NULL;
    }
}