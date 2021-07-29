#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define USERNAME_MAX_SIZE 60
#define PASSWORD_MAX_SIZE 60
#define NAME_MAX_SIZE 60
#define PHONE_SIZE 12

typedef enum
{
    menu = 0,
    new_account = 1,
    view_account = 2,
    edit_account = 3,
    see_account = 4,
    erase_account = 5,
    transact = 6,
    exit = 7
} bank_action_flags;

typedef struct account_node_t
{
    uint32_t account_number;
    uint8_t account_type;
    uint32_t account_balance;
    char name[NAME_MAX_SIZE];
    char username[USERNAME_MAX_SIZE];
    char password[PASSWORD_MAX_SIZE];
    char phone_number[PHONE_SIZE];
    struct account_node_t *next;
} account_node_t;





int main(int argc, char *argv[])
{
    puts("\nCUSTOMER ACCOUNT BANKING MANAGEMENT SYSTEM\n\n");
    // Execute Menu Command
    while(1)
    {
        char *command = calloc(1, sizeof(char));
        fgets(command,1, stdin);
        int command_code = atoi(command);


        switch (command_code)
        {
        case menu:
            /* code */
            break;
        case new_account:
            /* code */
            break;
        case view_account:
            /* code */
            break;
        case edit_account:
            /* code */
            break;
        case see_account:
            /* code */
            break;
        case erase_account:
            /* code */
            break;
        case transact:
            /* code */
            break;
        case exit:
            /* code */
            break;
        default:
            break;
        }
        printf("Made through the switch;");
        break;
    }
}