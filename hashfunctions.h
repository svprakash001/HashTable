//
// Created by PRAKASH on 21-08-2018.
//

#ifndef HASHTABLE_HASHFUNCTIONS_H
#define HASHTABLE_HASHFUNCTIONS_H

int getHash(char* key,int attempt,int no_of_buckets);

int hashFunc(char* key,int prime,int no_of_buckets);

int next_prime(int n);

bool isPrime(int num);

#endif //HASHTABLE_HASHFUNCTIONS_H
