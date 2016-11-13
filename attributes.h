//
// Created by Kyle Edgette on 11/13/16.
//

#ifndef RELATIONALDATAMODEL_ATTRIBUTES_H
#define RELATIONALDATAMODEL_ATTRIBUTES_H


typedef struct C_S_G_Row{
    char Course[6]; // These two rows combine
    int StudentId;	// to make the primary key
    char Grade[3];
    struct C_S_G_Row* next;
} C_S_G_Row;



#endif //RELATIONALDATAMODEL_ATTRIBUTES_H
