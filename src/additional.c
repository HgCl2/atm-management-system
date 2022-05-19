#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "header.h"

bool isContain(char* array[100], char* str){
    for (int i = 0; i < 100; i++){
        if (array[i] == str){
            return false;
        }
    }

    return true;
}