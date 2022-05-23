#include "header.h"

const char *RECORDS = "./data/records.txt";

int getAccountFromFile(FILE *ptr, char name[50], struct Record *r)
{
    return fscanf(ptr, "%d %d %s %d %d/%d/%d %s %d %lf %s",
                  &r->id,
		  &r->userId,
		  name,
                  &r->accountNbr,
                  &r->deposit.month,
                  &r->deposit.day,
                  &r->deposit.year,
                  r->country,
                  &r->phone,
                  &r->amount,
                  r->accountType) != EOF;
}

void saveAccountToFile(FILE *ptr, struct User u, struct Record r)
{
    fprintf(ptr, "%d %d %s %d %d/%d/%d %s %d %.2lf %s\n\n",
            r.id,
	        u.id,
	        u.name,
            r.accountNbr,
            r.deposit.month,
            r.deposit.day,
            r.deposit.year,
            r.country,
            r.phone,
            r.amount,
            r.accountType);
}

void stayOrReturn(int notGood, void f(struct User u), struct User u)
{
    int option;
    if (notGood == 0)
    {
        system("clear");
        printf("\n✖ Record not found!!\n");
    invalid:
        printf("\nEnter 0 to try again, 1 to return to main menu and 2 to exit:");
        scanf("%d", &option);
        if (option == 0)
            f(u);
        else if (option == 1)
            mainMenu(u);
        else if (option == 2)
            exit(0);
        else
        {
            printf("Insert a valid operation!\n");
            goto invalid;
        }
    }
    else
    {
        printf("\nEnter 1 to go to the main menu and 0 to exit:");
        scanf("%d", &option);
    }
    if (option == 1)
    {
        system("clear");
        mainMenu(u);
    }
    else
    {
        system("clear");
        exit(1);
    }
}

void success(struct User u)
{
    int option;
    printf("\n✔ Success!\n\n");
invalid:
    printf("Enter 1 to go to the main menu and 0 to exit!\n");
    scanf("%d", &option);
    system("clear");
    if (option == 1)
    {
        mainMenu(u);
    }
    else if (option == 0)
    {
        exit(1);
    }
    else
    {
        printf("Insert a valid operation!\n");
        goto invalid;
    }
}

void createNewAcc(struct User u)
{
    struct Record r;
    struct Record cr;
    char userName[50];
    FILE *pf = fopen(RECORDS, "a+");

noAccount:
    system("clear");
    printf("\t\t\t===== New record =====\n");

    printf("\nEnter today's date(mm/dd/yyyy):");
    scanf("%d/%d/%d", &r.deposit.month, &r.deposit.day, &r.deposit.year);
    printf("\nEnter the account number:");
    scanf("%d", &r.accountNbr);

    while (getAccountFromFile(pf, userName, &cr))
    {
        if (strcmp(userName, u.name) == 0 && cr.accountNbr == r.accountNbr)
        {
            printf("✖ This Account already exists for this user\n\n");
            goto noAccount;
        }
    }
    printf("\nEnter the country:");
    scanf("%s", r.country);
    printf("\nEnter the phone number:");
    scanf("%d", &r.phone);
    printf("\nEnter amount to deposit: $");
    scanf("%lf", &r.amount);
    printf("\nChoose the type of account:\n\t-> saving\n\t-> current\n\t-> fixed01(for 1 year)\n\t-> fixed02(for 2 years)\n\t-> fixed03(for 3 years)\n\n\tEnter your choice:");
    scanf("%s", r.accountType);

    saveAccountToFile(pf, u, r);

    fclose(pf);
    success(u);
}

void checkAllAccounts(struct User u)
{
    char userName[100];
    struct Record r;

    FILE *pf = fopen(RECORDS, "r");

    system("clear");
    printf("\t\t====== All accounts from user, %s =====\n\n", u.name);
    while (getAccountFromFile(pf, userName, &r))
    {
        if (strcmp(userName, u.name) == 0)
        {
            printf("_____________________\n");
            printf("\nAccount number:%d\nDeposit Date:%d/%d/%d \ncountry:%s \nPhone number:%d \nAmount deposited: $%.2f \nType Of Account:%s\n",
                   r.accountNbr,
                   r.deposit.day,
                   r.deposit.month,
                   r.deposit.year,
                   r.country,
                   r.phone,
                   r.amount,
                   r.accountType);
        }
    }
    fclose(pf);
    success(u);
}

void checkDetailOfAccount(struct User u, int accountNum){
    char userName[100];
    struct Record r;
    FILE *pf = fopen(RECORDS, "r");

    system("clear");
    while (getAccountFromFile(pf, userName, &r))
    {
        if (strcmp(userName, u.name) == 0 &&
            r.accountNbr == accountNum)
        {
            printf("_____________________\n");
            printf("\nAccount number:%d\nDeposit Date:%d/%d/%d \ncountry:%s \nPhone number:%d \nAmount deposited: $%.2f \nType Of Account:%s\n",
                    r.accountNbr,
                    r.deposit.day,
                    r.deposit.month,
                    r.deposit.year,
                    r.country,
                    r.phone,
                    r.amount,
                    r.accountType);

            float rate;
            if(strcmp(r.accountType, "saving") == 0){
                rate = 0.07;
            }
            else if(strcmp(r.accountType, "fixed01") == 0){
                rate = 0.04;
            }
            else if(strcmp(r.accountType, "fixed02") == 0){
                rate = 0.05;
            }
            else if(strcmp(r.accountType, "fixed03") == 0){
                rate = 0.08;
            }
            else{
                rate = 0;
            }

            if (rate == 0){
                printf("You will not get interests because the account is of type current\n");
            }
            else{
                float interest = r.amount * (1 + rate / 12) - r.amount;
                printf(" -> You will get $%.2f as interest on day 10 of every month\n", interest);
            }

            fclose(pf);
            success(u);
        }
    }

}

void updateAccountInfo(struct User u, int accountNum, int commandNum){
    char userName[100];
    struct Record r;
    struct Record arr[100];
    FILE *pf = fopen(RECORDS, "a+");

    system("clear");

    int index = 0;
    while (getAccountFromFile(pf, userName, &r))
    {      
        if(strcmp(userName, u.name) == 0 &&
            r.accountNbr == accountNum){
            if(commandNum == 1){
                printf("Enter the new phone number:");
                scanf("%d", &r.phone);
            }
            else if(commandNum == 2){
                printf("Enter the new country:");
                scanf("%s", r.country);
            }
        }
        arr[index] = r;
        index++;
    }

    // clear the file
    fclose(fopen(RECORDS, "w"));

    for (int i = 0; i < index; i++){
        saveAccountToFile(pf, u, arr[i]);
    }

    fclose(pf);
    success(u);
}