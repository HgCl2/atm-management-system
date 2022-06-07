#include "header.h"

bool isContain(char* array[100], char* str){
    for (int i = 0; i < 100; i++){
        if (array[i] == str){
            return false;
        }
    }

    return true;
}

bool usersChecker(){
    FILE* pf = fopen("./data/users.txt", "r+");

    char id[5];
    struct User temp;
    int userPosition = 0;
    int userID = 0;
    float floatID = 0;

    while(fscanf(pf, "%s %s %s", id, temp.name, temp.password) != EOF){
        floatID = atof(id);
        userID = atoi(id);
        
        if(userID == 0 && userPosition != 0){
            return false;
        }
        else if(userID != userPosition || userID != floatID){
            return false;
        }
        else if(strcmp(temp.name, "") == 0 || strcmp(temp.name, " ") == 0){
            return false;
        }
        else if(strcmp(temp.password, "") == 0 || strcmp(temp.password, " ") == 0){
            return false;
        }
        userPosition++;
    }

    return true;

}