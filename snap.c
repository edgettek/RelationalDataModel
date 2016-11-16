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

    SNAPRow* this = table[index];

    while ((this->next) != NULL ){
        this = this->next;
    }

    SNAPRow* newer = (SNAPRow*) malloc(sizeof(SNAPRow));
    this->next = newer;
    this = newer;
    this->next = NULL;
    newer->next = NULL;
    row.next = NULL;

    memcpy(this, &row, sizeof(SNAPRow));

    if (debug) {
        printf("Successfully inserted new row at hashtable index %i\n", index);
    }
    return;
}

SNAPRow* lookupSNAP(SNAPRow row, SNAPRow* table[], bool debug){
    int index = hashInt(row.StudentId, TABLE_SIZE);

    SNAPRow* this = table[index];
    while ((this->next) != NULL) {
        if (this->StudentId == row.StudentId){
            if (debug) {
                printf("Successfully found matching row at hashtable index %i\n", index);
            }
            return this;
        }
        this = this->next;
    }
    if (this->StudentId == row.StudentId) {
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

SNAPRow* deleteSNAP(SNAPRow row, SNAPRow* table[], bool debug){
    int index = hashInt(row.StudentId, TABLE_SIZE);

    SNAPRow* this = table[index];

    if (this->StudentId == row.StudentId) {
        SNAPRow* returner = this->next;
        this->next = (this->next)->next;
        if (debug) {
            printf("Successfully deleted row at hashtable index %i\n", index);
        }
        return returner;
    }

    while ((this->next) != NULL) {
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