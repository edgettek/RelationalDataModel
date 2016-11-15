#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "attributes.h"

int TABLE_SIZE = 1009;

int stringToInt(char* string, int stringSize) {

	int step = sizeof(char);
	int returner = 0;

	for (int i = 0; i < stringSize; i++) {
		int adder = (int) string[0];
		returner += adder;
		string += step;
	}
	return returner;
}

int hashIntAndString(char courseTitle[], int strSize, int id, int hashPrime) {

	char* start = &courseTitle[0];
	int stringPart = stringToInt(start, strSize);

	int returner = (id + stringPart) % hashPrime;
	return returner;
}

int hashInt(int id, int hashPrime){
	int returner = (id)%hashPrime;
	return returner;
}

int hashTwoStrings(char str1[], int strSize1, char str2[],int strSize2, int hashPrime){
	char* start1 = &str1[0];
	int stringPartOne = stringToInt(start1, strSize1);

	char* start2 = &str2[0];
	int stringPartTwo = stringToInt(start2, strSize2);

	int returner = (stringPartOne + stringPartTwo)%hashPrime;
	return returner;

}

int hashOneString(char str[], int strSize, int hashPrime){
	char* start1 = &str[0];
	int stringPart = stringToInt(start1, strSize);
	int returner = (stringPart)%hashPrime;
	return returner;
}

void insertCSG(C_S_G_Row row, C_S_G_Row* table[], bool debug) {
	int index = hashIntAndString(row.Course, 6, row.StudentId, TABLE_SIZE);

	C_S_G_Row* this = table[index];
	while ((this->next) != NULL) {
		this = this->next;
	}

	C_S_G_Row* newer = (C_S_G_Row*) malloc(sizeof(C_S_G_Row));
	this->next = newer;
	this = newer;

	memcpy(this, &row, sizeof(C_S_G_Row));

	if (debug) {
		printf("Successfully inserted new row at hashtable index %i\n", index);
	}
	return;
}

C_S_G_Row* lookupCSG(C_S_G_Row row, C_S_G_Row* table[], bool debug) {
	int index = hashIntAndString(row.Course, 6, row.StudentId, TABLE_SIZE);

	C_S_G_Row* this = table[index];
	while ((this->next) != NULL) {
		if (strcmp(this->Course, row.Course) == 0 && 
			this->StudentId == row.StudentId && 
			strcmp(this->Grade, row.Grade) == 0) {
			if (debug) {
				printf("Successfully found matching row at hashtable index %i\n", index);
			}
			return this;
		}
		this = this->next;
	}
	if (this->Course == row.Course && this->StudentId == row.StudentId && this->Grade == row.Grade) {
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

C_S_G_Row* deleteCSG(C_S_G_Row row, C_S_G_Row* table[], bool debug) {
	int index = hashIntAndString(row.Course, 6, row.StudentId, TABLE_SIZE);

	C_S_G_Row* this = table[index];

	if (this->Course == row.Course && this->StudentId == row.StudentId && this->Grade == row.Grade) {
		C_S_G_Row* returner = this->next;
		this->next = (this->next)->next;
		if (debug) {
			printf("Successfully deleted row at hashtable index %i\n", index);
		}
		return returner;
	}

	while ((this->next) != NULL) {
		if (strcmp((this->next)->Course, row.Course) == 0 && 
			(this->next)->StudentId == row.StudentId && 
			strcmp((this->next)->Grade, row.Grade) == 0) {
			
			C_S_G_Row* returner = this->next;
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


void printCSGRelation(C_S_G_Row* table[], bool debug) {

	FILE *CSGFile;

    CSGFile = fopen("CSG.txt", "w" );

	if (CSGFile == NULL)
	{
		perror("Error opening file!\n");
		exit(1);
	}

	char* Course; // These two rows combine
	int StudentId;	// to make the primary key
	char* Grade;

	C_S_G_Row* currentRow;

	for(int i = 0; i < TABLE_SIZE; i++) {
            //printf("Going through table in print! i == %d\n", i);
		currentRow = table[i];

			Course = currentRow->Course;
			StudentId = currentRow->StudentId;
			Grade = currentRow->Grade;
                        //printf("%s\t%d\t%s\n", Course, StudentId, Grade);
			fprintf(CSGFile, "%s\t%d\t%s\n", Course, StudentId, Grade);

			while (currentRow->next != NULL) {
				currentRow = currentRow->next;

				Course = currentRow->Course;
				StudentId = currentRow->StudentId;
				Grade = currentRow->Grade;

                        }

	}
	fclose(CSGFile);

}

int main(int argc, char const *argv[])
{
	// 1) CSG
	C_S_G_Row* CSGtable[TABLE_SIZE];
	for (int i = 0; i < TABLE_SIZE; i++) {
		CSGtable[i] = (C_S_G_Row*) malloc(sizeof(C_S_G_Row));
		CSGtable[i]->next = NULL;
	}
	C_S_G_Row test;
	strcpy(test.Course, "CS101");
	test.StudentId = 12345;
	strcpy(test.Grade, "A+");
	for (int i = 0; i < 3; i++) {
		insertCSG(test, CSGtable, true);
	}
        
        printf("IN MAIN: at 553 Course: %s StudentID: %d Grade: %s\n", CSGtable[553]->Course, CSGtable[553]->StudentId, CSGtable[553]->Grade);

	printCSGRelation(CSGtable, true);

	C_S_G_Row* lookedup = lookupCSG(test, CSGtable, true);
	for (int i = 0; i < 6; i++) {
		C_S_G_Row* returned = deleteCSG(test, CSGtable, true);
	}



	// 2) SNAP
    SNAPRow* SNAPtable[TABLE_SIZE];
    for (int i = 0; i < TABLE_SIZE; i++) {
        SNAPtable[i] = (SNAPRow*) malloc(sizeof(SNAPRow));
    }
    SNAPRow snapRow;
	snapRow.name = "C. Brown";
    snapRow.StudentId = 12345;
    strcpy(snapRow.address, "12 Apple St.");
	snapRow.phone = "555-1234";

	for (int i = 0; i < 3; i++) {
		insertSNAP(snapRow, SNAPtable, true);
	}

	SNAPRow* thisRow = lookupSNAP(snapRow, SNAPtable, true);
	for (int i = 0; i < 6; i++) {
		SNAPRow* returned = deleteSNAP(snapRow, SNAPtable, true);
	}
	return 0;
}



