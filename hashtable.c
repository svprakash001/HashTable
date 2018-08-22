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

        index = getHash(key,attempt++,table1->size);
        cur_item = table1->items[index];
    }

    table1->items[index] = newItem(key,value);

    table1->count++;

    //If load in the table > 0.65 its difficult to find an empty bucket to insert
    // Increase the size of table to avoid frequent collisions
    //0.65 is an arbitrary value

    float buckets_filled_ratio = table1->count/(float)table1->size;

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
        index = getHash(key,attempt++,table1->size);
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
        index = getHash(key,attempt++,table1->size);
        cur_item = table1->items[index];
    }

    table1->count--;

    //If load in the table < 0.15 we are wasting a lot of space
    // Decrease the size of table to avoid frequent collisions
    //0.15 is an arbitrary value
    float buckets_filled_ratio = table1->count/(float)table1->size;

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

    old_table->size = new_table->size;

    item** tmp = old_table->items;
    old_table->items = new_table->items;
    new_table->items = tmp;

    //Delete the old table
    deleteTable(new_table);
}

int main() {

    htable = newTable(100);

    printf("Welcome to PHash, a simple hash table >>>");

    while(1){

        int input;
        char key[32];
        char value[32];

        printf("Enter a choice\n");
        printf("\t1. Insert\n");
        printf("\t2. Search\n");
        printf("\t3. Delete\n");
        printf("\t0. Exit\n");

        scanf("%d",&input);

        switch (input)
        {
            case 0:
                printf("case 0");
                return 0;

            case 1:
                printf("Enter the key to insert\n");
                scanf("%s",key);
                printf("Enter the value\n");
                scanf("%s",value);

                insert(htable,key,value);
                printf("Inserted the key %s and value %s \n",key,value);
                break;

            case 2:
                printf("Enter the key to search\n");
                scanf("%s",key);

                item* item1 = search(htable,key);
                if(item1 == NULL){
                    printf("Key not found in hashtable \n");
                } else{
                    printf("Value for key %s is %s \n",key,item1->value);
                }
                break;

            case 3:
                printf("Enter the key to delete \n");
                scanf("%s",key);

                del(htable,key);
                printf("Deleted the key %s successfully \n",key);
                break;

            default:
                printf("Enter a value betweeen 0 and 3\n");
        }
    }

}
