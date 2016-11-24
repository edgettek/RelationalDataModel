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
        return "GRADE NOT FOUND";
    }
    int studentId = projectId(thisRow);
    C_S_G_Row* row = selectCSGByIdAndCourse(studentId, course, csgTable, false);
    char* grade = projectGrade(row);

    if(grade == NULL) {
        return "GRADE NOT FOUND";
    }

    return grade;
}

char* getRoom(char*name, char* time, char* day, C_S_G_Row* csgTable[], CRRow* crTable[], SNAPRow* snapTable[], CDHRow* cdhTable[]){
    SNAPRow* row = selectSNAPByName(name, snapTable);

    int studentId = projectId(row);

    C_S_G_Row* csgRow = selectCoursesById(csgTable, studentId);


    while(csgRow!=NULL){

        char* course = csgRow->course;

        CDHRow tempCDH;
        tempCDH.course = course;
        tempCDH.day = day;
        tempCDH.hour = time;
        tempCDH.next = NULL;


        CDHRow* cdhRow = lookupCDH(tempCDH, cdhTable, false);

        if(cdhRow != NULL){
            CRRow* crRow = selectCRByCourse(crTable, course);
            return crRow->room;
        }

        csgRow = csgRow->next;
    }
    return "NO ROOM FOUND";
}

