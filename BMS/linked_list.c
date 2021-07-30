#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct _account
{
    int account_number;
    char * account_type;
    int balance;
} account;

typedef struct _customer
{
    char * name;
    int dob_month;
    int dob_day;
    int dob_year;
    double citizen_num;
    char * address;
    int phone_number;
    account customer_account;
} customer;


/**
 * @brief A struct that defines a node in the linked list.
 *
 */
typedef struct ll_node_t
{
    customer customer_data;
    struct ll_node_t *next;
} ll_node_t;

/**
 * @brief A struct that defines a pointer to the head node as well as
 *        additional metadata your linked list implementation contains.
 *
 */
typedef struct linked_list_t
{
    ll_node_t *head;
} linked_list_t;

linked_list_t *linked_list_new();

void linked_list_delete(linked_list_t **list);

size_t linked_list_size(linked_list_t *list);

//Linked List Structure that Containes all of the Users
//REF: JQR Item 3.3.2

/**
 * @brief Creates a newly allocated linked list
 *
 * The custom del and cmp functions are tailored to the data type or data structure
 * being stored in the linked list.  For simple data types, passing the standard free
 * function as the del parameter will usually suffice. These function pointers allow
 * the library user to store arbitrary data in the linked list.
 *
 * Asserts that the cmp function is not NULL.
 * If NULL is passed as the del parameter, implementation must set free as the default.
 *
 * @param del a function pointer to a custom free function tailored to
 * @param cmp a function pointer to a custom compare function
 * @return linked_list_t* a pointer to an allocated linked list object
 */
linked_list_t *linked_list_new(){
    linked_list_t *new = malloc (sizeof(linked_list_t));

    new->head = NULL;

    return new;
}

/**
 * @brief Destroy the list and all nodes it contains, deallocating any memory
 *        that was allocated.
 *
 * Asserts that list is not NULL, however *list == NULL is safe.
 * List pointer is set to NULL after memory is deallocated to
 * mitgate chance of Use-after-free bugs.
 *
 * @param list a reference to a pointer to an allocated list.
 */
void linked_list_delete(linked_list_t **list){
    assert(list != NULL);

    linked_list_t *the_list = *list;

    ll_node_t *current = the_list->head;
    ll_node_t *next;

    while(current != NULL){
        next = current->next;
        free(current);
        current = next;
    }

    //free(current);
    //free(next);
    free(the_list);
    the_list = NULL;
    *list = NULL;
}

void * add_node(linked_list_t *list, customer data)
{
    if(list == NULL)
    {
        return NULL;
    }

    ll_node_t * new_data = malloc(sizeof(ll_node_t));
    new_data->customer_data = data;
    new_data->next = NULL;

    ll_node_t * hold = list->head;

    if(hold == NULL)
    {
        list->head = new_data;
    }

    while(hold->next != NULL)
    {
        hold = hold->next;
    }

    hold->next = new_data;
}

/**
 * @brief Returns the number of nodes in the linked list
 *
 * Asserts that the list pointer is not NULL.
 *
 * @param list a pointer to an allocated linked list object
 * @return size_t the number of nodes in the linked list
 */
size_t linked_list_size(linked_list_t *list){
    assert(list != NULL);

    size_t size = 0;
    ll_node_t *current = list->head;

    while(current != NULL){
        size++;
        current = current->next;
    }

    return size;
}