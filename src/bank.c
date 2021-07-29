#include "bank.h"

// This function displays the menu or welcome screen to perform different banking activities mentioned below.
void menu(void)
{
    printf("CUSTOMER ACCOUNT BANKING MANAGEMENT SYSTEM\n\n");
    printf("WELCOME TO THE MAIN MENU\n\n");
    printf("1. Create new account\n");
    printf("2. Update information of existing account\n");
    printf("3. For transactions\n");
    printf("4. Check the details of existing account\n");
    printf("5. Removing existing account\n");
    printf("6. View customer's list\n");
    printf("7. Exit\n\n\n\n");
    printf("Enter your choice: \n\n");
}

// This function creates a new customer account. It asks for some  personal and banking details of the customer such as name, date of birth, citizenship number, address and phone number. You can enter the amount to deposit and choose one type of deposit account – saving, current, fixed for 1 year, fixed for 2 years or fixed for 3 years.
user_t *new_acc(void)
{
    // Get SSN from user
    int ssn = ssn_helper();
    int 

    printf("Type name: (First Middle Last) \n");

    user_t *new = malloc(sizeof(user_t));
    if (NULL == new)
    {
        perror("Memory Allocation");
        return NULL;
    }
}

// With this function, you can view the customer’s banking information such as account number, name, address and phone number provided while creating the account.
void view_list(void);

// This function has been used for changing the address and phone number of a particular customer account.
void edit(void);

// With this function, you can deposit and withdraw money to and from a particular customer account.
void transact(void);

// This function is for deleting a customer account.
void erase(void);

// This function shows account number, name, date of birth, citizenship number, age, address, phone number, type of account, amount deposited and date of deposit. It also displays the amount of interest corresponding to a particular account type.
void see(void);
