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
    for(int i = 0; i<TABLE_SIZE; i++){
        while(table[i]->next!=NULL){
            SNAPRow* thisRow = table[i];
            if(thisRow->name == name){
                return thisRow;
            }
            thisRow = thisRow->next;
        }
    }
    return NULL;
}

int projectId(SNAPRow* row){
    return row->StudentId;
}

C_S_G_Row* selectCSGByIdAndCourse(int id, char* course C_S_G_Row* table[], bool debug){
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


