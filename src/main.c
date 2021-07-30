#include "bank.c"

int main(void)
{
    char* a = get_name();
    printf("\n%s\n", a);
    free(a);
    return 0;
}