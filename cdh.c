//
// Created by Manan hora on 11/16/16.
//
#include "attributes.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

void insertCDH(CDHRow row, CDHRow* table[], bool debug){
    int index = hashTwoStrings(row.course, 6, row.day, 6, TABLE_SIZE);

    CDHRow* this = table[index];

    while ((this->next) != NULL) {
        this = this->next;
    }

    CDHRow* newer = (CDHRow*) malloc(sizeof(CDHRow));

    if (this->course == NULL) {
        this->next = newer;
        this = newer;
    }


    memcpy(this, &row, sizeof(CDHRow));

    if (debug) {
        printf("Successfully inserted new row at hashtable index %i\n", index);
    }
    return;
}

CDHRow* lookupCDH(CDHRow row, CDHRow* table[], bool debug){
    int index = hashTwoStrings(row.course, 6, row.day, 6, TABLE_SIZE);

    CDHRow* this = table[index];

    if(this->course == NULL) {
        return NULL;
    }

    while ((this->next) != NULL) {
        if (strcmp(this->course, row.course) == 0 && strcmp(this->day, row.day) == 0 && strcmp(this->hour, row.hour) == 0){
            if (debug) {
                printf("Successfully found matching row at hashtable index %i\n", index);
            }
            return this;
        }
        this = this->next;
    }

    if(strcmp(this->course, row.course) == 0 && strcmp(this->day, row.day) == 0 && strcmp(this->hour, row.hour) == 0) {
        if (debug) {
            printf("Successfully found matching row at hashtable index %i\n", index);
        }
        return this;
    }


    if (this->course == row.course && this->day == row.day) {
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

CDHRow* deleteCDH(CDHRow row, CDHRow* table[], bool debug){
    int index = hashTwoStrings(row.course, 6, row.day, 6, TABLE_SIZE);

    CDHRow* this = table[index];

    if(this->course == NULL) {
        return NULL;
    }

    if (this->course == row.course && this->day==row.day) {
        CDHRow* returner = this->next;
        this->next = (this->next)->next;
        if (debug) {
            printf("Successfully deleted row at hashtable index %i\n", index);
        }
        return returner;
    }

    while ((this->next) != NULL) {
            if ((strcmp(this->next->course, row.course) == 0) && (strcmp(this->next->day, row.day) == 0)) {

                CDHRow *returner = this->next;
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

