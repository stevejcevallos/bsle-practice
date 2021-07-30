#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#define USERNAME_MAX_SIZE 60
#define PASSWORD_MAX_SIZE 60
#define BUFFER_MAX_SIZE 256
#define NAME_MAX_SIZE 60
#define PHONE_SIZE 12

typedef enum
{
    menu_code = 0,
    new_account_code = 1,
    view_account = 2,
    edit_account = 3,
    see_account = 4,
    erase_account = 5,
    transact = 6,
    exit_code = 7
} bank_action_flags;

typedef struct account_node
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
    struct account_node *next;
} account_node_t;

typedef struct bank_accounts_t
{
    account_node_t *head;
}bank_accounts_t;