#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "attributes.h"

C_S_G_Row* project(C_S_G_Row* table, char** array_of_attributes) {

	int size = 0;
	C_S_G_Row* tempPointer = table;
	while (tempPointer != NULL) {
		size++;
		tempPointer++;
	}

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

	C_S_G_Row* returner = (C_S_G_Row*) malloc(size * sizeof(C_S_G_Row));

	tablePointer = table;
	returnerPointer = returner;
	while (tempPointer != NULL) {

		C_S_G_Row* newRow = returnerPointer;

		newRow->Course = (keepCourse) ? (tablePointer->Course) : ("No");
		newRow->Student = (keepStudent) ? (tablePointer->Student) : (-1);
		newRow->Grade = (keepGrade) ? (tablePointer->Grade) : ("No");

		returnerPointer++;
		tablePointer++;
	}

	return returner;

}







