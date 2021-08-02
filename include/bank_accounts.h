#ifndef BANK_ACCOUNTS_H
#define BANK_ACCOUNTS_H

#include "bank.h"
typedef struct bank_account
{
    uint32_t account_number;
    uint32_t account_balance;
    char *ssn;
    char *name;
    char *username;
    char *password;
    char *address;
    char *phone;
    char *date_of_birth;
    char *account_type;
    struct bank_account *next;
} bank_account_t;

bank_account_t *create_bank_account(int bank_account_num);

bank_account_t *add_bank_account(bank_account_t *head, bank_account_t *new_account);

bank_account_t *delete_bank_account(bank_account_t *head, int account_number);

bank_account_t *edit_bank_account(bank_account_t *head, int account_number, char *new_address, char *new_phone_number);

bank_account_t *transaction_bank_account(bank_account_t *head, int account_number, int transaction_type, int amount);
int delete_bank_account_list(bank_account_t *head);
int delete_node(bank_account_t *account_to_delete);
int see(bank_account_t *head, int account_number);
#endif