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
    C_S_G_Row* row = NULL;
    C_S_G_Row* tempRow = NULL;
    for(int i = 0; i<TABLE_SIZE; i++){
        while(csgTable[i]->next!=NULL){
            C_S_G_Row* thisRow = csgTable[i];
            if(thisRow->StudentId == studentId){
                if(row==NULL){
                    row = thisRow;
                    row->next = tempRow;
                }
                else{
                    if(tempRow==NULL){
                        tempRow = thisRow;
                    }
                    else{
                        while(tempRow->next!=NULL){
                            tempRow = tempRow->next;
                        }
                        tempRow->next = thisRow;
                    }
                }
            }
        }
    }
    return row;
}


CDHRow* selectCDHByCourse(CDHRow* cdhTable[], char* course, char* day){
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