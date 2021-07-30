#include "bank.h"
#include "file_ops.h"

int write_account_to_file(char *filename, account_node_t *account)
{
    int return_value = FAIL;
    FILE *file;
    file = fopen(filename,"a+");
    if(NULL == file)
    {
        perror("Failed to open file\n");
    }
    else if(account)
    {
        int bytes_wrote = fprintf(file,"%d, %d, %s\n",account->account_number,
        account->account_balance,account->ssn);
        if(bytes_wrote != 0)
        {
            return_value = SUCCESS;
        }
        else
        {
            perror("Failed to write all of account\n");
        }
        fclose(file);

    }
    return(return_value);
}

account_node_t * read_accounts_from_file(char *filename)
{
    account_node_t *read_account = NULL;
    if(!filename)
    {
        perror("No File name provided\n");
        return(read_account);
    }
    FILE *file;
    file = fopen(filename,"r");
    if(NULL == file)
    {
        perror("Can't open file\n");
        return(read_account);
    }

    char buffer[1024];
    while(fgets(buffer,1024,file))
    {
        char *item = strtok(buffer, ", ");
        while(item)
        {
            printf("Item is: %ld", strlen(item));
            item = strtok(NULL, ", ");
        }
        printf("\n");
    }
    fclose(file);
    return(NULL);
}