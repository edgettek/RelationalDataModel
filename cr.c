//
// Created by Manan hora on 11/16/16.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "attributes.h"

void insertCR(CRRow row, CRRow* table[], bool debug){
    int index = hashOneString(row.course, 6, TABLE_SIZE);

    CRRow* this = table[index];

    while ((this->next) != NULL) {
        this = this->next;
    }

    CRRow* newer = (CRRow*) malloc(sizeof(CRRow));
    if (this->course == NULL) {
        this->next = newer;
        this = newer;
    }


    memcpy(this, &row, sizeof(CRRow));

    if (debug) {
        printf("Successfully inserted new row at hashtable index %i\n", index);
    }
    return;
}

CRRow* lookupCR(CRRow row, CRRow* table[], bool debug){
    int index = hashOneString(row.course, 6, TABLE_SIZE);

    CRRow* this = table[index];

    if(this->course == NULL) {
        return NULL;
    }

    while ((this->next) != NULL) {
        if (strcmp(this->course, row.course) == 0 && strcmp(this->room, row.room) == 0){
            if (debug) {
                printf("Successfully found matching row at hashtable index %i\n", index);
            }
            return this;
        }
        this = this->next;
    }

    if(strcmp(this->course, row.course) == 0 && strcmp(this->room, row.room) == 0) {
        if (debug) {
            printf("Successfully found matching row at hashtable index %i\n", index);
        }
        return this;
    }


    if (this->course == row.course && this->room == row.room) {
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

CRRow* deleteCR(CRRow row, CRRow* table[], bool debug){
    int index = hashTwoStrings(row.course, 6, row.room, 6, TABLE_SIZE);

    CRRow* this = table[index];

    if(this->course == NULL) {
        return NULL;
    }

    if (this->course == row.course && this->room==row.room) {
        CRRow* returner = this->next;
        this->next = (this->next)->next;
        if (debug) {
            printf("Successfully deleted row at hashtable index %i\n", index);
        }
        return returner;
    }

    while ((this->next) != NULL) {
        if ((strcmp(this->next->course, row.course) == 0) && (strcmp(this->next->room, row.room) == 0)) {

            CRRow *returner = this->next;
            this->next = (this->next)->next;
            if (debug) {
                printf("Successfully deleted row at hashtable index %i\n", index);
            }
            return returner;
        }
        else{
            this = this->next;
        }
    }

    if (debug) {
        printf("No matching row to delete in hashtable at index %i, returning null\n", index);
    }
    return NULL;
}