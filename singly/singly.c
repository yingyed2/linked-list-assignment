#include "singly.h"
#include <stdlib.h>
#include <stdio.h>


// creates a new linked list
list_t *list_alloc(void) {
    list_t *list = malloc(sizeof(list_t)); // block of memory allocated to list
    printf("allocated list\n");
    if (list != NULL) { // if malloc doesn't return NULL (doesn't fail)
        list->head = NULL;
        list->tail = NULL;
        list->size = 0;
    } // ensures that the list is empty and size is 0
    return list; // returns the created list as the function type is list_t
}

// clears the data of the list
void list_free(list_t *list) {
    node_t *node = list->head;
    while (node != NULL) { // when the node exists
        node_t *walker = node; // creates a temp variable to iterate through the list
        node = node->next;
        free(walker); // frees current temp variable for one iteration
    }
    free(list); // frees the linked list itself
}

// adding a node to the beginning of the linked list, with its pointer connected to the original list's head node
int list_prepend(list_t *list, int val) { // user passes in a linked list and integer value argument to be prepended
    node_t *node = malloc(sizeof(node_t)); // allocates memory for new node to be prepended
    if (node != NULL) {
        if (list->size == 0) {
            printf("empty list\n");
            list->head = node;
            list->tail = node;
            node->data = val;
            list->size++;
        }
        else {
            node->data = val; // data of the argument is assigned to new prepended node
            node->next = list->head; // prepended node points to list's old head
            list->head = node; // list's head node is now assigned to new node
            list->size++;
        }
    }
    return 0; // success
}

// adding a node to the end of the linked list, with the original list's tail node's next pointer pointing the the new node
int list_append(list_t *list, int val) {
    node_t *node = malloc(sizeof(node_t)); // allocates memory for new node to be appended
    printf("allocated node\n");
    if (node != NULL) {
        if (list->size == 0) {
            printf("empty list\n");
            list->head = node;
            list->tail = node;
            node->data = val;
            list->size++; // updating size of the list because a new node was added

        }
        else {
            node->data = val;
            node->next = NULL; // because it is a tail node
            list->tail->next = node; // updating original linked list's tail node to the new node
            list->tail = node;
            list->size++; // updating size of the list because a new node was added
        }
    }
    else {
        printf("failed to allocate node\n");
        return 1; // failure to create node
    }
    return 0;
}

// // adding a node to a specified position in a linked list
int list_insert(list_t *list, int val, size_t pos) {
    if (pos == 0) {
        return list_prepend(list, val); // call prepend function if position is the beginning of the linked list
    }
    else if (pos >= sizeof(list) - 1) {
        return list_append(list, val); // call append function if position is the end of the linked list
    }

    node_t *node = malloc(sizeof(node_t)); // sequenced after conditional statements to prevent 2 nodes from being created
    if (node == NULL) {
        return 1; // failure
    }
    else {
    node_t *walker = list->head; // begin at the list's head
    for (int i = 0; i < pos - 1; i++) {
        walker = walker->next; // temporary node moving to the next node
    }
    node->data = val;
    node->next = walker->next; // reassigning the pointers
    walker->next = node;
    list->size++;}
    return 0;
}

// // unlinks a node from a linked list
int list_rm(list_t *list, int *val, size_t pos) {
    if (list->size == 0) {
        return -1; // list is empty
    }
    
    node_t *remove;
    if (pos == 0) { // remove head node
        remove = list->head; // points to the head
        *val = remove->data; // removes data of the head node
        list->head = list->head->next; // next node becomes the new head node
        if (list->size == 1) { // if there was only 1 node, update tail to NULL
            list->tail = NULL;
        }
    } else {
        node_t *current = list->head;
        for (size_t i = 0; i < pos - 1; i++) { // iteratively traverses the nodes until it reaches the node before the position
            current = current->next;
        }
        remove = current->next; // points to the node to be removed
        *val = remove->data; // stores data in the parameter to be removed
        current->next = remove->next; // updates current pointer to point to the node after the position
        if (pos == list->size - 1) // if the last node was removed, update tail
            list->tail = current;
    }

    free(remove); // freeing the node
    list->size--;

    return 0;
}

// // assign new data to specified node
int list_set(list_t *list, int val, size_t pos) {
    if (pos >= list->size) {
        printf("invalid positoin.\n");
        return 1;
    }
    
    else {
    node_t *walker = list->head;
    for (int i = 0; i < pos; i++) {
        walker = walker->next;
    }
    walker->data = val; // sets new data
    }
    return 0;
}


// // retrieve data of a specified node
int list_get(list_t *list, int *val, size_t pos) {
    if (pos >= list->size) { // invalid position
        printf("invalid position.\n");
        return 1;
    }

    node_t *walker = list->head;
    for (size_t i = 0; i < pos; i++) {
        walker = walker->next;
    }
    *val = walker->data; // correctly retrieve the data

    return 0;
}