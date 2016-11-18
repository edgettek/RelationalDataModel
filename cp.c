//
// Created by Manan hora on 11/15/16.
//

#include "attributes.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

void insertCP(CPRow row, CPRow* table[], bool debug){
    int index = hashOneString(row.course, 6, TABLE_SIZE);

    CPRow* this = table[index];

    while ((this->next) != NULL) {
        this = this->next;
    }

    CPRow* newer = (CPRow*) malloc(sizeof(CPRow));

    if (strcmp(this->course, "") != 0) {
        this->next = newer;
        this = newer;
    }

    memcpy(this, &row, sizeof(CPRow));

    if (debug) {
        printf("Successfully inserted new row at hashtable index %i\n", index);
    }
    return;
}

CPRow* lookupCP(CPRow row, CPRow* table[], bool debug){
    int index = hashOneString(row.course, 6, TABLE_SIZE);

    CPRow* this = table[index];
    while ((this->next) != NULL) {
        if (this->course == row.course){
            if (debug) {
                printf("Successfully found matching row at hashtable index %i\n", index);
            }
            return this;
        }
        this = this->next;
    }
    if (this->course == row.course) {
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

CPRow* deleteCP(CPRow row, CPRow* table[], bool debug){
    int index = hashOneString(row.course, 6, TABLE_SIZE);

    CPRow* this = table[index];

    if (this->course == row.course) {
        CPRow* returner = this->next;
        this->next = (this->next)->next;
        if (debug) {
            printf("Successfully deleted row at hashtable index %i\n", index);
        }
        return returner;
    }

    while ((this->next) != NULL) {
        if (strcmp((this->next)->course, row.course) == 0) {

            CPRow* returner = this->next;
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
