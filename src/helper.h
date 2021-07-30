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

int get_ssn(void);

char *get_name(void);

#endif // OTHER _H_INCLUDED