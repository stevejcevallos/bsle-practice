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
    exit_code = 7
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

        int command_code = menu;
        printf("Please type a command:\n");
        int command_response = scanf("%d", &command_code);
        if(command_response == EOF)
        {
            perror("Input failure\n");
        }
        if(command_response < 0)
        {
            perror("Unsuccessful execution");
        }
        else
        {
            switch (command_code)
            {
                case menu:
                    /* code */
                    printf("Execute menu\n");
                    break;
                case new_account:
                    printf("Create new account\n");
                    /* code */
                    break;
                case view_account:
                    printf("View account\n");
                    /* code */
                    break;
                case edit_account:
                    printf("Edit account\n");
                    /* code */
                    break;
                case see_account:
                    printf("See account\n");
                    /* code */
                    break;
                case erase_account:
                    printf("Erase account\n");
                    /* code */
                    break;
                case transact:
                    printf("Conduct a transaction\n");
                    /* code */
                    break;
                case exit_code:
                    printf("Exit\n");
                    /* code */
                    break;
                default:
                    printf("Invalid command.\n");
                    break;
            }
        }
    }
}