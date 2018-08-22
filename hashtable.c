//
// Created by PRAKASH on 20-08-2018.
//
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "hashtable.h"
#include "hashfunctions.h"

table* htable;

static item DELETED_ITEM = {NULL,NULL};

/**
 * Create a new hashtable based on struct 'table'
 * @param size of the hashtable
 * @return a new hashtable
 */
table* newTable(int size){

    table* t = malloc(sizeof(table));
    t->size = size;
    t->count = 0;
    t->items = calloc( (size_t)t->size, sizeof(item*));

    return t;
}

/**
 * Creates a new KV item
 * @param key
 * @param value
 * @return a new item with key and value filled
 */
item* newItem(char* key,char* value){

    item* i = malloc(sizeof(item));
    i->key = strdup(key);
    i->value = strdup(value);

    return i;
}

/**
 * Delete an item from hashtable
 * @param Ptr to item
 */
void deleteItem(item* i){

    if(i == NULL)
        return;

    free(i->key);
    free(i->value);
}

/**
 * Delete the entire hashtable and its contents.
 * Call deleteItem to delete all the items first and then free the hashtable data structure
 * @param Pointer to hashtable
 */
void deleteTable(table* t){

    if(t == NULL)
        return;

    for(int i=0;i<t->count;i++){

        if(t->items[i] != NULL){
            deleteItem(t->items[i]);
        }
    }

    free(t->items);
    free(t);
}

/**
 * Insert an item into hashtable
 * @param hashtable
 * @param key
 * @param value
 */
void insert(table* table1,char* key,char* value){


    int index = getHash(key,0,table1->size);  //Hash the key and get the index

    item* cur_item = table1->items[index];

    int attempt = 1;

    while(cur_item != NULL && cur_item != &DELETED_ITEM){

        index = getHash(cur_item,attempt++,table1->size);
        cur_item = table1->items[index];
    }

    cur_item = newItem(key,value);

    table1->count++;

    //If load in the table > 0.65 its difficult to find an empty bucket to insert
    // Increase the size of table to avoid frequent collisions
    //0.65 is an arbitrary value

    int buckets_filled_ratio = table1->size/table1->count;

    if(buckets_filled_ratio > 0.65){
        increaseSize(table1);
    }
}

item* search(table* table1,char* key){

    int index = getHash(key,0,table1->size);

    item* cur_item = table1->items[index];

    int attempt = 1;

    while(cur_item != NULL){

        if(cur_item != &DELETED_ITEM  && (strcmp(key,cur_item->key) == 0) ){

            return cur_item;
        }
        index = getHash(cur_item,attempt++,table1->size);
        cur_item = table1->items[index];
    }
    return NULL;
}

void del(table* table1,char* key){

    int index = getHash(key,0,table1->size);

    item* cur_item = table1->items[index];

    int attempt = 1;

    while(cur_item != NULL){

        if(strcmp(key,cur_item->key) == 0){

            deleteItem(cur_item);
            table1->items[index] = &DELETED_ITEM;
        }
        index = getHash(cur_item,attempt++,table1->size);
        cur_item = table1->items[index];
    }

    table1->count--;

    //If load in the table < 0.15 we are wasting a lot of space
    // Decrease the size of table to avoid frequent collisions
    //0.15 is an arbitrary value
    int buckets_filled_ratio = table1->size/table1->count;

    if(buckets_filled_ratio < 0.15){
        decreaseSize(table1);
    }
}

/**
 * Increase the size of hash table. New size = Prime number next to (old size * 2).
 * We choose Prime number as it helps in distributing the data evenly across the buckets
 */
void increaseSize(table* table1){

    int cur_size = table1->size;

    //Increase the table size by 2.
    int new_base_size = cur_size * 2;

    //Its better to have table size as a prime number. So, find the prime no next to new_base_size
    int new_size = next_prime(new_base_size);

    resize(table1,new_size);
}

/**
 * Decrease the size of hash table. New size = Prime number next to (old size / 2)
 * We choose Prime number as it helps in distributing the data evenly across the buckets
 */
void decreaseSize(table* table1){

    int cur_size = table1->size;
    //Increase the table size by 2.
    int new_base_size = cur_size / 2;
    //Its better to have table size as a prime number. So, find the prime no next to new_base_size
    int new_size = next_prime(new_base_size);

    resize(table1,new_size);
}

void resize(table* old_table,int size){

    table* new_table = newTable(size);

    new_table->size = size;
    new_table->count = 0;

    for(int i=0;i<old_table->count;i++){

        item* cur_item = old_table->items[i];

        if(cur_item != NULL && cur_item != &DELETED_ITEM){

            insert(new_table,cur_item->key,cur_item->value);
        }

    }

    //Make a reference to the old table
    table* tmp_table_ptr = old_table;

    //old_table ptr will now point to the new table. In this way, resizing is transparent to other functions
    //as the pointer variable is still the same and only the value of the ptr is changed (It now points to the new table instead of old one)
    old_table = new_table;

    //Delete the old table
    deleteTable(tmp_table_ptr);
}

int main() {

    htable = newTable(100);

    printf("Welocme to PHash, a simple hash table >>>");
    printf("Enter your choice\n");
    printf("\t1. Insert");
    printf("\t2. Search");
    printf("\t3. Delete");

    

    return 0;
}
