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

void saveRecordToFile(FILE *ptr, struct Record r)
{
    fprintf(ptr, "%d %d %s %d %d/%d/%d %s %d %.2lf %s\n\n",
            r.id,
	        r.userId,
	        r.name,
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
    int index = 0;

noAccount:
    system("clear");
    printf("\t\t\t===== New record =====\n");

date:
    printf("\nEnter today's date(mm/dd/yyyy):");
    scanf("%d/%d/%d", &r.deposit.month, &r.deposit.day, &r.deposit.year);

    if(r.deposit.month <= 0 || r.deposit.month > 12 ||
        r.deposit.day <= 0 || r.deposit.day > 31 ||
        r.deposit.year < 1900 || r.deposit.year > 2900){
        printf("Invalid date.\n");
        goto date;
    }

accountNumber:
    printf("\nEnter the account number:");
    scanf("%d", &r.accountNbr);
    if (r.accountNbr <= 0)
    {
        printf("Invalid account number.\n");
        goto accountNumber;
    }
    
    while (getAccountFromFile(pf, userName, &cr))
    {
        if (strcmp(userName, u.name) == 0 && cr.accountNbr == r.accountNbr)
        {
            printf("\n✖ This Account already exists for this user\n\n");
            goto noAccount;
        }
        index++;
    }

    r.id = index;
    printf("\nEnter the country:");
    scanf("%s", r.country);

phone:
    printf("\nEnter the phone number:");
    scanf("%d", &r.phone);
    if(r.phone == 0){
        printf("Invalid phone number.\n");
        goto phone;
    }

amount:
    printf("\nEnter amount to deposit: $");
    scanf("%lf", &r.amount);
    if(r.amount < 0 || r.amount > 1000000){
        printf("\nToo less or too many for account.\n");
        goto amount;
    }
    else if(r.amount == 0){
        printf("Invalid amount.\n");
        goto amount;
    }

accountType:
    printf("\nChoose the type of account:\n\t-> saving\n\t-> current\n\t-> fixed01(for 1 year)\n\t-> fixed02(for 2 years)\n\t-> fixed03(for 3 years)\n\n\tEnter your choice:");
    scanf("%s", r.accountType);
    if (strcmp(r.accountType, "current") != 0 &&
        strcmp(r.accountType, "saving") != 0 &&
        strcmp(r.accountType, "fixed01") != 0 &&
        strcmp(r.accountType, "fixed02") != 0 &&
        strcmp(r.accountType, "fixed03") != 0){
        printf("\nThis type of account don't exist.\n");
        goto accountType;
    }

    fprintf(pf,"\n");
    
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
                float interest = r.amount * (1 + rate / 12) - r.amount;
                printf(" -> You will get $%.2f as interest on day 10 of every month\n", interest);
            }
            else if(strcmp(r.accountType, "fixed01") == 0){
                rate = 0.04;
                float interest = r.amount * (1 + rate / 12) - r.amount;
                interest *= 12;
                printf(" -> You will get $%.2f as interest on %d/%d/%d\n", interest, 
                    r.deposit.month, r.deposit.day, r.deposit.year+1);
            }
            else if(strcmp(r.accountType, "fixed02") == 0){
                rate = 0.05;
                float interest = r.amount * (1 + rate / 12) - r.amount;
                interest *= 24;
                printf(" -> You will get $%.2f as interest on %d/%d/%d\n", interest, 
                    r.deposit.month, r.deposit.day, r.deposit.year+2);
            }
            else if(strcmp(r.accountType, "fixed03") == 0){
                rate = 0.08;
                float interest = r.amount * (1 + rate / 12) - r.amount;
                interest *= 36;
                printf(" -> You will get $%.2f as interest on %d/%d/%d\n", interest, 
                    r.deposit.month, r.deposit.day, r.deposit.year+3);
            }
            else{
                printf("You will not get interests because the account is of type current\n");
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
        strcpy(r.name, userName);

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
        saveRecordToFile(pf, arr[i]);
    }

    fclose(pf);
    success(u);
}

void makeTransaction(struct User u, int accountNum, int commandNum){
    char userName[100];
    struct Record r;
    struct Record arr[100];
    FILE *pf = fopen(RECORDS, "a+");

    int index = 0;
    double available = 0;
    double input = 0;
    while (getAccountFromFile(pf, userName, &r))
    {
        strcpy(r.name, userName);

        if(strcmp(userName, u.name) == 0 &&
            r.accountNbr == accountNum){
            if(strcmp(r.accountType, "fixed01") == 0 ||
            strcmp(r.accountType, "fixed02") == 0 ||
            strcmp(r.accountType, "fixed03") == 0){
                system("clear");
                printf("✖ You cannot deposit or withdraw cash in fixed accounts!");
                mainMenu(u);
            }

            available = r.amount;

            
            if(commandNum == 1){
                printf("Enter the amount you want to withdraw:");
                scanf("%lf", &input);
            }
            else if(commandNum == 2){
                printf("Enter the amount you want to deposit:");
                scanf("%lf", &input);
            }

            if (input <= available && input > 0 && commandNum == 1){
                r.amount -= input;
            }
            else if (commandNum == 1 && input > 0){
                system("clear");
                printf("✖ The amount you chose to withdraw is superior to your available balance");
                mainMenu(u);
            }
            else if(commandNum == 1 && input <= 0){
                system("clear");
                printf("✖ You can't withdraw cash equals 0 or less than 0.");
                mainMenu(u);
            }
            else if (commandNum == 2 && input > 0 && input <= 200000){
                r.amount += input;
            }
            else if(commandNum == 2 && input > 0){
                system("clear");
                printf("✖ You cannot deposit cash greater than 200 thousands.");
                mainMenu(u);
            }
            else if (commandNum == 2){
                system("clear");
                printf("✖ You cannot deposit cash equal 0 or less than 0.");
                mainMenu(u);
            }
        }

        arr[index] = r;
        index++;
    }

    // clear the file
    fclose(fopen(RECORDS, "w"));

    for (int i = 0; i < index; i++){
        saveRecordToFile(pf, arr[i]);
    }

    system("clear");
    fclose(pf);
    success(u);
}

void removeAccount(struct  User u, int accountNum){
    char userName[100];
    struct Record r;
    struct Record deleted;
    struct Record arr[100];
    FILE *pf = fopen(RECORDS, "a+");

    int index = 0;
    while (getAccountFromFile(pf, userName, &r))
    {
        strcpy(r.name, userName);

        if(strcmp(userName, u.name) == 0 &&
            r.accountNbr == accountNum){
            deleted = r;
        }
        else{
            arr[index] = r;
            index++;
        }
        
    }

    system("clear");
    printf("                       ===== Deleted account =====\n");
    printf("\nAccount number:%d\nDeposit Date:%d/%d/%d \ncountry:%s \nPhone number:%d \nAmount deposited: $%.2f \nType Of Account:%s\n",
        deleted.accountNbr,
        deleted.deposit.day,
        deleted.deposit.month,
        deleted.deposit.year,
        deleted.country,
        deleted.phone,
        deleted.amount,
        deleted.accountType);
    
    // clear the file
    fclose(fopen(RECORDS, "w"));

    for (int i = 0; i < index; i++){
        saveRecordToFile(pf, arr[i]);
    }

    fclose(pf);
    success(u);
}

void transfereAccount(struct User u, int accountNum){
    char userName[100];
    char ownerName[100];
    struct Record r;
    struct Record arr[100];
    FILE *pf = fopen(RECORDS, "a+");

    int index = 0;
    while (getAccountFromFile(pf, userName, &r))
    {
        strcpy(r.name, userName);
        if (strcmp(userName, u.name) == 0 &&
            r.accountNbr == accountNum)
        {
            system("clear");
            printf("                       ===== Transfering account:\n");
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

        arr[index] = r;
        index++;
    }
    
    fclose(pf);

    printf("Which user you want transfer ownership to (user name):");
    scanf("%s", ownerName);
    if(!IsNameContained(ownerName)){
        printf("This user don't exist.");
        mainMenu(u);
    }
    int ownerId;
    ownerId = getUserId(ownerName);

    for(int i = 0; i < index; i++){
        if(strcmp(arr[i].name, u.name) == 0 &&
            arr[i].accountNbr == accountNum){
            strcpy(arr[i].name, ownerName);
            arr[i].userId = ownerId;
        }
    }
    
    // clear the file
    fclose(fopen(RECORDS, "w"));
    
    pf = fopen(RECORDS, "a+");
    for (int i = 0; i < index; i++){
        saveRecordToFile(pf, arr[i]);
    }

    fclose(pf);
    success(u);
    
}

int getUserId(char *name){
    FILE *pf = fopen("./data/users.txt", "r+");

    char id[5];
    struct User temp;
    while(fscanf(pf, "%s %s %s", id, temp.name, temp.password) != EOF){
        if(strcmp(temp.name, name) == 0){
            return atoi(id);
        }
    }

    return -1;
}