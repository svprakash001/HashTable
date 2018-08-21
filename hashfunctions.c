//
// Created by PRAKASH on 21-08-2018.
//
#include <string.h>
#include "hashtable.h"
#include "hashfunctions.h"

int getHash(char* key,int attempt,int no_of_buckets){

    int a = hashFunc(key,11,no_of_buckets);
    int b = hashFunc(key,13,no_of_buckets);

    return (a + attempt*(b+1)) % no_of_buckets;
}

int hashFunc(char* key,int prime,int no_of_buckets){

    int len = strlen(key);
    long hashval = 0;

    for(int i=0;i<len;i++){
        hashval += (long) prime * i * key[i];
        hashval %= no_of_buckets;
    }
    return hashval%no_of_buckets;
}
