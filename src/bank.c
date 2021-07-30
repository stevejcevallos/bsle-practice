#include "bank.h"
#include "helper.c"

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

/**
 * Generate New Account
 * @return user struct on success, NULL for errors
 */
user_t *new_acc(void)
{
    user_t *new = malloc(sizeof(user_t));
    if (NULL == new)
    {
        perror("Memory Allocation");
        return NULL;
    }

    new->ssn = get_ssn();
    if (new->ssn == -1)
    {
        destroy_user(new);
        return NULL;
    }
    new->name = get_name();
    if (NULL == new->name)
    {
        destroy_user(new);
        return NULL;
    }
    new->dob = get_dob();
    if (NULL == new->dob)
    {
        destroy_user(new);
        return NULL;
    }
    new->p_num = get_phone();
    if (NULL == new->p_num)
    {
        destroy_user(new);
        return NULL;
    }
}

/**
 * Destroy allocated user_t structure from stack
 * @param user user_t structure
 * @return 0 on success, -1 for errors
 */
int destroy_user(user_t *user)
{
    if (NULL == user)
    {
        return -1;
    }

    account_t *current = user->account;
    account_t *temp;

    if (NULL != user->name)
    {
        free(user->name);
        user->name = NULL;
    }

    if (NULL != user->dob)
    {
        free(user->dob);
        user->dob = NULL;
    }

    if (NULL != user->address)
    {
        free(user->address);
        user->address = NULL;
    }

    if (NULL != current)
    {
        temp = current->next;
        free(current);
        current = temp;
    }

    free(user);
    user = NULL;
    return 0;
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
