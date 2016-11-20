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

    if(lookupCP(row, table, false) != NULL) {
        if(debug) {printf("Tuple (%s, %s) in CP already existed at index %d.\n", row.course, row.prereq, index);}
        return;
    }
    else {

        CPRow *this = table[index];

        while ((this->next) != NULL) {
            this = this->next;
        }

        CPRow *newer = (CPRow *) malloc(sizeof(CPRow));

        if (this->course != NULL) {
            this->next = newer;
            this = newer;
        }

        memcpy(this, &row, sizeof(CPRow));

        if (debug) {
            printf("Tuple (%s, %s) in CP was inserted at index %d.\n", row.course, row.prereq, index);
        }
        return;
    }
}

CPRow* lookupCP(CPRow row, CPRow* table[], bool debug){
    int index = hashOneString(row.course, 6, TABLE_SIZE);


    CPRow* this = table[index];

    if(this->course == NULL) {
        return NULL;
    }


    while ((this->next) != NULL) {
        if (strcmp(this->course, row.course) == 0 && strcmp(this->prereq, row.prereq) == 0){
            if (debug) {
                printf("Tuple (%s, %s) in CP was found at index %d.\n", row.course, row.prereq, index);
            }
            return this;
        }
        this = this->next;
    }

    if(strcmp(this->course, row.course) == 0 && strcmp(this->prereq, row.prereq) == 0) {
        if (debug) {
            printf("Tuple (%s, %s) in CP was found at index %d.\n", row.course, row.prereq, index);
        }
        return this;
    }

    return NULL;

//
//    if (this->course == row.course) {
//        if (debug) {
//            printf("Tuple (%s, %s) in CP was found at index %d.\n", row.course, row.prereq, index);
//        }
//        return this;
//    } else {
//        if (debug) {
//            printf("Tuple (%s, %s) in CP was NOT found at index %d.\n", row.course, row.prereq, index);
//        }
//        return NULL;
//    }
}

CPRow* deleteCP(CPRow row, CPRow* table[], bool debug){
    int index = hashOneString(row.course, 6, TABLE_SIZE);

    CPRow* this = table[index];

    if(lookupCP(row, table, false) == NULL) {
        printf("Tuple (%s, %s) in CP was NOT deleted/found at index %d.\n", row.course, row.prereq, index);
        return NULL;
    }

    if(this->course == NULL) {
        return NULL;
    }

    if (this->course == row.course) {

        this->course = NULL;
        this->prereq = NULL;

        if (debug) {
            printf("Tuple (%s, %s) in CP was deleted at index %d.\n", row.course, row.prereq, index);
        }
        return this;
    }

    while ((this->next) != NULL) {
        if (strcmp((this->next)->course, row.course) == 0) {

            CPRow* returner = this->next;
            this->next = (this->next)->next;
            if (debug) {
                printf("Tuple (%s, %s) in CP was deleted at index %d.\n", row.course, row.prereq, index);
            }
            return returner;
        }
        this = this->next;
    }
    if (debug) {
        printf("Tuple (%s, %s) in CP was NOT deleted/found at index %d.\n", row.course, row.prereq, index);
    }
    return NULL;
}

void printCPRelation(CPRow* table[], bool debug) {

    FILE *CPFile;

    CPFile = fopen("CP.txt", "w" );

    if (CPFile == NULL)
    {
        perror("Error opening file!\n");
        exit(1);
    }

    CPRow* currentRow;

    for(int i = 0; i < TABLE_SIZE; i++) {

        currentRow = table[i];

        if(currentRow->course != NULL) {

            fprintf(CPFile, "%s\t%s\n", currentRow->course, currentRow->prereq);

            while (currentRow->next != NULL) {
                currentRow = currentRow->next;
                fprintf(CPFile, "%s\t%s\n", currentRow->course, currentRow->prereq);

            }
        }

    }

    printf("CP Relation has been printed to file!\n");

    fclose(CPFile);

}
