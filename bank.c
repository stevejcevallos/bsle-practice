#include "bank.h"
#include "file_ops.h"

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


int check_username_exists(account_node_t *account, bank_accounts_t *account_list)
{
    int return_value = FAIL;
    if (account && account->username && account_list)
    {
        account_node_t *existing_account = account_list->head;
        while (existing_account)
        {
            int username_found = memcmp(account->username,existing_account->username, USERNAME_MAX_SIZE);
            if (SUCCESS == username_found)
            {
                //the username already exists in the bank thus we should not create a new account
                return_value = SUCCESS;
                break;
            }
            existing_account = existing_account->next;
        }
    }
    return(return_value);
}

int add_account(account_node_t *account, bank_accounts_t *account_list)
{
    int return_value = FAIL;
    if(account && account->username && account_list)
    {
        account_node_t *existing_account = account_list->head;
        if(!existing_account)
        {
            account_list->head = account;
        }
        else
        {
            while(existing_account->next)
            {
                existing_account = existing_account->next;
            }
            existing_account->next = account;
        }
        return_value = SUCCESS;
    }
    if(SUCCESS == return_value)
    {
        return_value = write_account_to_file("data1.csv",account);
        printf("%d\n",return_value);
    }

    return(return_value);
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

account_node_t * make_new_account(bank_accounts_t *bank_accounts)
{

    account_node_t *new_account = malloc(sizeof(account_node_t));
    if(!new_account)
    {
        perror("New Account Error: Memory Allocation");
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
        printf("user_name_exists: %s\n", new_account->username);
        int user_name_exists = check_username_exists(new_account,bank_accounts);
        printf("user_name_exists: %d\n", user_name_exists);
        int added_account = add_account(new_account,bank_accounts);
        if(1 == added_account)
        {
            printf("Account added\n");
        }
    }

    // Check if each input value is valid
    // Check if username has been used before
    // Linked list of all accounts search for all the usernames and if username has been created don't allow
    // Else add the new account to the bankaccounts list. And create a file in the bankaccounts folder with the the new account info.
    return(new_account);
}



bank_accounts_t *create_bank_accounts_list(void)
{
    bank_accounts_t *bank_accounts = calloc(1, sizeof(bank_accounts_t));
    if(!bank_accounts)
    {
        perror("Bank account memory error");
        //do a proper command to handle this error probably exit.
        return(NULL);
    }
    bank_accounts->head = NULL;
    return(bank_accounts);
}

int main(int argc, char *argv[])
{
    // Initialize the bank_accounts_linked_list
    bank_accounts_t *bank_accounts = create_bank_accounts_list();
    if(NULL == bank_accounts)
    {
        return(-1);
    }

    read_accounts_from_file("data1.csv");
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
                    make_new_account(bank_accounts);
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
                    menu();
                    break;
            }
        }
    }
}