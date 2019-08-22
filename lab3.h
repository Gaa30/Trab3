#ifndef LAB3_H
#define LAB3_h
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* decimal_to_binary_16bits(int n){
    int c, d, count;
    char* pointer;
    char* splitted;
    count = 0;
    pointer = (char*)malloc(32);
    if(pointer == NULL){
        exit(EXIT_FAILURE);
    }
    for(c = 31; c>=0; c--){
        d = n >> c;
        if(d&1)
            *(pointer+count) = 1 + '0';
        else
            *(pointer+count) = 0 + '0';
        count ++;
    }
    *(pointer+count) = '\0';
    for(c = 31; c>=16; c--){
        splitted[c-16] = pointer[c];
    }
    while(strlen(splitted)>16){
        splitted[strlen(splitted)-1] = '\0';
    }
    return splitted;
}

char* decimal_to_binary_26bits(int n){
    int c, d, count;
    char* pointer;
    char* splitted;
    count = 0;
    pointer = (char*)malloc(32+1);
    if(pointer == NULL){
        exit(EXIT_FAILURE);
    }
    for(c = 31; c>=0; c--){
        d = n >> c;
        if(d&1)
            *(pointer+count) = 1 + '0';
        else
            *(pointer+count) = 0 + '0';
        count ++;
    }
    *(pointer+count) = '\0';
    for(c = 31; c>=6; c--){
        splitted[c-6] = pointer[c];
    }
    while(strlen(splitted)>26){
        splitted[strlen(splitted)-1] = '\0';
    }
    return splitted;
}

#endif