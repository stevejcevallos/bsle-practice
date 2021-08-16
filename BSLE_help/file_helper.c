#include <stdlib.h>
#include <stdio.h>

/**
 * @brief Opens the given file name for r+, will need for later closing
 *
 * @param file_name of the file to open
 *
 * @return: returns fp to work with
*/
int open_file(char *filename)
{
    FILE *fp;
    fp = fopen(filename, "r+");

    if(fp == NULL)
    {
        perror("Failed to open the specified filename");
        return -1;
    }

    return fp;
}