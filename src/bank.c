#include "../include/bank.h"
#include "../include/file_ops.h"
#include "../include/bank_accounts.h"

#define USERNAME_MAX_SIZE 60
#define PASSWORD_MAX_SIZE 60
#define BUFFER_MAX_SIZE 256
#define NAME_MAX_SIZE 60
#define PHONE_SIZE 12


int bank_account_num = 0;

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
    char buffer[BUFFER_MAX_SIZE] ={0};

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

    char *filename = "bankaccounts.txt";
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
                    bank_account_num++;
                    bank_account_t *new_account = create_bank_account(bank_account_num);
                    if(new_account)
                    {
                        // add bank account to file
                        // if that is good then add it to the linked list
                        // if both are successful then return success
                        // if they arent successful remove the entry from which ever failed
                        // and return failed to add bank account
                        if(bank_accounts == NULL)
                        {
                            bank_accounts = new_account;
                        }
                        else
                        {
                            bank_accounts = add_bank_account(bank_accounts,new_account);
                            printf("This is the new acount: %d\n",bank_accounts->next->account_number);
                        }
                        int bank_write_success = write_account_to_file(filename,new_account);
                        if (FAIL == bank_write_success)
                        {
                            perror("Unsuccessful account creation");
                        }
                    }
                    break;
                case view_account:
                    printf("View account\n");
                    int viewing_account_number = 0;
                    int van = scanf("%d", &viewing_account_number);
                    while((getchar() != '\n'));
                    if(van > 0)
                    {
                        see(bank_accounts, viewing_account_number);
                    }
                    else
                    {
                        perror("Invalid account number.\n");
                    }
                    break;
                case edit_account:
                    printf("Edit account\n");
                    /* code */
                    int edit_account_number = 0;
                    char new_address_buffer[BUFFER_MAX_SIZE] ={0};
                    char new_phone_buffer[BUFFER_MAX_SIZE] ={0};

                    printf("Enter Account Number: ");
                    int edit_an = scanf("%d", &edit_account_number);
                    while((getchar() != '\n'));

                    printf("\n Enter new address: ");
                    char *new_address = fgets(new_address_buffer,BUFFER_MAX_SIZE,stdin);
                    printf("\n Enter new phone number: ");
                    char *new_phone =fgets(new_phone_buffer,BUFFER_MAX_SIZE,stdin);

                    if(new_phone && new_address && edit_an)
                    {
                        bank_accounts = edit_bank_account(bank_accounts, edit_account_number, new_address, new_phone);
                    }
                    else
                    {
                        perror("Invalid Account\n");
                    }
                    break;
                case see_account:
                    printf("See account\n");
                    int see_account_number = 0;
                    int san = scanf("%d", &see_account_number);
                    while((getchar() != '\n'));
                    if(san > 0)
                    {
                        see(bank_accounts, see_account_number);
                    }
                    else
                    {
                        perror("Invalid Account\n");
                    }
                    break;
                case erase_account:
                    printf("Erase account\n");
                    int erase_account_number = 0;
                    int ean = scanf("%d", &erase_account_number);
                    while((getchar() != '\n'));
                    if(ean > 0)
                    {
                        bank_accounts = delete_bank_account(bank_accounts, erase_account_number);
                    }
                    else
                    {
                        perror("Invalid Account\n");
                    }
                    break;
                case transact:
                    printf("Conduct a transaction\n");
                    int account_number = 0;
                    printf("Enter Account Number: ");
                    int an = scanf("%d", &account_number);
                    while((getchar() != '\n'));
                    int transaction_type = 0;
                    printf("\n Enter Transaction Type [0] Deposit [1] Withdrawl: ");
                    an = scanf("%d", &transaction_type);
                    while((getchar() != '\n'));
                    int amount = 0;
                    printf("\n Enter transaction amount: ");
                    an = scanf("%d",&amount);
                    while((getchar() != '\n'));
                    if(an > 0)
                    {
                        bank_accounts = transaction_bank_account(bank_accounts, account_number, transaction_type, amount);
                    }
                    else
                    {
                        perror("Invalid Account\n");
                    }
                    break;
                case exit_code:
                    printf("Exit\n");
                    delete_bank_account_list(bank_accounts);
                    /* code */
                    break;
                default:
                    menu();
                    break;
            }
        }
    }
}