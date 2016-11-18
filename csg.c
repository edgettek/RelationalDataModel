
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


	if (strcmp(this->Course, row.Course) == 0 && this->StudentId == row.StudentId && strcmp(this->Grade, row.Grade) == 0) {
		if (debug) {
			printf("Successfully found matching row at hashtable index %i\n", index);
		}
		return this;

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

void insertCSG(C_S_G_Row row, C_S_G_Row* table[], bool debug) {
	int index = hashIntAndString(row.Course, 6, row.StudentId, TABLE_SIZE);

	if(lookupCSG(row, table, false) != NULL) {
		if(debug) {printf("That row already existed!\n");}
		return;
	}
	else {

		C_S_G_Row *this = table[index];
		while ((this->next) != NULL) {
			this = this->next;
		}

		C_S_G_Row *newer = (C_S_G_Row *) malloc(sizeof(C_S_G_Row));

		if (strcmp(this->Course, "") != 0) {
			this->next = newer;
			this = newer;
		}

		memcpy(this, &row, sizeof(C_S_G_Row));

		if (debug) {
			printf("Successfully inserted new row at hashtable index %i\n", index);
		}
		return;
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

	C_S_G_Row* current;

	for(int i = 0; i < TABLE_SIZE; i++) {
		current = CSGtable[i];

		printf("i == %d: Course == %s StudentID == %d Grade == %s\n", i, current->Course, current->StudentId, current->Grade);
	}


	//printCSGRelation(CSGtable, true);

	C_S_G_Row* lookedup = lookupCSG(test, CSGtable, true);
	for (int i = 0; i < 6; i++) {
		C_S_G_Row* returned = deleteCSG(test, CSGtable, true);
	}



//	// 2) SNAP
//    SNAPRow* SNAPtable[TABLE_SIZE];
//    for (int i = 0; i < TABLE_SIZE; i++) {
//        SNAPtable[i] = (SNAPRow*) malloc(sizeof(SNAPRow));
//		SNAPtable[i]->name=NULL;
//		SNAPtable[i]->StudentId=NULL;
//		SNAPtable[i]->next = NULL;
//		SNAPtable[i]->address = NULL;
//		SNAPtable[i]->phone = NULL;
//    }
//    SNAPRow snapRow;
//	snapRow.name = "C. Brown";
//    snapRow.StudentId = 28890;
//    strcpy(snapRow.address, "12 Apple St.");
//	snapRow.phone = "555-1234";
//
//	insertSNAP(snapRow, SNAPtable, true);
//
//	SNAPRow row2;
//	row2.name = "Raina Langevin";
//	row2.StudentId = 12345;
//	strcpy(row2.address, "Burlington Street, Burlington, VT");
//	row2.phone = "555-3334";
//	for(int i = 0; i<2; i++){
//		insertSNAP(row2, SNAPtable, true);
//	}
//
//	SNAPRow* thisRow = lookupSNAP(snapRow, SNAPtable, true);
//	thisRow = lookupSNAP(row2, SNAPtable, true);
//	for (int i = 0; i < 6; i++) {
//		SNAPRow* returned = deleteSNAP(snapRow, SNAPtable, true);
//	}

	// 3) CP
//	CPRow* CPtable[TABLE_SIZE];
//
//	for(int i = 0;i<TABLE_SIZE; i++){
//		CPtable[i] = (CPRow*)malloc(sizeof(CPRow));
//		CPtable[i]->next = NULL;
//		CPtable[i]->course = NULL;
//		CPtable[i]->prereq = NULL;
//	}
//	CPRow cpRow;
//	cpRow.course = "CS101";
//	cpRow.prereq = "CS100";
//
//	insertCP(cpRow, CPtable, true);
//	CPRow cpRow2;
//	cpRow2.course = "EE200";
//	cpRow2.prereq = "EE005";
//
//	insertCP(cpRow2, CPtable, true);
//	CPRow* findCPRow1 = lookupCP(cpRow, CPtable, true);
//	CPRow* findCPRow2 = lookupCP(cpRow2, CPtable, true);
//
//	CPRow* deletedCP = deleteCP(cpRow, CPtable, true);
//
//	return 0;

	// 4) CDH
//	CDHRow* CDHTable[TABLE_SIZE];
//
//
//	for(int i = 0;i<TABLE_SIZE; i++){
//		CDHTable[i] = (CDHRow*)malloc(sizeof(CDHRow));
//		CDHTable[i]->next = NULL;
//		CDHTable[i]->course = NULL;
//		CDHTable[i]->day = NULL;
//		CDHTable[i]->hour = NULL;
//	}
//	CDHRow cdhRow;
//	cdhRow.course = "CS101";
//	cdhRow.day = "M";
//	cdhRow.hour = "9AM";
//
//	insertCDH(cdhRow, CDHTable, true);
//	CDHRow cdhRow1;
//	cdhRow1.course = "CSC101";
//	cdhRow1.day = "W";
//	cdhRow1.hour = "9AM";
//
//	insertCDH(cdhRow1, CDHTable, true);
//
//	CDHRow* current;
//
//	for(int i = 0; i < TABLE_SIZE; i++) {
//		current = CDHTable[i];
//
//		printf("i == %d: Course == %s Day == %s Hour == %s\n", i, current->course, current->day, current->hour);
//	}
//
//
//	CDHRow* findCDHRow1 = lookupCDH(cdhRow, CDHTable, true);
//	CDHRow* findCDHRow2 = lookupCDH(cdhRow1, CDHTable, true);
//
//	CDHRow* deletedCDH = deleteCDH(cdhRow, CDHTable, true);

	return 0;


	}



