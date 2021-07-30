#include "helper.h"

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
            if (length != 9)
            {
                printf("Citizenship number length must be 9.\n");
                continue;
            }

            for (int i = 0; i < 9; i++)
            {
                if (isdigit(buffer[i]))
                {
                    count++;
                }
            }

            if (count == 9)
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
            if (length > 20)
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
 * Get name from user and return the name array
 * @return name array on success, NULL for errors
 */
char *get_dob(void)
{

}