#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>

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

int main (void)
{
    FILE *fp = 0;
    unsigned char * file_contents = malloc(sizeof(char) * MAX_BUFF);
    char * rest = NULL;
    int location = 0;

    user_node_t test_user = {0};

    fp = open_file("test.txt");

    puts("File Opened");

    while(fgets(file_contents, MAX_BUFF, fp) != NULL)
    {

        location = ftell(fp);
        printf("Location %d \n", location);

        test_user.username_length = (uint16_t) strtok_r(file_contents, ",", &rest);
        printf("%d",test_user.username_length );

        test_user.username = strtok_r(NULL,",", &rest);
        printf("\t%s",test_user.username);

        test_user.password_length = strtok_r(NULL,",", &rest);
        printf("\t%d",test_user.password_length);

        test_user.password = strtok_r(NULL,",", &rest);
        printf("\t%s \n",test_user.password);
    }

    free(file_contents);
    fclose(fp);

    return EXIT_SUCCESS;
}