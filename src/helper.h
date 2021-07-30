#ifndef HELPER_H_INCLUDED
#define HELPER_H_INCLUDED

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

#define SSN_Max     9
#define Name_Max    20
#define DOB_Max     8
#define Addr_Max    80
#define Phone_Max   10
#define Bal_Max     50

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

int get_ssn(void);

char *get_name(void);

#endif // OTHER _H_INCLUDED