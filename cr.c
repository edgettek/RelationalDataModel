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

    if(lookupCR(row, table, false) != NULL) {
        if(debug) {printf("Tuple (%s, %s) in CR already existed at index %d.\n", row.course, row.room, index);}
        return;
    }
    else {

        CRRow *this = table[index];


        while ((this->next) != NULL) {
            this = this->next;
        }

        CRRow *newer = (CRRow *) malloc(sizeof(CRRow));
        if (this->course != NULL) {
            this->next = newer;
            this = newer;
        }


        memcpy(this, &row, sizeof(CRRow));

        if (debug) {
            printf("Tuple (%s, %s) in CR was inserted at index %d.\n", row.course, row.room, index);
        }
        return;
    }
}

CRRow* lookupCR(CRRow row, CRRow* table[], bool debug){
    int index = hashOneString(row.course, 6, TABLE_SIZE);

    CRRow* this = table[index];

    if(this->course == NULL) {
        printf("Tuple (%s, %s) in CR was NOT found at index %d.\n", row.course, row.room, index);
        return NULL;
    }

    while ((this->next) != NULL) {
        if (strcmp(this->course, row.course) == 0 && strcmp(this->room, row.room) == 0){
            if (debug) {
                printf("Tuple (%s, %s) in CR was found at index %d.\n", row.course, row.room, index);
            }
            return this;
        }
        this = this->next;
    }

    if(strcmp(this->course, row.course) == 0 && strcmp(this->room, row.room) == 0) {
        if (debug) {
            printf("Tuple (%s, %s) in CR was found at index %d.\n", row.course, row.room, index);
        }
        return this;
    }


    if (this->course == row.course && this->room == row.room) {
        if (debug) {
            printf("Tuple (%s, %s) in CR was found at index %d.\n", row.course, row.room, index);
        }
        return this;
    } else {
        if (debug) {
            printf("Tuple (%s, %s) in CR was NOT found at index %d.\n", row.course, row.room, index);
        }
        return NULL;
    }
}

CRRow* deleteCR(CRRow row, CRRow* table[], bool debug){
    int index = hashOneString(row.course, 6, TABLE_SIZE);

    CRRow* this = table[index];

    if(lookupCR(row, table, false) == NULL) {
        printf("Tuple (%s, %s) in CR was NOT found or deleted at index %d.\n", row.course, row.room, index);
        return NULL;
    }

    if(this->course == NULL) {
        return NULL;
    }

    if (this->course == row.course && this->room==row.room) {

        this->course = NULL;
        this->room = NULL;

        if (debug) {
            printf("Tuple (%s, %s) in CR was deleted at index %d.\n", row.course, row.room, index);
        }
        return this;
    }

    while ((this->next) != NULL) {
        if ((strcmp(this->next->course, row.course) == 0) && (strcmp(this->next->room, row.room) == 0)) {

            CRRow *returner = this->next;
            this->next = (this->next)->next;
            if (debug) {
                printf("Tuple (%s, %s) in CR was deleted at index %d.\n", row.course, row.room, index);
            }
            return returner;
        }
        else{
            this = this->next;
        }
    }

    if (debug) {
        printf("Tuple (%s, %s) in CR was NOT found or deleted at index %d.\n", row.course, row.room, index);
    }
    return NULL;
}

void printCRRelation(CRRow* table[], bool debug) {

    FILE *CRFile;

    CRFile = fopen("CR.txt", "w" );

    if (CRFile == NULL)
    {
        perror("Error opening file!\n");
        exit(1);
    }

    CRRow* currentRow;

    for(int i = 0; i < TABLE_SIZE; i++) {

        currentRow = table[i];

        if(currentRow->course != NULL) {

            fprintf(CRFile, "%s\t%s\n", currentRow->course, currentRow->room);

            while (currentRow->next != NULL) {
                currentRow = currentRow->next;
                fprintf(CRFile, "%s\t%s\n", currentRow->course, currentRow->room);

            }
        }

    }

    printf("CR Relation has been printed to file!\n");

    fclose(CRFile);

}