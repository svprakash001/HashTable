//
// Created by PRAKASH on 21-08-2018.
//
#include <string.h>
#include <math.h>

#include "hashfunctions.h"

const int PRIME_1 = 151;

const int PRIME_2 = 239;

/**
 * Wrapper for hash function. Takes care of collision by using 'Double hashing'
 * @param key - string to hash
 * @param attempt - Which attempt this is to get hash for this key.
 * We have already failed in previous attempts due to 'collision while inserting' or 'keys not matching while searching'
 * @param no_of_buckets - Bucket size
 * @return hashed value for the key
 */
int getHash(char* key,int attempt,int no_of_buckets){

    int a = hashFunc(key,PRIME_1,no_of_buckets);
    int b = hashFunc(key,PRIME_2,no_of_buckets);

    return (a + attempt*(b+1)) % no_of_buckets;
}

/**
 * Hash function that converts a string to an int between 0 and bucket_size-1.
 * Just created my own simple basic hash function, nothing special
 * @param key
 * @param prime - Prime number used as part of hashing function
 * @param no_of_buckets - Bucket size
 * @return hashed value
 */
int hashFunc(char* key,int prime,int no_of_buckets){

    int len = strlen(key);
    long hashval = 0;

    for(int i=0;i<len;i++){

        hashval += (long) pow(prime,i) * key[i];
        hashval %= no_of_buckets;

    }
    return (int)hashval%no_of_buckets;
}

//Find the prime number that occurs next to the given number
int next_prime(int n){

    if(n <= 2){
        return 2;
    }

    while(1){
        if(isPrime(n)){
            return n;
        }
        n++;
    }
}

//check if a number is prime or not
int isPrime(int num){

    if(num == 1)
        return 0;
    else if(num%2 == 0)
        return 0;
    else{
        for(int i=3;i<=floor(sqrt(num));i++){

            if(num%i == 0){
                return 0;
            }
        }
        return 1;
    }
}
