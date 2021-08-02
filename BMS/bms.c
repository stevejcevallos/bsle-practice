#include "bms.h"

/*
see()
erase()
transact()
edit()
view_list()

*/

void new_acc()
{
    puts("Create New Account");
    customer * new__customer_account;
    new__customer_account = get_customer_info();
    //load_users();

}

void menu(void)
{
    int user_input = 0;

    //Display the Welcome Screen
    puts("\n\t\t CUSTOMER ACCOUNT BANKING MANAGMENT SYSTEM \n");
    puts("\t\t WELCOME TO THE MAIN MENU \n");
    puts("\t 1. Create New Account");
    puts("\t 2. Update information of exisiting account");
    puts("\t 3. For transactions");
    puts("\t 4. Check the details fo existing account");
    puts("\t 5. Remove existing account");
    puts("\t 6. View customer's list");
    puts("\t 7. Exit \n");

    printf("\t Enter your choice: ");

    //Check if Scanf if working right
    scanf("%d", &user_input);

    //Checks to see if the input is valid
    switch (user_input)
    {
    case 1:
        new_acc();
        break;
    case 2:
        puts("Selected Update Info");
        break;

    case 3:
        puts("Selected Transactions");
        break;

    case 4:
        puts("Selected Check Details");
        break;

    case 5:
        puts("Selected Remove Account");
        break;

    case 6:
        puts("Selected Customer List");
        break;

    case 7:
        puts("Selected Exit");
        puts("Goodbye!");
        exit(EXIT_SUCCESS);
        break;

    default:
        puts("Invalid Input Goodbye");
        exit(EXIT_FAILURE);
        break;
    }
}

int main()
{
    // Runs the menu function
    menu();
}
