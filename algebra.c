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

    C_S_G_Row* returner[TABLE_SIZE];
    for (int i = 0; i < TABLE_SIZE; i++) {
        returner[i] = (C_S_G_Row*) malloc(sizeof(C_S_G_Row));
        returner[i]->next = NULL;
    }
    C_S_G_Row* returnerPointer;

	for (int i = 0; i < 1009; ++i) {

		strcpy(returner[i]->course, ((keepCourse) ? (table[i]->course) : ("")));
		returner[i]->StudentId = ((keepStudent) ? (table[i]->StudentId) : (-1));
		strcpy(returner[i]->grade, ((keepGrade) ? (table[i]->grade) : ("")));
	}

	return returner;

}







