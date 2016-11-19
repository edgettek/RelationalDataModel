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
    int studentId = projectSId(thisRow);
    C_S_G_Row* row = selectCSGById(studentId, course, csgTable, true);
    char* grade = projectGrade(row);
    return grade;
}

