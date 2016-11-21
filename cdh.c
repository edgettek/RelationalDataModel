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

    if(lookupCDH(row, table, false) != NULL) {
        if(debug) {printf("Tuple (%s, %d, %s) already existed.\n", row.course, row.day, row.hour);}
        return;
    }
    else {

        while ((this->next) != NULL) {
            this = this->next;
        }

        CDHRow* newer = (CDHRow*) malloc(sizeof(CDHRow));

        if (this->course != NULL) {
            this->next = newer;
            this = newer;
        }


        memcpy(this, &row, sizeof(CDHRow));

        if (debug) {
            printf("Tuple (%s, %s, %s) in CDH was inserted at index %d.\n", row.course, row.day, row.hour, index);
        }
        return;

    }
}

CDHRow* lookupCDH(CDHRow row, CDHRow* table[], bool debug){
    int index = hashTwoStrings(row.course, 6, row.day, 6, TABLE_SIZE);

    CDHRow* this = table[index];

    if(this->course == NULL) {
        if(debug) {printf("Tuple (%s, %s, %s) in CDH was NOT found at index %d.\n", row.course, row.day, row.hour, index);}
        return NULL;
    }

    while ((this->next) != NULL) {
        if (strcmp(this->course, row.course) == 0 && strcmp(this->day, row.day) == 0 && strcmp(this->hour, row.hour) == 0){
            if (debug) {
                printf("Tuple (%s, %s, %s) in CDH was found at index %d.\n", row.course, row.day, row.hour, index);
            }
            return this;
        }
        this = this->next;
    }

    if(strcmp(this->course, row.course) == 0 && strcmp(this->day, row.day) == 0 && strcmp(this->hour, row.hour) == 0) {
        if (debug) {
            printf("Tuple (%s, %s, %s) in CDH was found at index %d.\n", row.course, row.day, row.hour, index);
        }
        return this;
    }


    if (this->course == row.course && this->day == row.day) {
        if (debug) {
            printf("Tuple (%s, %s, %s) in CDH was found at index %d.\n", row.course, row.day, row.hour, index);
        }
        return this;
    } else {
        if (debug) {
            printf("Tuple (%s, %s, %s) in CDH was NOT found at index %d.\n", row.course, row.day, row.hour, index);
        }
        return NULL;
    }
}

CDHRow* deleteCDH(CDHRow row, CDHRow* table[], bool debug){
    int index = hashTwoStrings(row.course, 6, row.day, 6, TABLE_SIZE);

    CDHRow* this = table[index];

    if(lookupCDH(row, table, false) == NULL) {
        printf("Tuple (%s, %s, %s) in CDH was NOT found/deleted at index %d.\n", row.course, row.day, row.hour, index);
        return NULL;
    }



    if(this->course == NULL) {
        printf("Tuple (%s, %s, %s) in CDH was deleted at index %d.\n", row.course, row.day, row.hour, index);
        return NULL;
    }

    if (this->course == row.course && this->day==row.day) {

        this->course = NULL;
        this->hour = NULL;
        this->day = NULL;

        if (debug) {
            printf("Tuple (%s, %s, %s) in CDH was deleted at index %d.\n", row.course, row.day, row.hour, index);
        }
        return this;
    }

    while ((this->next) != NULL) {
            if ((strcmp(this->next->course, row.course) == 0) && (strcmp(this->next->day, row.day) == 0)) {

                this->course = NULL;
                this->hour = NULL;
                this->day = NULL;
                if (debug) {
                    printf("Tuple (%s, %s, %s) in CDH was deleted at index %d.\n", row.course, row.day, row.hour, index);
                }
                return this;
            }
            else{
                this = this->next;
            }
    }

    if (debug) {
        printf("Tuple (%s, %s, %s) in CDH was NOT found/deleted at index %d.\n", row.course, row.day, row.hour, index);
    }
    return NULL;
}

void printCDHRelation(CDHRow* table[], bool debug) {

    FILE *CDHFile;

    CDHFile = fopen("CDH.txt", "w" );

    if (CDHFile == NULL)
    {
        perror("Error opening file!\n");
        exit(1);
    }

    CDHRow* currentRow;

    for(int i = 0; i < TABLE_SIZE; i++) {

        currentRow = table[i];

        if(currentRow->course != NULL) {

            fprintf(CDHFile, "%s\t%s\t%s\n", currentRow->course, currentRow->day, currentRow->hour);

            while (currentRow->next != NULL) {
                currentRow = currentRow->next;
                fprintf(CDHFile, "%s\t%s\n", currentRow->course, currentRow->day, currentRow->hour);

            }
        }

    }

    printf("CDH Relation has been printed to file!\n");

    fclose(CDHFile);

}

