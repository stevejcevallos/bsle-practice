#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>


typedef struct _account
{
    int account_number;
    char * account_type;
    int balance;
} account;


typedef struct _customer
{
    char * name;
    int dob_month;
    int dob_day;
    int dob_year;
    double citizen_num;
    char * address;
    int phone_number;
    account customer_account;
} customer;
