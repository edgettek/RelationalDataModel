//
// Created by Manan hora on 11/19/16.
//

#include "attributes.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

char* getGradeByName(char* name, char* course, SNAPRow* snapTable[], C_S_G_Row* csgTable[]){
    SNAPRow* thisRow = selectSNAPByName(name, snapTable);
    if(thisRow==NULL){
        printf("NOT FOUND\n");
        return NULL;
    }
    int studentId = projectId(thisRow);
    C_S_G_Row* row = selectCSGByIdAndCourse(studentId, course, csgTable, true);
    char* grade = projectGrade(row);
    return grade;
}

char* getRoom(char*name, char* time, char* day, C_S_G_Row* csgTable[], CRRow* crTable[], SNAPRow* snapTable[], CDHRow* cdhTable[]){
    SNAPRow* row = selectSNAPByName(name, snapTable);

    int studentId = projectId(row);

    C_S_G_Row* csgRow = selectCoursesById(csgTable, studentId);

    C_S_G_Row*tempRow;

    tempRow->next = csgRow;
    
    while(tempRow->next!=NULL){
        tempRow = tempRow->next;
        char* course = tempRow->course;
//        CDHRow* cdhRow = selectCDHByCourseAndDay(cdhTable, course, day);
//        if(cdhRow->hour==time){
//            CRRow* crRow = selectCRByCourse(crTable, course);
//            return crRow->room;
//        }
    }
    return NULL;
}

