//
// Created by PRAKASH on 21-08-2018.
//
#include <string.h>
#include <math.h>

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
    return (int)hashval%no_of_buckets;
}

//Find the prime number that occurs next to the given number
int next_prime(int n){

    if(base <= 2){
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
bool isPrime(int num){

    if(num == 1)
        return true;
    else if(num%2 == 0)
        return false;
    else{
        for(int i=3;i<=floor(sqrt(num));i++){

            if(num%i == 0){
                return false;
            }
        }
        return true;
    }
}
