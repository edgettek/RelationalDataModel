
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
	int index = hashIntAndString(row.course, 6, row.StudentId, TABLE_SIZE);
	C_S_G_Row* this = table[index];

	if(this->course == NULL) {
		return NULL;
	}


	while ((this->next) != NULL) {
		if (strcmp(this->course, row.course) == 0 &&
			this->StudentId == row.StudentId &&
			strcmp(this->grade, row.grade) == 0) {
			if (debug) {
				printf("Tuple (%s, %d, %s) in CSG was found at index %d.\n", row.course, row.StudentId, row.grade, index);
			}
			return this;
		}
		this = this->next;
	}

	if (strcmp(this->course, row.course) == 0 && this->StudentId == row.StudentId && strcmp(this->grade, row.grade) == 0) {
		if (debug) {
			printf("Tuple (%s, %d, %s) in CSG was found at index %d.\n", row.course, row.StudentId, row.grade, index);
		}
		return this;

	}

	if (this->course == row.course && this->StudentId == row.StudentId && this->grade == row.grade) {
		if (debug) {
			printf("Tuple (%s, %d, %s) in CSG was found at index %d.\n", row.course, row.StudentId, row.grade, index);
		}
		return this;
	} else {
		if (debug) {
			if(debug) {printf("Tuple (%s, %d, %s) in CSG could not be found at index %d.\n", row.course, row.StudentId, row.grade, index);}
		}
		return NULL;
	}
}

void insertCSG(C_S_G_Row row, C_S_G_Row* table[], bool debug) {
	int index = hashIntAndString(row.course, 6, row.StudentId, TABLE_SIZE);

	if(lookupCSG(row, table, false) != NULL) {
		if(debug) {printf("Tuple (%s, %d, %s) already existed.\n", row.course, row.StudentId, row.grade);}
		return;
	}
	else {

		C_S_G_Row *this = table[index];
		while ((this->next) != NULL) {
			this = this->next;
		}

		C_S_G_Row *newer = (C_S_G_Row *) malloc(sizeof(C_S_G_Row));

		if (this->course == NULL) {
			this->next = newer;
			this = newer;
		}

		memcpy(this, &row, sizeof(C_S_G_Row));

		if (debug) {
			if(debug) {printf("Tuple (%s, %d, %s) has been inserted in CSG.\n", row.course, row.StudentId, row.grade);}
		}
		return;
	}
}

C_S_G_Row* deleteCSG(C_S_G_Row row, C_S_G_Row* table[], bool debug) {
	int index = hashIntAndString(row.course, 6, row.StudentId, TABLE_SIZE);

	if(lookupCSG(row, table, false) == NULL) {
		printf("Tuple (%s, %d, %s) in CSG was was not deleted/found at index %d.\n", row.course, row.StudentId, row.grade, index);
		return NULL;
	}

	C_S_G_Row* this = table[index];

	if(this->course == NULL) {
		return NULL;
	}

	if (strcmp(this->course, row.course) == 0 && this->StudentId == row.StudentId && strcmp(this->grade, row.grade) == 0) {

		if(this->next == NULL) {
			strcpy(this->grade, "");
			strcpy(this->course, "");
			this->StudentId = 0;

			return this;
		}

		C_S_G_Row* returner = this->next;
		this->next = (this->next)->next;
		if (debug) {
			printf("Tuple (%s, %d, %s) in CSG was deleted at index %d.\n", row.course, row.StudentId, row.grade, index);
		}
		return returner;
	}

	while ((this->next) != NULL) {
		if (strcmp((this->next)->course, row.course) == 0 &&
			(this->next)->StudentId == row.StudentId &&
			strcmp((this->next)->grade, row.grade) == 0) {

			C_S_G_Row* returner = this->next;
			this->next = (this->next)->next;
			if (debug) {
				printf("Tuple (%s, %d, %s) in CSG was deleted at index %d.\n", row.course, row.StudentId, row.grade, index);
			}
			return returner;
		}
		this = this->next;
	}
	if (debug) {
		printf("Tuple (%s, %d, %s) in CSG was was not found at index %d.\n", row.course, row.StudentId, row.grade, index);
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

	C_S_G_Row* currentRow;

	for(int i = 0; i < TABLE_SIZE; i++) {

		currentRow = table[i];

		if(strcmp(currentRow->grade, "") != 0) {

		fprintf(CSGFile, "%s\t%d\t%s\n", currentRow->course, currentRow->StudentId, currentRow->grade);

			while (currentRow->next != NULL) {
				currentRow = currentRow->next;
				fprintf(CSGFile, "%s\t%d\t%s\n", currentRow->course, currentRow->StudentId, currentRow->grade);

			}
		}

	}

	printf("CSG Relation has been printed to file!\n");

	fclose(CSGFile);

}

int main(int argc, char const *argv[])
{

	printf("\n\t *** TESTING CSG *** \n\n");

    // Initialize table
	C_S_G_Row* CSGtable[TABLE_SIZE];
	for (int i = 0; i < TABLE_SIZE; i++) {
		CSGtable[i] = (C_S_G_Row*) malloc(sizeof(C_S_G_Row));
		CSGtable[i]->next = NULL;
	}

	// Inserting tuples into CSG Relation
	C_S_G_Row toFill;

	strcpy(toFill.course, "CS101");
	toFill.StudentId = 12345;
	strcpy(toFill.grade, "B");
	insertCSG(toFill, CSGtable, true);
	insertCSG(toFill, CSGtable, true);
	insertCSG(toFill, CSGtable, true);

	strcpy(toFill.course, "CS101");
	toFill.StudentId = 67890;
	strcpy(toFill.grade, "B");
	insertCSG(toFill, CSGtable, true);

	strcpy(toFill.course, "EE200");
	toFill.StudentId = 12345;
	strcpy(toFill.grade, "C");
	insertCSG(toFill, CSGtable, true);

	strcpy(toFill.course, "EE200");
	toFill.StudentId = 22222;
	strcpy(toFill.grade, "B+");
	insertCSG(toFill, CSGtable, true);

	strcpy(toFill.course, "CS101");
	toFill.StudentId = 33333;
	strcpy(toFill.grade, "A-");
	insertCSG(toFill, CSGtable, true);

	strcpy(toFill.course, "PH100");
	toFill.StudentId = 67890;
	strcpy(toFill.grade, "C+");
	insertCSG(toFill, CSGtable, true);

	// Printing relation to file
	printCSGRelation(CSGtable, true);


	C_S_G_Row* lookedup = lookupCSG(toFill, CSGtable, true);
	for (int i = 0; i < 6; i++) {
		C_S_G_Row* returned = deleteCSG(toFill, CSGtable, true);
	}

	printf("\n\t *** TESTING SNAP *** \n\n");

    SNAPRow* SNAPtable[TABLE_SIZE];
    for (int i = 0; i < TABLE_SIZE; i++) {
        SNAPtable[i] = (SNAPRow*) malloc(sizeof(SNAPRow));
		SNAPtable[i]->name=NULL;
		SNAPtable[i]->StudentId = 0;
		SNAPtable[i]->next = NULL;
		SNAPtable[i]->address = NULL;
		SNAPtable[i]->phone = NULL;
    }
    SNAPRow snapRow;
	snapRow.name = "C.Brown";
    snapRow.StudentId = 12345;
	snapRow.address = "12 Apple St.";
	snapRow.phone = "555-1234";
	snapRow.next = NULL;

	insertSNAP(snapRow, SNAPtable, true);

	SNAPRow row2;
	row2.name = "Raina Langevin";
	row2.StudentId = 12335;
	row2.address = "Burlington Street, Burlington, VT";
	row2.phone = "555-3334";
	row2.next = NULL;

	for(int i = 0; i<2; i++){
		insertSNAP(row2, SNAPtable, true);
	}

	SNAPRow* thisRow = lookupSNAP(snapRow, SNAPtable, true);
	thisRow = lookupSNAP(row2, SNAPtable, true);
//	for (int i = 0; i < 6; i++) {
//		SNAPRow* returned = deleteSNAP(snapRow, SNAPtable, true);
//	}


	printf("\n\t *** TESTING CP *** \n\n");
	 //3) CP
	CPRow* CPtable[TABLE_SIZE];

	for(int i = 0;i<TABLE_SIZE; i++){
		CPtable[i] = (CPRow*)malloc(sizeof(CPRow));
		CPtable[i]->next = NULL;
		CPtable[i]->course = NULL;
		CPtable[i]->prereq = NULL;
	}
	CPRow cpRow;
	cpRow.course = "CS101";
	cpRow.prereq = "CS100";

	insertCP(cpRow, CPtable, true);
	CPRow cpRow2;
	cpRow2.course = "EE200";
	cpRow2.prereq = "EE005";

	insertCP(cpRow2, CPtable, true);
	CPRow* findCPRow1 = lookupCP(cpRow, CPtable, true);
	CPRow* findCPRow2 = lookupCP(cpRow2, CPtable, true);

	CPRow* deletedCP = deleteCP(cpRow, CPtable, true);


	 //4) CDH

	printf("\n\t *** TESTING CDH *** \n\n");

	CDHRow* CDHTable[TABLE_SIZE];


	for(int i = 0;i<TABLE_SIZE; i++){
		CDHTable[i] = (CDHRow*)malloc(sizeof(CDHRow));
		CDHTable[i]->next = NULL;
		CDHTable[i]->course = NULL;
		CDHTable[i]->day = NULL;
		CDHTable[i]->hour = NULL;
	}
	CDHRow cdhRow;
	cdhRow.course = "CS101";
	cdhRow.day = "M";
	cdhRow.hour = "9AM";

	insertCDH(cdhRow, CDHTable, true);
	CDHRow cdhRow1;
	cdhRow1.course = "CSC101";
	cdhRow1.day = "W";
	cdhRow1.hour = "9AM";

	insertCDH(cdhRow1, CDHTable, true);

	printf("\n\t *** TESTING CR *** \n\n");

	return 0;


	//PART 2 TEST
	char* grade = getGradeByName("C.Brown", "CS101", SNAPtable, CSGtable);
	printf("grade: %s ", grade);

}


