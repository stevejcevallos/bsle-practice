#include "../include/bank.h"
#include "../include/file_ops.h"
#include "../include/bank_accounts.h"

int write_account_to_file(char *filename, bank_account_t *account)
{
    int return_value = FAIL;
    bank_account_t *temp = account;
    FILE *file;
    file = fopen(filename,"w");
    if(NULL == file)
    {
        perror("Failed to open file\n");
    }
    else
    {
        while(temp)
        {
            int items_written = fwrite(temp, sizeof(bank_account_t), 1, file);
            printf("This i sthe number if items written %d\n", items_written);
            if(1 != items_written)
            {
                perror("Write to file failure\n");
                return_value = FAIL;
                break;
            }
            temp = temp->next;
            return_value = SUCCESS;
        }
    }
    fclose(file);
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