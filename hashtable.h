//
// Created by PRAKASH on 21-08-2018.
//

#ifndef HASHTABLE_HASHTABLE_H
#define HASHTABLE_HASHTABLE_H

table* newTable(int size);

item* newItem(char* key,char* value);

void deleteItem(item* item1);

void deleteTable(table* table1);

void insert(table* table1,char* key,char* value);

item* search(table* table1,char* key);

void del(table* table1,char* key);

void increaseSize(table* table1);

void decreaseSize(table* table1);

void resize(table* table1,int size);

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
