#include "../include/bank.h"
#include "../include/file_ops.h"
#include "../include/bank_accounts.h"

#define USERNAME_MAX_SIZE 60
#define PASSWORD_MAX_SIZE 60
#define BUFFER_MAX_SIZE 256
#define NAME_MAX_SIZE 60
#define PHONE_SIZE 12


int bank_account_num = 1;

int menu(void)
{
    printf("\n \t\t\t CUSTOMER ACCOUNT BANKING MANAGEMENT SYSTEM\n\n");
    printf("\n\n \t\t\t Bank Management Menu Page\n\n");
    printf("The following commands are available for customer use: \n\n");
    printf("Display Menu Page: 0\n");
    printf("Create New Account: 1\n");
    printf("View Account: 2\n");
    printf("Edit Account: 3\n");
    printf("See Account: 4\n");
    printf("Erase Account: 5\n");
    printf("Conduct Transaction: 6\n");
    printf("Exit: 7\n\n");
    return(1);
}


char *get_info(char *command_prompt_str)
{
    char *new_username = NULL;
    char buffer[BUFFER_MAX_SIZE];
    memset(buffer, '\0',BUFFER_MAX_SIZE);

    printf("Type in your %s: ", command_prompt_str);
    char * return_string = fgets(buffer,BUFFER_MAX_SIZE,stdin);

    if(!return_string)
    {
        perror("Did not recieve command");
    }

    else
    {
        int return_string_length = strlen(return_string);
        //fgets appends a newline character to the character pointer
        // must remove it bc most usernames don't contain a \n char.
        if (return_string_length > 0)
        {
            new_username = calloc(return_string_length - 1, sizeof(char));
            memcpy(new_username,return_string,return_string_length - 1);
            //eror check
        }
    }
    return(new_username);
}


int main(int argc, char *argv[])
{
    // Initialize the bank_accounts_linked_list
    bank_account_t *bank_accounts = NULL;
    menu();
    // Execute Menu Command
    int command_code = menu_code;
    while(1)
    {

        printf("Please type a command:\n");
        int command_response = scanf("%d", &command_code);
        while((getchar() != '\n'));

        if(command_response == EOF)
        {
            perror("Input failure\n");
            //Accept a new command
            continue;
        }
        if(command_response < 0)
        {
            //Accept a new command;
            perror("Unsuccessful execution");
            continue;
        }
        else
        {
            switch (command_code)
            {
                case menu_code:
                    menu();
                    break;
                case new_account_code:
                    printf("Create new account\n");
                    bank_account_t *new_account = create_bank_account(bank_account_num);
                    if(new_account)
                    {
                        bank_accounts = add_bank_account(bank_accounts,new_account);
                    }
                    break;
                case view_account:
                    printf("View account\n");
                    int viewing_account_number = 0;
                    int van = scanf("%d", &viewing_account_number);
                    while((getchar() != '\n'));
                    see(bank_accounts, viewing_account_number);

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
                    menu();
                    break;
            }
        }
    }
}