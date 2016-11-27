#include "attributes.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

C_S_G_Row* project(C_S_G_Row* table[], char* array_of_attributes[]) {

	int size = TABLE_SIZE;

	bool keepCourse = false;
	bool keepStudent = false;
	bool keepGrade = false;

	char* single_attribute = *array_of_attributes;

	while (*single_attribute != NULL) {

		if (strcmp(single_attribute, "Course") == 0) {
			keepCourse = true;
		} else if (strcmp(single_attribute, "Student") == 0) {
			keepStudent = true;
		} else if (strcmp(single_attribute, "Grade") == 0) {
			keepGrade = true;
		}

		*single_attribute++;
	}
    C_S_G_Row* tablePointer;
    C_S_G_Row* returner = malloc(1009 * sizeof(C_S_G_Row));

    for (int i = 0; i < TABLE_SIZE; i++) {
        returner[i].next = NULL;
    }
    C_S_G_Row* returnerPointer;

	for (int i = 0; i < 1009; ++i) {

		strcpy(returner[i].course, ((keepCourse) ? (table[i]->course) : ("")));
		returner[i].StudentId = ((keepStudent) ? (table[i]->StudentId) : (-1));
		strcpy(returner[i].grade, ((keepGrade) ? (table[i]->grade) : ("")));
	}

	return returner;

}

CRDHrow* join(CRRow* CRTable[], CDHRow* CDHTable[]) { 

	CRDHrow* returner = malloc(1009 * sizeof(CRDHrow));

	for (int i = 0; i < 1009; ++i) {

		CRDHrow* joinedRow = (CRDHrow*) malloc(sizeof(CRDHrow));
		joinedRow->course = (char*) malloc(7 * sizeof(char));
		joinedRow->day = (char*) malloc(2 * sizeof(char));
		joinedRow->hour = (char*) malloc(5 * sizeof(char));
		joinedRow->room = (char*) malloc(30 * sizeof(char));

		CDHRow* CDHRowPointer = CDHTable[i];

		if (CDHRowPointer->course == NULL) {
			returner[i] = *joinedRow;
			continue;
		}

		if (strcmp(CDHRowPointer->course, "") != 0) {

			CRRow* temp = (CRRow*) malloc(sizeof(CRRow));
			temp->course = (char*) malloc(7 * sizeof(char));

			char* courseName = CDHRowPointer->course;
			printf("Here\n");
			strcpy(temp->course, courseName);
			printf("Here\n");
			CRRow* possiblyFound = lookupCR(*temp, CRTable, false);

			printf("Here\n");

			while (possiblyFound != NULL) {

				printf("Here\n");

				joinedRow->course = CDHRowPointer->course;
				joinedRow->day = CDHRowPointer->day;
				joinedRow->hour = CDHRowPointer->hour;
				joinedRow->room = possiblyFound->room;

				possiblyFound = possiblyFound->next;

			}
		}

		returner[i] = *joinedRow;
	}

	return returner;
}





