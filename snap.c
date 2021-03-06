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
        if(debug) {printf("Tuple (%d, %s, %s, %s) in SNAP was already existed at index %d.\n", row.StudentId, row.name, row.address, row.phone, index);}
        return;
    }
    else {

        SNAPRow* this = table[index];

        while ((this->next) != NULL) {
            this = this->next;
        }

        SNAPRow *newer = (SNAPRow *) malloc(sizeof(SNAPRow));

        if (this->name != NULL) {
            this->next = newer;
            this = newer;
        }

        memcpy(this, &row, sizeof(SNAPRow));

        SNAPRow* temp = table[index];

        if (debug) {
            printf("Tuple (%d, %s, %s, %s) in SNAP was inserted at index %d.\n", row.StudentId, row.name, row.address, row.phone, index);
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
        if (this->StudentId == row.StudentId && strcmp(this->name, row.name) == 0 && strcmp(this->address, row.address) == 0 && strcmp(this->phone, row.phone) == 0){
            if (debug) {
                printf("Tuple (%d, %s, %s, %s) in SNAP was found at index %d.\n", row.StudentId, row.name, row.address, row.phone, index);
            }
            return this;
        }
        this = this->next;
    }



    if(this->StudentId == row.StudentId && strcmp(this->name, row.name) == 0 && strcmp(this->address, row.address) == 0 && strcmp(this->phone, row.phone) == 0) {
        if (debug) {
            printf("Tuple (%d, %s, %s, %s) in SNAP was found at index %d.\n", row.StudentId, row.name, row.address, row.phone, index);
        }
        return this;
    }

    if (this->StudentId == row.StudentId) {
        if (debug) {
            printf("Tuple (%d, %s, %s, %s) in SNAP was found at index %d.\n", row.StudentId, row.name, row.address, row.phone, index);
        }
        return this;
    } else {
        if (debug) {
            printf("Tuple (%d, %s, %s, %s) in SNAP was NOT found at index %d.\n", row.StudentId, row.name, row.address, row.phone, index);
        }
        return NULL;
    }
}

SNAPRow* deleteSNAP(SNAPRow row, SNAPRow* table[], bool debug){
    int index = hashInt(row.StudentId, TABLE_SIZE);

    if(lookupSNAP(row, table, false) == NULL) {
        printf("Tuple (%d, %s, %s, %s) in SNAP was NOT deleted/found at index %d.\n", row.StudentId, row.name, row.address, row.phone, index);
        return NULL;
    }

    SNAPRow* this = table[index];

    if(this->name == NULL) {
        return NULL;
    }

    if (this->StudentId == row.StudentId) {

        this->StudentId=0;
        this->name = NULL;
        this->address = NULL;
        this->phone = NULL;

        if (debug) {
            printf("Tuple (%d, %s, %s, %s) in SNAP was deleted at index %d.\n", row.StudentId, row.name, row.address, row.phone, index);
        }
        return this;
    }

    while ((this->next) != NULL && (this->next)) {
        if ((this->next)->StudentId == row.StudentId){

            SNAPRow* returner = this->next;
            if (debug) {
                printf("Tuple (%d, %s, %s, %s) in SNAP was deleted at index %d.\n", row.StudentId, row.name, row.address, row.phone, index);
            }
            return returner;
        }
        this = this->next;
    }
    if (debug) {
        printf("Tuple (%d, %s, %s, %s) in SNAP was NOT deleted/found at index %d.\n", row.StudentId, row.name, row.address, row.phone, index);
    }
    return NULL;
}

void printSNAPRelation(SNAPRow* table[], bool debug) {

    FILE *SNAPFile;

    SNAPFile = fopen("SNAP.txt", "w" );

    if (SNAPFile == NULL)
    {
        perror("Error opening file!\n");
        exit(1);
    }

    SNAPRow* currentRow;

    for(int i = 0; i < TABLE_SIZE; i++) {

        currentRow = table[i];

        if(currentRow->StudentId != 0) {

            fprintf(SNAPFile, "%d\t%s\t%s\t%s\n", currentRow->StudentId, currentRow->name, currentRow->address, currentRow->phone);

            while (currentRow->next != NULL) {
                currentRow = currentRow->next;
                fprintf(SNAPFile, "%d\t%s\t%s\t%s\n", currentRow->StudentId, currentRow->name, currentRow->address, currentRow->phone);

            }
        }

    }

    printf("SNAP Relation has been printed to file!\n");

    fclose(SNAPFile);

}

void readFromFileSNAP(SNAPRow* table[], char* fileName, bool debug) {

    printf("\nReading new SNAP Table from File\n");

    FILE *SNAPFile;

    int i = 0;
    char buff2[255];
    char buff3[255];
    char buff4[255];

    SNAPFile = fopen(fileName, "r" );

    if (SNAPFile == NULL)
    {
        perror("Error opening file!\n");
        exit(1);
    }
    SNAPRow toFill;


    while (!feof (SNAPFile)) {
        fscanf(SNAPFile, "%d\t%[^\t]\t%[^\t]\t%[^\t]", &i, buff2, buff3, buff4);
        toFill.name = (char*) malloc(sizeof(char) * 255);
        toFill.address = (char*) malloc(sizeof(char) * 255);
        toFill.phone = (char*) malloc(sizeof(char) * 255);

        toFill.StudentId = i;
        strcpy(toFill.name, buff2);
        strcpy(toFill.address, buff3);
        strcpy(toFill.phone, buff4);

        insertSNAP(toFill, table, false);
    }

    fclose(SNAPFile);

    return;

}

void printSNAPToConsole(SNAPRow* table[], bool debug) {

    printf("Printing Out NEW SNAP Table\n\n");

    SNAPRow* currentRow;

    for(int i = 0; i < TABLE_SIZE; i++) {

        currentRow = table[i];

        if(currentRow->name != NULL) {

            printf("%d\t%s\t%s\t%s\n", currentRow->StudentId, currentRow->name, currentRow->address, currentRow->phone);

            while (currentRow->next != NULL) {
                currentRow = currentRow->next;
                printf("%d\t%s\t%s\t%s\n", currentRow->StudentId, currentRow->name, currentRow->address, currentRow->phone);
            }
        }

    }

    printf("\n");

}