#include "bank.c"

int main(void)
{
    account_t* a = new_account();
    printf("\n%d\n", a->acc_type);
    printf("\n%d\n", a->balance);
    free(a);
    return 0;
}