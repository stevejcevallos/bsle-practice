#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <errno.h>

#define MAX_BUFF 256

/**
 *
 * @brief CONTAINS ALL OF THE USER INFORMATION
 *
**/
typedef struct _user_node_t
{
    unsigned char * username;
    unsigned char * password;
    uint16_t username_length;
    uint8_t password_length;
}user_node_t;


/**
 * @brief Opens the given file name for r+, will need for later closing
 *
 * @param file_name of the file to open
 *
 * @return: returns fp to work with, if failed return NULL
*/
FILE * open_file(char *filename)
{
    FILE *fp;
    fp = fopen(filename, "r+");

    if(fp == NULL)
    {
        perror("Failed to open the specified filename");
        return NULL;
    }

    return fp;
}

int print_file_by_tokens(FILE * fp)
{
    unsigned char * file_contents = malloc(sizeof(char) * MAX_BUFF);
    char * rest = NULL;
    char * endptr = NULL;
    char * token = NULL;
    uint16_t item_length = 0;
    int location = 0;

    puts("File Opened");

    while(fgets(file_contents, MAX_BUFF, fp) != NULL)
    {

        location = ftell(fp);
        printf("\nLine Ends at: %d \n", location);

        item_length = strtol(strtok_r(file_contents, ",", &rest), &endptr, 10);
        if(0 == item_length)
        {
            if(EINVAL == errno)
            {
                perror("Conversion Error");
                exit(EXIT_FAILURE);
            }
        }
        printf("\t%d",item_length);

        token = strtok_r(NULL,",", &rest);
        printf("\t%s",token);

        item_length = strtol(strtok_r(NULL, ",", &rest), &endptr, 10);
        if(0 == item_length)
        {
            if(EINVAL == errno)
            {
                perror("Conversion Error");
                exit(EXIT_FAILURE);
            }
        }
        printf("\t%d",item_length);

        token = strtok_r(NULL,",", &rest);
        printf("\t%s \n",token);
    }
    free(file_contents);
    fclose(fp);

    return EXIT_SUCCESS;
}

int main (void)
{
    FILE *fp = 0;
    fp = open_file("test.txt");
    print_file_by_tokens(fp);

    exit(EXIT_SUCCESS);
}