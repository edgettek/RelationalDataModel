#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

int TABLE_SIZE = 1009;

typedef struct CSGrow {
	char Course[6]; // These two rows combine
	int StudentId;	// to make the primary key
	char Grade[3];
	struct CSGrow* next;
} CSGrow;

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

int hash(char courseTitle[], int strSize, int id, int hashPrime) {

	char* start = &courseTitle[0];
	int stringPart = stringToInt(start, strSize);

	int returner = (id + stringPart) % hashPrime;
	return returner;
}

void insert(CSGrow row, CSGrow* table[], bool debug) {
	int index = hash(row.Course, 6, row.StudentId, TABLE_SIZE);

	CSGrow* this = table[index];
	while ((this->next) != NULL) {
		this = this->next;
	}

	CSGrow* newer = (CSGrow*) malloc(sizeof(CSGrow));
	this->next = newer;
	this = newer;

	memcpy(this, &row, sizeof(CSGrow));

	if (debug) {
		printf("Successfully inserted new row at hashtable index %i\n", index);
	}
	return;
}

CSGrow* lookup(CSGrow row, CSGrow* table[], bool debug) {
	int index = hash(row.Course, 6, row.StudentId, TABLE_SIZE);

	CSGrow* this = table[index];
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

CSGrow* delete(CSGrow row, CSGrow* table[], bool debug) {
	int index = hash(row.Course, 6, row.StudentId, TABLE_SIZE);

	CSGrow* this = table[index];

	if (this->Course == row.Course && this->StudentId == row.StudentId && this->Grade == row.Grade) {
		CSGrow* returner = this->next;
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
			
			CSGrow* returner = this->next;
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

int main(int argc, char const *argv[])
{
	CSGrow* CSGtable[TABLE_SIZE];
	for (int i = 0; i < TABLE_SIZE; i++) {
		CSGtable[i] = (CSGrow*) malloc(sizeof(CSGrow));
	}
	CSGrow test;
	strcpy(test.Course, "CS101");
	test.StudentId = 12345;
	strcpy(test.Grade, "A+");
	for (int i = 0; i < 3; i++) {
		insert(test, CSGtable, true);
	}
	CSGrow* lookedup = lookup(test, CSGtable, true);
	for (int i = 0; i < 6; i++) {
		CSGrow* returned = delete(test, CSGtable, true);
	}
	return 0;
}










