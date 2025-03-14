#include "singly.c"
#include <stdio.h>

int main() {
    list_t* list = list_alloc();
    printf("making sure, size: %zu\n", list->size);

    list_prepend(list, 5);
    list_prepend(list, 3);

    printf("prepended to list first: %d , then %d last\n", list->tail->data, list->head->data); // appending & prepending works
    // linked list is now (3, 5)

    list_append(list, 2);
    printf("the new tail node data is: %d\n", list->tail->data);
    // (3, 5, 2)


    list_insert(list, 8, 2);
    printf("the inserted node data is: %d\n", list->head->next->next->data); // inserting works
    // (3, 5, 8, 2)

    list_set(list, 7, 2);
    printf("the set node data is: %d\n", list->head->next->next->data);
    // (3, 5, 7, 2)
    list_set(list, 9, 9); // testing

    int removed_val;
    list_rm(list, &removed_val, 1);
    printf("the removed node data is: %d\n", removed_val); // removing is working
    // (3, 7, 2)

    int gotten_val;
    list_get(list, &gotten_val, 2);
    printf("the gotten node data is %d\n", gotten_val);
    // (3, 7, 2)

    printf("from head to tail: %d, %d, %d\n", list->head->data, list->head->next->data, list->tail->data);
    printf("the list size is: %zu", list->size);

    list_free(list); // must free the memory afterwards
    
    //system("leaks -atExit a.out");

    return 0;
}