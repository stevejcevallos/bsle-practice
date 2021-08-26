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

int change_values_in_files(FILE * fp, uint16_t test_value)
{

    char * rest = NULL;
    char * endptr = NULL;
    char * token = NULL;
    uint16_t item_length = 0;
    size_t buffer_size = 256;
    char * file_contents = NULL;
    int location = 0;
    char writing_this[] = "Test";

    puts("File Opened");

    while(EOF != (location = getline(&file_contents, &buffer_size, fp)))
    {
        printf("\nByte Size at: %d \n", location);
        printf("BUFF %s \n", file_contents);

        item_length = strtol(strtok_r(file_contents, ",", &rest), &endptr, 10);
        if(0 == item_length)
        {
            if(EINVAL == errno)
            {
                perror("Conversion Error");
                exit(EXIT_FAILURE);
            }
        }

        //The value is the same to the one I am looking for
        if(item_length == test_value)
        {
            printf("Location of the pointer %ld \n", ftell(fp));
            fwrite(writing_this, 1, sizeof(writing_this), fp);
        }
    }

    free(file_contents);
    fclose(fp);

    return EXIT_SUCCESS;
}

int print_file_by_tokens(FILE * fp)
{
    char * rest = NULL;
    char * endptr = NULL;
    char * token = NULL;
    uint16_t item_length = 0;
    size_t buffer_size = 256;
    char * file_contents = NULL;
    int32_t bytes_read = 0;

    puts("File Opened");

    while(EOF != (bytes_read = getline(&file_contents, &buffer_size, fp)))
    {
        printf("\nBytes Read: %d \n", bytes_read);

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
    //change_values_in_files(fp, 2);

    exit(EXIT_SUCCESS);
}