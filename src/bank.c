#include "bank.h"
#include "helper.c"

/**
 * Print Menu
 */
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

/**
 * Generate New Account
 * @return user struct on success, NULL for errors
 */
user_t *new_acc(void)
{

    char *ssn;
    ssn = get_user_info(SSN);
    if (NULL == ssn)
    {
        return NULL;
    }
    /*
    Implement check if duplicated SSN in file
    */

    char *acc_type;
    char *acc_bal;
    user_t *new = malloc(sizeof(user_t));
    if (NULL == new)
    {
        perror("Memory Allocation");
        return NULL;
    }
    
    new->ssn = atoi(ssn);
    free(ssn);
    ssn = NULL;

    new->name = get_user_info(Name);
    if (NULL == new->name)
    {
        destroy_user(new);
        return NULL;
    }
    new->dob = get_user_info(DOB);
    if (NULL == new->dob)
    {
        destroy_user(new);
        return NULL;
    }
    new->p_num = get_user_info(Phone);
    if (NULL == new->p_num)
    {
        destroy_user(new);
        return NULL;
    }
    new->address = get_user_info(Address);
    if (NULL == new->address)
    {
        destroy_user(new);
        return NULL;
    }
    acc_type = get_user_info(Acc_Type);
    if (NULL == acc_type)
    {
        destroy_user(new);
        return NULL;
    }
    acc_bal = get_user_info(Acc_Bal);
    if (NULL == acc_bal)
    {
        destroy_user(new);
        return NULL;
    }
    new->account = calloc(1, sizeof(account_t));
    if (NULL == new->account)
    {
        destroy_user(new);
        return NULL;
    }
    new->account->acc_type = atoi(acc_type);
    new->account->balance = strtoull(acc_bal, NULL, 10);
    free(acc_type);
    acc_type = NULL;
    free(acc_bal);
    acc_bal == NULL;

    return new;
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

    if (NULL != user->p_num)
    {
        free(user->p_num);
        user->p_num = NULL;
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

/**
 * Display User Information
 * @param user user_t structure
 * @return 0 on success, -1 for errors
 */
int view_list(user_t *user)
{
    if (NULL == user)
    {
        return -1;
    }

    printf("***** User Information *****\n");
    printf("1. Name: %s\n", user->name);
    printf("2. SSN: %d\n", user->ssn);
    printf("3. DOB: %s\n", user->dob);
    printf("4. Phone Number: %s\n", user->p_num);
    printf("5. Address: %s\n", user->address);

    account_t *temp = user->account;
    int count = 1;
    while (NULL != temp)
    {
        switch (temp->acc_type)
        {
            case Saving:
                printf("%d. Account %d type: Saving\n", count + 5, count);
                break;
            case Current:
                printf("%d. Account %d type: Current\n", count + 5, count);
                break;
            case Fixed_One:
                printf("%d. Account %d type: Fixed 1 Year\n", count + 5, count);
                break;
            case Fixed_Two:
                printf("%d. Account %d type: Fixed 2 Year\n", count + 5, count);
                break;
            case Fixed_Three:
                printf("%d. Account %d type: Fixed 3 Year\n", count + 5, count);
                break;
            default:
                printf("%d. Account %d type: Unknown\n", count + 5, count);
                break;
        }
        printf("%d. Account %d balance: $%ld\n", count + 6, count, temp->balance);
        count++;
        temp = temp->next;
    }

    return 0;
}

// This function has been used for changing the address and phone number of a particular customer account.
int edit(user_t *user, int option)
{
    if (NULL == user)
    {
        return -1;
    }

    switch (option)
    {
        case Name:
            printf("Current Name: %s\n", user->name);
            printf("Enter New Name: ");

            break;
        
        default:
            break;
    }
}

// With this function, you can deposit and withdraw money to and from a particular customer account.
void transact(void);

// This function is for deleting a customer account.
void erase(void);

// This function shows account number, name, date of birth, citizenship number, age, address, phone number, type of account, amount deposited and date of deposit. It also displays the amount of interest corresponding to a particular account type.
void see(void);
