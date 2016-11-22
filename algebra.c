#include "attributes.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

C_S_G_Row** project(C_S_G_Row* table[], char* array_of_attributes[]) {

	int size = TABLE_SIZE;

	bool keepCourse = false;
	bool keepStudent = false;
	bool keepGrade = false;

	while (array_of_attributes != NULL) {

		char* single_attribute = *array_of_attributes;

		if (strcmp(single_attribute, "Course") == 0) {
			keepCourse = true;
		} else if (strcmp(single_attribute, "Student") == 0) {
			keepStudent = true;
		} else if (strcmp(single_attribute, "Grade") == 0) {
			keepGrade = true;
		}

		array_of_attributes++;
	}
    C_S_G_Row* tablePointer;

    C_S_G_Row* returner[TABLE_SIZE];
    for (int i = 0; i < TABLE_SIZE; i++) {
        returner[i] = (C_S_G_Row*) malloc(sizeof(C_S_G_Row));
        returner[i]->next = NULL;
    }
    C_S_G_Row* returnerPointer;

	tablePointer = table[0];
	returnerPointer = returner[0];
	while (tablePointer != NULL) {

		C_S_G_Row* newRow = returnerPointer;

		strcpy(newRow->course, ((keepCourse) ? (tablePointer->course) : ("")));
		strcpy(newRow->StudentId, ((keepStudent) ? (tablePointer->StudentId) : (-1)));
		strcpy(newRow->grade, ((keepGrade) ? (tablePointer->grade) : ("")));

		returnerPointer++;
		tablePointer++;
	}

	return returner;

}







