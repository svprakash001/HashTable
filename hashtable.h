//
// Created by PRAKASH on 21-08-2018.
//

#ifndef HASHTABLE_HASHTABLE_H
#define HASHTABLE_HASHTABLE_H

//Datastructure for an item
typedef struct{
    char* key;
    char* value;
}item;

//datastructure for the hash table
typedef struct{
    int size;
    int count;
    item** items;
}table;

#endif //HASHTABLE_HASHTABLE_H
