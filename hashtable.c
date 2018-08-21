#include <stdio.h>
#include <string.h>
#include "hashtable.h"

table* htable;

static item DELETED_ITEM = {NULL,NULL};

/**
 * Create a new hashtable based on struct 'table'
 * @param size of the hashtable
 * @return a new hashtable
 */
static table* newTable(int size){

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

void deleteItem(item* i){

    if(item == NULL)
        return;

    free(i->key);
    free(i->value);
}

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

void insert(char* key,char* value){

    int index = getHash(key,0);

    item* cur_item = htable->items[index];

    int attempt = 1;

    while(cur_item != NULL && cur_item != &DELETED_ITEM){

        index = getHash(cur_item,attempt++);
        cur_item = htable->items[index];
    }

    cur_item = newItem(key,value);

    htable->count++;
}

item* search(char* key){

    int index = getHash(key,0);

    item* cur_item = htable->items[index];

    int attempt = 1;

    while(cur_item != NULL){

        if(cur_item != &DELETED_ITEM  && (strcmp(key,cur_item->key) == 0) ){

            return cur_item;
        }
        index = getHash(cur_item,attempt++);
        cur_item = htable->items[index];
    }
    return NULL;
}

void del(char* key){

    int index = getHash(key,0);

    item* cur_item = htable->items[index];

    int attempt = 1;

    while(cur_item != NULL){

        if(strcmp(key,cur_item->key) == 0){

            deleteItem(cur_item);
            htable->items[index] = &DELETED_ITEM;
        }
        index = getHash(cur_item,attempt++);
        cur_item = htable->items[index];
    }

    htable->count--;
}

int main() {

    htable = newTable(100);

    return 0;
}