#include "helper.h"

// Get SSN string and return SSN integer
int ssn_helper(void)
{
    char buffer[256];
    int ret = 0;
    int length;
    int count = 0;
    int ssn;

    while (true)
    {
        printf("Type SSN: (9 digits)\n");
        ret = scanf("%s", &buffer);
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
        }
    }

    return atoi(buffer);
}

char *