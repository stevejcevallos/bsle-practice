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
    char buffer[256];
    int ret = 0;
    int length;
    int count = 0;

    // Get SSN from user
    while (true)
    {
        printf("Type SSN: (9 digits)\n");
        ret = scanf("%s", &buffer);
        if (ret == 1)
        {
            length = strlen(buffer);
            if (length != 9)
            {
                printf("Citizenship number length must be 9.\n");
                continue;
            }

            for (int i = 0; i < 9; i++)
            {
                if (isdigit(buffer[i]))
                {
                    count++;
                }
            }

            if (count == 9)
            {
                break;
            }
            else
            {

            }
        }
        else
        {
            printf("Scanf Malfunction. Try again.\n");
        }
    }

    length = strlen(buffer);
    if (length != 9)
    {
        printf("Citizenship number length is not 9.\n");
        return NULL;
    }

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
