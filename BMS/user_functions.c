#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linked_list.c"

#define MAX_SIZE 65535

//Contains all of the User Functions and will allow the file to be loaded in

//Load the file into the linked list in User_functions
void load_users()
{
    linked_list_t * user_list = linked_list_new();

    char current_user[MAX_SIZE] = NULL;
    char current_user[MAX_SIZE] = NULL;
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

        if(add_customer_to_list == NULL)
        {
            puts("Failed to Malloc");
            exit(EXIT_FAILURE);
        }

        printf("%s", current_user);

        /*
        current_token = strtok(current_user, "/");

        while(current_token != NULL)
        {
            printf("%s \n", current_token);
            current_token = strtok(NULL,"/");
        }

        */
    }
}