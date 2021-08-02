#include "bank.c"

int main(void)
{
    user_t* a = new_acc();
    if (NULL == a)
    {
        return ERR;
    }
    int ret = view_list(a);
    destroy_user(a);

    if (ret == ERR)
    {
        return ERR;
    }
    

    return Suc;
}