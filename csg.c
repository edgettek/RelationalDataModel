
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

	if (strcmp(this->course, row.course) == 0 && this->StudentId == row.StudentId && strcmp(this->grade, row.grade) == 0) {

		if(this->next == NULL) {
			strcpy(this->grade, "");
			strcpy(this->course, "");
			this->StudentId = 0;
			printf("Tuple (%s, %d, %s) in CSG was deleted at index %d.\n", row.course, row.StudentId, row.grade, index);
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

void printCSGToConsole(C_S_G_Row* table[], bool debug) {

	printf("Printing Out NEW CSG Table\n\n");

	C_S_G_Row* currentRow;

	for(int i = 0; i < TABLE_SIZE; i++) {

		currentRow = table[i];

		if(strcmp(currentRow->grade, "") != 0) {

			printf("%s\t%d\t%s\n", currentRow->course, currentRow->StudentId, currentRow->grade);

			while (currentRow->next != NULL) {
				currentRow = currentRow->next;
				printf("%s\t%d\t%s\n", currentRow->course, currentRow->StudentId, currentRow->grade);

			}
		}

	}

	printf("\n");

}


void readFromFileCSG(C_S_G_Row* table[], char* fileName, bool debug) {

	printf("\nReading new CSG Table from File\n");

	FILE *CSGFile;

	char buff[255];
	char buff2[255];
	int i = 0;

	CSGFile = fopen(fileName, "r" );

	if (CSGFile == NULL)
	{
		perror("Error opening file!\n");
		exit(1);
	}
	C_S_G_Row toFill;

	while (!feof (CSGFile)) {
		fscanf(CSGFile, "%s", buff);
		fscanf(CSGFile, "%d", &i);
		fscanf(CSGFile, "%s", buff2);


		strcpy(toFill.course, buff);
		toFill.StudentId = i;
		strcpy(toFill.grade, buff2);

		insertCSG(toFill, table, false);
	}

	fclose(CSGFile);

	return;

}




