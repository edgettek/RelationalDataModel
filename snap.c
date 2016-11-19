//
// Created by Kyle Edgette on 11/15/16.
//

#include "attributes.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>


void insertSNAP(SNAPRow row, SNAPRow* table[], bool debug) {
    int index = hashInt(row.StudentId, TABLE_SIZE);

    if(lookupSNAP(row, table, false) != NULL) {
        if(debug) {printf("That row already existed!\n");}
        return;
    }
    else {

        SNAPRow *this = table[index];

        while ((this->next) != NULL) {
            this = this->next;
        }

        SNAPRow *newer = (SNAPRow *) malloc(sizeof(SNAPRow));

        if (this->name == NULL) {
            this->next = newer;
            this = newer;
        }

        memcpy(this, &row, sizeof(SNAPRow));

        if (debug) {
            printf("Successfully inserted new row at hashtable index %i\n", index);
        }
        return;
    }
}

SNAPRow* lookupSNAP(SNAPRow row, SNAPRow* table[], bool debug){
    int index = hashInt(row.StudentId, TABLE_SIZE);

    SNAPRow* this = table[index];

    if(this->name == NULL) {
        return NULL;
    }

    while ((this->next) != NULL) {
        if (strcmp(this->StudentId, row.StudentId) == 0 && strcmp(this->name, row.name) == 0 && strcmp(this->address, row.address) == 0 && strcmp(this->phone, row.phone) == 0){
            if (debug) {
                printf("Successfully found matching row at hashtable index %i\n", index);
                printf("name is %s\n", this->name);
            }
            return this;
        }
        this = this->next;
    }



    if(strcmp(this->StudentId, row.StudentId) == 0 && strcmp(this->name, row.name) == 0 && strcmp(this->address, row.address) == 0 && strcmp(this->phone, row.phone) == 0) {
        if (debug) {
            printf("Successfully found matching row at hashtable index %i\n", index);
        }
        return this;
    }

    if (this->StudentId == row.StudentId) {
        if (debug) {
            printf("Successfully found matching row at hashtable index %i\n", index);
            printf("name is %s\n", this->name);
        }
        return this;
    } else {
        if (debug) {
            printf("Could not find matching row at hashtable index %i, returning null\n", index);
        }
        return NULL;
    }
}

SNAPRow* deleteSNAP(SNAPRow row, SNAPRow* table[], bool debug){
    int index = hashInt(row.StudentId, TABLE_SIZE);

    SNAPRow* this = table[index];

    if(this->name == NULL) {
        return NULL;
    }

    if (this->StudentId == row.StudentId) {
        SNAPRow* returner = this->next;
        this->next = (this->next)->next;
        if (debug) {
            printf("Successfully deleted row at hashtable index %i\n", index);
        }
        return returner;
    }

    while ((this->next) != NULL && (this->next)) {
        if ((this->next)->StudentId == row.StudentId){

            SNAPRow* returner = this->next;
            this->next = (this->next)->next;
            if (debug) {
                printf("Successfully deleted row at hashtable index %i\n", index);
            }
            return returner;
        }
        this = this->next;
    }
    if (debug) {
        printf("No matching row to delete in hashtable at index %i, returning null\n", index);
    }
    return NULL;
}