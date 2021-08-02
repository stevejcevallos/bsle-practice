#ifndef BANK_H_INCLUDED
#define BANK_H_INCLUDED

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

// Account Type
#define Saving      0
#define Current     1
#define Fixed_One   2
#define Fixed_Two   3
#define Fixed_Three 4

#define SSN_Max     9
#define Name_Max    20
#define DOB_Max     8
#define Addr_Max    80
#define Phone_Max   10
#define Bal_Max     50

#define Name        0
#define SSN         1
#define DOB         2
#define Phone       3
#define Address     4
#define Acc_Type    5
#define Acc_Bal     6

#define Suc         0
#define ERR        -1

// Account Structure
typedef struct account
{
    int acc_type;
    uint64_t balance;
    struct account *next;
} account_t;

// User Structure
typedef struct user
{
    char *name;     // First Middle Last - Max Length 20
    char *dob;      // MMDDYYYY Format
    int ssn;        // 9 fixed length number
    char *address;  // Max Length 40
    char *p_num;    // 10 fixed length number
    struct account *account;    // Linked List of Accounts
} user_t;

void menu(void);
user_t *new_acc(void);
int destroy_user(user_t *user);
int view_list(user_t *user);
int edit(user_t *user, int option);
void transact(void);
void erase(void);
void see(void);

#endif // OTHER _H_INCLUDED