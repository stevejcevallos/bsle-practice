#include "bank.h"

int get_user_info_print1(int option)
{
    switch (option)
    {
        case Name:
            printf("Type Name: (Max: 20)\n");
            break;
        case SSN:
            printf("Type SSN: (9 digits)\n");
            break;
        case DOB:
            printf("Type Date of Birth: (Format: MMDDYYYY)\n");
            break;
        case Phone:
            printf("Type Phone Number: (10 digits)\n");
            break;
        case Address:
            printf("Type Address: (Max: 80)\n");
            break;
        case Acc_Type:
            printf("Select Account Type: \n");
            printf("0: Saving, 1: Current, 2: Fixed_1yr 3: Fixed_2yr, 4: Fixed_3yr\n");
            break;
        case Acc_Bal:
            printf("Type Balance of Account: (Max: 50 digits)\n");
            break;
        default:
            printf("Unknown Option.\n");
            return -1;
    }
    return 0;
}

int name_validator(char *buffer, int length)
{
    int count = 0;

    if (length > Name_Max)
    {
        printf("Name length must be less than 20.\n");
        return ERR;
    }

    for (int i = 0; i < length; i++)
    {
        if (isalpha(buffer[i]) || buffer[i] == ' ')
        {
            count++;
        }
    }

    if (count == length)
    {
        return Suc;
    }
    else
    {
        printf("Input contains non-alphabetic value.\n");
        return ERR;
    }
}

int ssn_validator(char *buffer, int length)
{
    int count = 0;

    if (length != SSN_Max)
    {
        printf("Citizenship number length must be 9.\n");
        return ERR;
    }

    for (int i = 0; i < SSN_Max; i++)
    {
        if (isdigit(buffer[i]))
        {
            count++;
        }
    }

    if (count == SSN_Max)
    {
        return Suc;
    }
    else
    {
        printf("Input contains non-numeric value.\n");
        return ERR;
    }
}

int dob_validator(char *buffer, int length)
{
    int count = 0;
    char day[2];
    char month[2];
    char year[4];

    if (length != DOB_Max)
    {
        printf("Name length must be 8.\n");
        return ERR;
    }

    for (int i = 0; i < length; i++)
    {
        if (isdigit(buffer[i]))
        {
            count++;
        }
    }

    if (count == length)
    {
        memcpy(month, buffer, 2);
        memcpy(day, &buffer[2], 2);
        memcpy(year, &buffer[4], 4);

        if ((atoi(month) > 0 || atoi(month) <= 12) &&
            (atoi(day) > 0 || atoi(day) <= 31) &&
            (atoi(year) > 0))
        {
            return Suc;
        }
        
        printf("Invalid Dates.\n");
        return ERR;
    }
    else
    {
        printf("Input contains non-numeric value.\n");
        return ERR;
    }
}

int phone_validator(char *buffer, int length)
{
    int count = 0;

    if (length != Phone_Max)
    {
        printf("Phone number length must be 10.\n");
        return ERR;
    }

    for (int i = 0; i < length; i++)
    {
        if (isdigit(buffer[i]))
        {
            count++;
        }
    }

    if (count == length)
    {
        return Suc;
    }
    else
    {
        printf("Input contains non-numeric value.\n");
        return ERR;
    }
}

int address_validator(char *buffer, int length)
{
    int count = 0;

    if (length > Addr_Max)
    {
        printf("Address length must be less than 80.\n");
        return ERR;
    }

    for (int i = 0; i < length; i++)
    {
        if (isalnum(buffer[i]) || 
            buffer[i] == ' ' ||
            buffer[i] == ',' ||
            buffer[i] == '.' ||
            buffer[i] == '-' ||
            buffer[i] == '#')
        {
            count++;
        }
    }

    if (count == length)
    {
        return Suc;
    }
    else
    {
        printf("Input contains invalid address value.\n");
        return ERR;
    }
}

int acc_type_validator(char *buffer, int length)
{
    if (length != 1)
    {
        printf("Account type length must be 1.\n");
        return ERR;
    }

    char temp = buffer[0] - '0';

    if (0 <= temp <= 4)
    {
        return Suc;
    }

    printf("Invalid Option.\n");
    return ERR;
}

int acc_bal_validator(char *buffer, int length)
{
    int count = 0;
    if (length >= Bal_Max)
    {
        printf("Balance length must be less than 50.\n");
        return ERR;
    }

    for (int i = 0; i < length; i++)
    {
        if (isdigit(buffer[i]))
        {
            count++;
        }
    }

    if (count == length)
    {
        return Suc;
    }
    else
    {
        printf("Input contains non-numeric value.\n");
        return ERR;
    }
}

char *get_user_info(int option)
{
    char buffer[256];
    int print_ret;
    char *fgets_ret = NULL;
    int val_ret;
    int length;
    int ssn;
    char *my_char = NULL;

    while (true)
    {
        memset(buffer, '\0', 256);
        print_ret = get_user_info_print1(option);
        if (print_ret == ERR)
        {
            return NULL;
        }

        fgets_ret = fgets(buffer, 256, stdin);
        length = strlen(buffer) - 1;

        if (NULL != fgets_ret)
        {
            switch (option)
            {
                case Name:
                    val_ret = name_validator(buffer, length);
                    break;
                case SSN:
                    val_ret = ssn_validator(buffer, length);
                    break;
                case DOB:
                    val_ret = dob_validator(buffer, length);
                    break;
                case Phone:
                    val_ret = phone_validator(buffer, length);
                    break;
                case Address:
                    val_ret = address_validator(buffer, length);
                    break;
                case Acc_Type:
                    val_ret = acc_type_validator(buffer, length);
                    break;
                case Acc_Bal:
                    val_ret = acc_bal_validator(buffer, length);
                    break;
                default:
                    printf("Unknown Option.\n");
                    return NULL;
            }

            if (val_ret == Suc)
            {
                break;
            }
        }
        else
        {
            printf("Scanf Malfunction. Try again.\n");
            return NULL;
        }
    }

    switch (option)
    {
        case Name:
            my_char = calloc(1, Name_Max + 1);
            break;
        case SSN:
            my_char = calloc(1, SSN_Max + 1);
            break;
        case DOB:
            my_char = calloc(1, DOB_Max + 1);
            break;
        case Phone:
            my_char = calloc(1, Phone_Max + 1);
            break;
        case Address:
            my_char = calloc(1, Addr_Max + 1);
            break;
        case Acc_Type:
            my_char = calloc(1, 2);
            break;
        case Acc_Bal:
            my_char = calloc(1, Bal_Max + 1);
            break;
        default:
            break;
    }

    if (NULL == my_char)
    {
        perror("Memory Allocation");
        return NULL;
    }

    memcpy(my_char, buffer, length);

    return my_char;
}