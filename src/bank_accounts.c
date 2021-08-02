#include "../include/bank_accounts.h"
#include "../include/bank.h"

#define WITHDRAW 1
#define DEPOSIT 0

bank_account_t *create_bank_account(int bank_account_num)
{
    bank_account_t *new_account = malloc(sizeof(bank_account_t));
    if(!new_account)
    {
        perror("New Account Error: Memory Allocation");
        //new account is NULL
    }
    else
    {
        new_account->name = get_info("name");
        new_account->username = get_info("username");
        new_account->password = get_info("password");
        new_account->address = get_info("address");
        new_account->phone = get_info("phone number");
        new_account->ssn = get_info("citizenship number");
        new_account->date_of_birth = get_info("Date of Birth (MMDDYYYY)");
        new_account->account_type  = get_info("Account Type");
        new_account->account_balance = 0;
        new_account->account_number = bank_account_num++;
        new_account->next = NULL;
    }
    return(new_account);
}

bank_account_t *add_bank_account(bank_account_t *head, bank_account_t *new_account)
{
    if(NULL == head)
    {
        // no accounts in the system and the new account is the
        // first account.
        return(new_account);
    }
    else
    {
        printf("Head is not null\n");
        bank_account_t *temp_account = head;
        bank_account_t *prev_account = NULL;
        while(temp_account)
        {
            prev_account = temp_account;
            temp_account = temp_account->next;
        }
        prev_account->next = new_account;
    }
    return(head);
}


bank_account_t *delete_bank_account(bank_account_t *head, int account_number)
{
    if(head->account_number == account_number)
    {
        //we need to delete the head.
        bank_account_t *new_head = head->next;
        int deleted = delete_node(head);
        if(SUCCESS == deleted)
        {
            return(new_head);
        }
        else
        {
            return(head);
        }
    }
    else
    {
        //loop through to find the node we want to delete
        bank_account_t *temp_account = head;
        bank_account_t *prev_account = NULL;
        while(temp_account && temp_account->account_number != account_number)
        {
            prev_account = temp_account;
            temp_account = temp_account->next;
        }

        //If temp_account is NULL account number does not exist
        if(NULL == temp_account)
        {
            return (head);
        }
        else
        {
            prev_account->next = temp_account->next;
            delete_node(temp_account);
            return(head);
        }
    }
}

bank_account_t *edit_bank_account(bank_account_t *head, int account_number, char *new_address, char *new_phone_number)
{
    if (NULL == head)
    {
        perror("Head is not initialized\n");
        return(NULL);
    }
    else
    {
        bank_account_t *current_account = head;
        while(current_account)
        {
            if(current_account->account_number == account_number)
            {
                break;
            }
            current_account = current_account->next;
        }
        if(NULL == current_account)
        {
            perror("Account does not exist\n");
            return(head);
        }
        else
        {
            if(new_address)
            {
                current_account->address = new_address;
            }
            if(new_phone_number)
            {
                current_account->phone = new_phone_number;
            }
        }
        return(head);
    }
}

bank_account_t *transaction_bank_account(bank_account_t *head, int account_number, int transaction_type, int amount)
{
    if (NULL == head)
    {
        perror("Head is not initialized\n");
        return(NULL);
    }
    else
    {
        bank_account_t *current_account = head;
        while(current_account)
        {
            if(current_account->account_number == account_number)
            {
                break;
            }
            current_account = current_account->next;
        }
        if(NULL == current_account)
        {
            perror("Account does not exist\n");
            return(head);
        }
        else
        {
            if(amount > current_account->account_balance && WITHDRAW == transaction_type)
            {
                perror("Insufficent funds");
            }
            else if(amount < 0)
            {
                perror("Can't transact negative money.");
            }
            else
            {
                if(WITHDRAW == transaction_type)
                {
                    current_account->account_balance = current_account->account_balance - amount;
                }
                else if(DEPOSIT == transaction_type)
                {
                    current_account->account_balance = current_account->account_balance + amount;
                }
                printf("Your new account balance is: %d\n", current_account->account_balance);
            }

        }
        return(head);
    }
}

int see(bank_account_t *head, int account_number)
{
    if(!head)
    {
        perror("NO Accounts exist\n");
        return(FAIL);
    }
    bank_account_t *current_account = head;
    while(current_account)
    {
        if(current_account->account_number == account_number)
        {
            break;
        }
        current_account = current_account->next;
    }
    if(NULL == current_account)
    {
        perror("Account does not exist\n");
        return(FAIL);
    }
    printf("\n\n Number\tBalance\tname\taddress\tphone\account_type\n\n");
    printf("\n\n %d\t%d\t%s\t%s\t%s\t %s\n\n", current_account->account_number, current_account->account_balance, current_account->name, current_account->address, current_account->phone,current_account->account_type);
    return(SUCCESS);
}

int delete_node(bank_account_t *account_to_delete)
{
    int return_value = FAIL;
    if(account_to_delete)
    {
        free(account_to_delete->ssn);
        free(account_to_delete->name);
        free(account_to_delete->username);
        free(account_to_delete->password);
        free(account_to_delete->address);
        free(account_to_delete->phone);
        free(account_to_delete->date_of_birth);
        free(account_to_delete->account_type);
        free(account_to_delete);
        return_value = SUCCESS;
    }
    return(return_value);

}

int delete_bank_account_list(bank_account_t *head)
{
    int return_value = FAIL;
    if(NULL == head)
    {
        return_value = SUCCESS;
    }
    else
    {
        bank_account_t *temp = NULL;
        while(head)
        {
            temp = head->next;
            delete_node(head);
            head = temp;
        }
        return_value = SUCCESS;
    }
    return(return_value);
}