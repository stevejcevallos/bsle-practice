#include "bank.h"

/** 
 * Get SSN string and return SSN integer
 * @return SSN integer on success, -1 for errors
 */
int get_ssn(void)
{
    char buffer[256];
    int ret = 0;
    int length;
    int count = 0;
    int ssn;

    while (true)
    {
        count = 0;
        memset(buffer, 0, 256);
        printf("Type SSN: (9 digits)\n");
        ret = scanf("%s", buffer);
        if (ret == 1)
        {
            length = strlen(buffer);
            if (length != SSN_Max)
            {
                printf("Citizenship number length must be 9.\n");
                continue;
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
                break;
            }
            else
            {
                printf("Input contains non-numeric value.\n");
            }
        }
        else
        {
            printf("Scanf Malfunction. Try again.\n");
            return -1;
        }
    }

    ssn = atoi(buffer);
    return ssn;
}

/** 
 * Get name from user and return the name array
 * @return name array on success, NULL for errors
 */
char *get_name(void)
{
    char buffer[256];
    char *ret;
    int length;
    int count = 0;
    char *name;

    while (true)
    {
        count = 0;
        memset(buffer, '\0', 256);
        printf("Type Name: (Max: 20)\n");
        ret = fgets(buffer, 256, stdin);
        length = strlen(buffer) - 1;

        if (NULL != ret)
        {
            if (length > Name_Max)
            {
                printf("Name length must be less than 20.\n");
                continue;
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
                break;
            }
            else
            {
                printf("Input contains non-alphabetic value.\n");
            }
        }
        else
        {
            printf("Command Line Input Error. Try again.\n");
            return NULL;
        }
    }

    name = calloc(1, Name_Max + 1);
    if (NULL == name)
    {
        perror("Memory Allocation");
        return NULL;
    }
    memcpy(name, buffer, Name_Max);
    name[Name_Max] = '\0';

    return name;
}

/** 
 * Get date of birth from user and return the DOB array
 * @return DOB array on success, NULL for errors
 */
char *get_dob(void)
{
    char buffer[256];
    char *ret;
    int length;
    int count = 0;
    char *dob;
    char day[2];
    char month[2];
    char year[4];

    while (true)
    {
        count = 0;
        memset(buffer, '\0', 256);
        printf("Type Date of Birth: (Format: MMDDYYYY)\n");
        ret = fgets(buffer, 256, stdin);
        length = strlen(buffer) - 1;

        if (NULL != ret)
        {
            if (length != DOB_Max)
            {
                printf("Name length must be 8.\n");
                continue;
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
                    break;
                }
                
                printf("Invalid Dates.\n");
            }
            else
            {
                printf("Input contains non-numeric value.\n");
            }
        }
        else
        {
            printf("Command Line Input Error. Try again.\n");
            return NULL;
        }
    }

    dob = calloc(1, DOB_Max + 1);
    if (NULL == dob)
    {
        perror("Memory Allocation");
        return NULL;
    }
    memcpy(dob, buffer, DOB_Max);
    dob[DOB_Max] = '\0';

    return dob;
}

/** 
 * Get address from user and return the address array
 * @return address array on success, NULL for errors
 */
char *get_address(void)
{
    char buffer[256];
    char *ret;
    int length;
    int count = 0;
    char *address;

    while (true)
    {
        count = 0;
        memset(buffer, '\0', 256);
        printf("Type Address: (Max: 80)\n");
        ret = fgets(buffer, 256, stdin);
        length = strlen(buffer) - 1;

        if (NULL != ret)
        {
            if (length > Addr_Max)
            {
                printf("address length must be less than 80.\n");
                continue;
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
                break;
            }
            else
            {
                printf("Input contains invalid address value.\n");
            }
        }
        else
        {
            printf("Command Line Input Error. Try again.\n");
            return NULL;
        }
    }

    address = calloc(1, Addr_Max + 1);
    if (NULL == address)
    {
        perror("Memory Allocation");
        return NULL;
    }
    memcpy(address, buffer, Addr_Max);
    address[Addr_Max] = '\0';

    return address;
}

/** 
 * Get phone number from user and return the phone number
 * @return address array on success, NULL for errors
 */
char *get_phone(void)
{
    char buffer[256];
    char *ret;
    int length;
    int count = 0;
    char *p_num;

    while (true)
    {
        count = 0;
        memset(buffer, '\0', 256);
        printf("Type Phone Number: (10 digits)\n");
        ret = fgets(buffer, 256, stdin);
        length = strlen(buffer) - 1;

        if (NULL != ret)
        {
            if (length != Phone_Max)
            {
                printf("Phone number length must be 10.\n");
                continue;
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
                break;
            }
            else
            {
                printf("Input contains non-numeric value.\n");
            }
        }
        else
        {
            printf("Command Line Input Error. Try again.\n");
            return NULL;
        }
    }

    p_num = calloc(1, Phone_Max + 1);
    if (NULL == p_num)
    {
        perror("Memory Allocation");
        return NULL;
    }
    memcpy(p_num, buffer, Phone_Max);
    p_num[Phone_Max] = '\0';

    return p_num;
}

/** 
 * Get deposit account information from user 
 * and generate the account structure
 * @return account_t structure on success, NULL for errors
 */
account_t *new_account(void)
{
    char temp;
    char buffer[256];
    char *ret;
    int length;
    int count = 0;
    account_t *new;

    while (true)
    {
        printf("Type Account Type: (0: Saving, 1: Current, 2: Fixed_1yr 3: Fixed_2yr, 4: Fixed_3yr)\n");
        temp = getchar();
        if (temp)
        {
            if (temp - '0' < 0 || temp -'0' > 4)
            {
                printf("Invalid Option.\n");
            }
            else
            {
                break;
            }
        }
        else
        {
            printf("Input is non-digit.\n");
        }
    }

    while (true)
    {
        count = 0;
        memset(buffer, '\0', 256);
        printf("Type Balance of Account: (Max: 50 digits)\n");
        ret = fgets(buffer, 256, stdin);
        length = strlen(buffer) - 1;

        if (NULL != ret)
        {
            if (length >= Bal_Max)
            {
                printf("Balance length must be less than 80.\n");
                continue;
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
                break;
            }
            else
            {
                printf("Input contains non-numeric value.\n");
            }
        }
        else
        {
            printf("Command Line Input Error. Try again.\n");
            return NULL;
        }
    }

    new = calloc(1, sizeof(account_t));
    if (NULL == new)
    {
        return NULL;
    }
    new->acc_type = temp - '0';
    new->balance = atoi(buffer);
    new->next = NULL;

    return new;
}