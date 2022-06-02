#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

struct Date
{
    int month, day, year;
};

// all fields for each record of an account
struct Record
{
    int id;
    int userId;
    char name[100];
    char country[100];
    int phone;
    char accountType[10];
    int accountNbr;
    double amount;
    struct Date deposit;
    struct Date withdraw;
};

struct User
{
    int id;
    char name[50];
    char password[50];
};

// authentication functions
void loginMenu(char a[50], char pass[50]);
void registerMenu(char a[50], char pass[50]);
const char *getPassword(struct User u);

// system function
void createNewAcc(struct User u);
void mainMenu(struct User u);
void checkAllAccounts(struct User u);
void checkDetailOfAccount(struct User u, int accountID);
void updateAccountInfo(struct User u, int accountNum, int commandNum);
void makeTransaction(struct User u, int accountNum, int commandNum);
void removeAccount(struct  User u, int accountNum);
void transfereAccount(struct User u, int accountNum);

// additionally functions
bool isContain(char* array[100], char* str);
int getUserId(char *name);