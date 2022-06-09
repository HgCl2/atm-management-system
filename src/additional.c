#include "header.h"

bool isContain(char* array[100], char* str){
    for (int i = 0; i < 100; i++){
        if (strcmp(array[i], str) == 0){
            return true;
        }
    }

    return false;
}

bool IsNameContained(char *name){
    char id[5];
    char userName[100];
    char password[100];

    FILE *pf = fopen("./data/users.txt", "r");
    while(fscanf(pf, "%s %s %s", id, userName, password) != EOF){
        if(strcmp(name, userName) == 0){
            return true;
        }
    }
    return false;
}

bool usersChecker(){
    FILE* pf = fopen("./data/users.txt", "r+");

    char id[100];
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

bool recordsChecker(){
    FILE *ptr = fopen("./data/records.txt", "r");

    char id[100];
    char userId[100];
    char name[100];
    char accountNbr[100];
    int depositDay = -1;
    int depositMonth = -1;
    int depositYear = -1;
    char country[100];
    char phone[100];
    char amount[100];
    char accountType[100];
    int index = 0;
    while(fscanf(ptr, "%s %s %s %s %d/%d/%d %s %s %s %s",
        id, userId, name, accountNbr,
        &depositMonth, &depositDay,
        &depositYear, country, phone,
        amount, accountType) != EOF){
        int intId = atoi(id);
        float floatId = atof(id);
        int intUserId = atoi(userId);
        float floatUserId = atof(userId);
        
        if(intId == 0 && strcmp(id, "0") != 0){
            printf("1");
            return false;
        }
        else if(intId != index || intId != floatId){
            printf("2");
            return false;
        }
        else if (!IsNameContained(name)){
            printf("3");
            return false;
        }
        else if(getUserId(name) != intUserId){
            printf("4");
            return false;
        }
        else if(strcmp(accountType, "current") != 0 &&
            strcmp(accountType, "fixed01") != 0 &&
            strcmp(accountType, "fixed02") != 0 &&
            strcmp(accountType, "fixed03") != 0 &&
            strcmp(accountType, "saving") != 0){
            printf("5");
            return false;
        }
        else if((depositMonth < 1 || depositMonth > 12) ||
            (depositDay < 1 || depositDay > 31) ||
            (depositYear < 1900 || depositYear > 2900)){
            return false;
        }
        

        index++;
    }
    return true;
}