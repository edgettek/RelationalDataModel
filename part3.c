//
// Created by Manan hora on 11/19/16.
//

#include "attributes.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

SNAPRow* getSNAPByName(char* name, SNAPRow* table[]){
    for(int i = 0; i<TABLE_SIZE; i++){
        while(table[i]->next!=NULL){
            SNAPRow* thisRow = table[i];
            if(thisRow->name == name){
                return thisRow;
            }
            thisRow = thisRow->next;
        }
    }
    return NULL;
}