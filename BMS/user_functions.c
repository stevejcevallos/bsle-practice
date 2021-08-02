#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linked_list.c"

#define MAX_SIZE 65535

//Contains all of the User Functions and will allow the file to be loaded in

customer * get_customer_info()
{
    customer * new_customer = malloc(sizeof(customer));
    new_customer->citizen_num = malloc(sizeof(9));
    new_customer->dob = malloc(sizeof(8));
    new_customer->phone_number = malloc(sizeof(10));

    char user_input[MAX_SIZE];

    printf("\t Enter your first: ");
    //Check if Scanf if working right
    scanf("%s", new_customer->first_name);

    new_customer->first_name = malloc(sizeof(strlen(user_input)));
    new_customer->first_name = user_input;

    fflush(stdin);

    printf("%s\n", new_customer->first_name);


    printf("\t Enter your last: ");
    //Check if Scanf if working right
    scanf("%s",user_input);

    new_customer->last_name = malloc(sizeof(strlen(user_input)));
    new_customer->last_name = user_input;

    fflush(stdin);


    printf("\t Enter your DOB (MMDDYYY): ");
    //Check if Scanf if working right
    scanf("%s",user_input);

    new_customer->dob = user_input;

    fflush(stdin);

    printf("\t Enter your SSN: ");
    //Check if Scanf if working right
    scanf("%s",user_input);

    new_customer->citizen_num = user_input;

    fflush(stdin);


    printf("\t Enter your Phone Number (123-456-7899): ");
    //Check if Scanf if working right
    scanf("%s",user_input);

    new_customer->phone_number = user_input;

    fflush(stdin);

}

//Load the file into the linked list in User_functions
void load_users()
{
    linked_list_t * user_list = linked_list_new();

    char current_user[MAX_SIZE] = {0};
    char * current_token = NULL;

    FILE *fp;
    fp = fopen("users.txt", "r");

    if(fp == NULL)
    {
        puts("File Could Not be Opened");
        exit(EXIT_FAILURE);
    }

    while (fgets(current_user, MAX_SIZE, fp) != NULL)
    {
        customer * add_customer_to_list = malloc(sizeof(add_customer_to_list));
        char * token;
        int customer_index = 0;

        if(add_customer_to_list == NULL)
        {
            puts("Failed to Malloc");
            exit(EXIT_FAILURE);
        }

        token = strtok(current_user, "/");

        while(token != NULL)
        {
            printf("%s \n", token);

            switch (customer_index)
            {
                case 0:
                    add_customer_to_list->first_name = token;
                    break;
                case 1:
                    add_customer_to_list->dob = token;
                    break;

                case 2:
                    add_customer_to_list->citizen_num = token;
                    break;
                case 5:
                    add_customer_to_list->customer_account->account_number = token;
                    break;

                default:
                    break;
            }

            add_node(user_list, add_customer_to_list);

            token = strtok(NULL,"/");
            customer_index++;
        }

    }
}