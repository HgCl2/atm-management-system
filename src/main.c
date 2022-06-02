#include "header.h"

void mainMenu(struct User u)
{
    int option;
    int accountNum;
    int commandNum;
    system("clear");
    printf("\n\n\t\t======= ATM =======\n\n");
    printf("\n\t\t-->> Feel free to choose one of the options below <<--\n");
    printf("\n\t\t[1]- Create a new account\n");
    printf("\n\t\t[2]- Update account information\n");
    printf("\n\t\t[3]- Check accounts\n");
    printf("\n\t\t[4]- Check list of owned account\n");
    printf("\n\t\t[5]- Make Transaction\n");
    printf("\n\t\t[6]- Remove existing account\n");
    printf("\n\t\t[7]- Transfer ownership\n");
    printf("\n\t\t[8]- Exit\n");
    scanf("%d", &option);

    switch (option)
    {
    case 1:
        createNewAcc(u);
        break;
    case 2:
        printf("What is the account number you want to change:");
        scanf("%d", &accountNum);
        printf("\nWhich information do you want to update?\n1-> phone number\n2-> country\n");
        scanf("%d", &commandNum);
        updateAccountInfo(u, accountNum, commandNum);

        break;
    case 3:
        printf("Enter the account number:");
        scanf("%d", &accountNum);
        checkDetailOfAccount(u, accountNum);
        break;
    case 4:
        checkAllAccounts(u);
        break;
    case 5:
        printf("Enter the account number of the customer:");
        scanf("%d", &accountNum);
        printf("Do you want to:\n        1-> Withdraw\n        2-> Deposit\n\n");
        printf("Enter your choice:");
        scanf("%d", &commandNum);
        makeTransaction(u, accountNum, commandNum);
        break;
    case 6:
        // student TODO : add your **Remove existing account** function
        // here
        printf("Enter the account number you want to delete:");
        scanf("%d", &accountNum);
        removeAccount(u, accountNum);
        break;
    case 7:
        // student TODO : add your **Transfer owner** function
        // here
        break;
    case 8:
        exit(1);
        break;
    default:
        printf("Invalid operation!\n");
    }
};

void initMenu(struct User *u)
{
    int r = 0;
    int option;
    system("clear");
    printf("\n\n\t\t======= ATM =======\n");
    printf("\n\t\t-->> Feel free to login / register :\n");
    printf("\n\t\t[1]- login\n");
    printf("\n\t\t[2]- register\n");
    printf("\n\t\t[3]- exit\n");
    while (!r)
    {
        scanf("%d", &option);
        switch (option)
        {
        case 1:
            loginMenu(u->name, u->password);
            if (strcmp(u->password, getPassword(*u)) == 0)
            {
                printf("\n\nPassword Match!");
            }
            else
            {
                printf("\nWrong password!! or User Name\n");
                exit(1);
            }
            r = 1;
            break;
        case 2:
            // student TODO : add your **Registration** function
            registerMenu(u->name, u->password);
            r = 1;
            break;
        case 3:
            exit(1);
            break;
        default:
            printf("Insert a valid operation!\n");
        }
    }
};

int main()
{
    struct User u;
    
    initMenu(&u);
    mainMenu(u);
    return 0;
}
