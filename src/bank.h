#ifndef BANK_H_INCLUDED
#define BANK_H_INCLUDED

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

// Account Type
#define Saving      0
#define Current     1
#define Fixed_One   2
#define Fixed_Two   3
#define Fixed_Three 4

// Account Structure
typedef struct account
{
    int acc_type;
    int balance;
    struct account *next;
} account_t;

// User Structure
typedef struct user
{
    char *name;     // First Middle Last - Max Length 20
    char *dob;      // MMDDYYYY Format
    int c_num;      // 9 fixed length number
    char *address;  // Max Length 40
    int p_num;      // 10 fixed length number
    struct account *account;    // Linked List of Accounts
} user_t;

// This function displays the menu or welcome screen to perform different banking activities mentioned below.
void menu(void);

// This function creates a new customer account. It asks for some  personal and banking details of the customer such as name, date of birth, citizenship number, address and phone number. You can enter the amount to deposit and choose one type of deposit account – saving, current, fixed for 1 year, fixed for 2 years or fixed for 3 years.
void new_acc(void);

// With this function, you can view the customer’s banking information such as account number, name, address and phone number provided while creating the account.
void view_list(void);

// This function has been used for changing the address and phone number of a particular customer account.
void edit(void);

// With this function, you can deposit and withdraw money to and from a particular customer account.
void transact(void);

// This function is for deleting a customer account.
void erase(void);

// This function shows account number, name, date of birth, citizenship number, age, address, phone number, type of account, amount deposited and date of deposit. It also displays the amount of interest corresponding to a particular account type.
void see(void);

#endif // OTHER _H_INCLUDED