#include "doubly.h"
#include <stdio.h>
#include <stdlib.h>

// works the same as a singly linked list
list_t *list_alloc(void) {
    list_t *list = malloc(sizeof(list_t));
    printf("list has been allocated\n");
    if (list) {
        list->head = NULL;
        list->tail = NULL;
        list->size = 0;
    }
    return list;
}


void list_free(list_t *list, void (*free_data)(void *data)) {
    node_t *node = list->head;
    while (node != NULL) {
        node_t *walker = node;
        node = node->next;

        if (free_data != NULL) {
            free_data(walker->data);
        }

        free(walker);
    }
    free(list);
}


int list_prepend(list_t *list, void *val) {
    node_t *node = malloc(sizeof(node_t));
    if (node != NULL) {
        node->data = val;
        node->prev = NULL; // new head node has no previous node
        if (list->size == 0) {
            printf("empty list right now!\n");
            node->next = NULL; // only node in the list
            list->head = node;
            list->tail = node;
        } else {
            node->next = list->head; // point to the old head
            list->head->prev = node; // update old head's prev pointer
            list->head = node;       // update head pointer
        }
        list->size++;
    } else {
        printf("node couldn't be created");
        return 1;
    }
    return 0;
}


int list_append(list_t *list, void *val) {
    node_t *node = malloc(sizeof(node_t));
    if (node != NULL) {
        node->data = val;
        node->next = NULL;
        if (list->size == 0) {
            printf("empty list right now!\n");
            node->prev = NULL; // only node in the list
            list->head = node;
            list->tail = node;
        } else {
            node->prev = list->tail; // Point to the old tail
            list->tail->next = node; // update old tail's next pointer
            list->tail = node;       // update tail pointer
        }
        list->size++;
    } else {
        printf("node couldn't be created");
        return 1;
    }
    return 0;
}


int list_insert(list_t *list, void *val, size_t pos) {
    if (pos > list->size) {
        printf("invalid position.\n");
        return 1;
    }
    if (pos == 0) {
        return list_prepend(list, val);
    }
    if (pos == list->size) {
        return list_append(list, val);
    }

    node_t *node = malloc(sizeof(node_t));
    if (node == NULL) {
        printf("node couldn't be created.\n");
        return 1;
    }

    node_t *walker;
    if (pos < list->size / 2) {
        walker = list->head;
        for (size_t i = 0; i < pos - 1; i++) {
            walker = walker->next;
        }
    } else {
        walker = list->tail;
        for (size_t i = list->size - 1; i > pos - 1; i--) {
            walker = walker->prev;
        }
    }

    node->data = val;
    node->next = walker->next;
    node->prev = walker;

    if (walker->next != NULL) {
        walker->next->prev = node; // update the prev pointer of the next node
    }
    walker->next = node; // update the next pointer of the current node

    list->size++;
    return 0;
}


int list_rm(list_t *list, void **val, size_t pos) {
    if (list->size == 0) {
        return -1; // List is empty
    }

    node_t *remove;
    if (pos == 0) {
        remove = list->head;
        *val = remove->data;
        list->head = list->head->next;
        if (list->head != NULL) {
            list->head->prev = NULL;
        } else {
            list->tail = NULL;
        }
    } else if (pos == list->size - 1) {
        remove = list->tail;
        *val = remove->data;
        list->tail = list->tail->prev;
        if (list->tail != NULL) {
            list->tail->next = NULL;
        } else {
            list->head = NULL;
        }
    } else {
        node_t *walker;
        if (pos < list->size / 2) {
            walker = list->head;
            for (size_t i = 0; i < pos; i++) {
                walker = walker->next;
            }
        } else {
            walker = list->tail;
            for (size_t i = list->size - 1; i > pos; i--) {
                walker = walker->prev;
            }
        }
        remove = walker;
        *val = remove->data;
        walker->prev->next = walker->next;
        walker->next->prev = walker->prev;
    }

    free(remove);
    list->size--;
    return 0;
}


int list_set(list_t *list, void *val, size_t pos) {
    if (pos >= list->size) {
        printf("invalid positoin.\n");
        return 1;
    }

    node_t *walker;
    if (pos < list->size / 2) {
        walker = list->head;
        for (size_t i = 0; i < pos; i++) { // start from the head if the position is in the first half
            walker = walker->next;
        }
    } else {
        walker = list->tail;
        for (size_t i = list->size - 1; i > pos; i--) { // start from the tail if the position is in the second half
            walker = walker->prev;
        }
    }

    walker->data = val;
    return 0;
}

// bi-directionally traversing the list
int list_get(list_t *list, void **val, size_t pos) {
    if (pos >= list->size) {
        printf("invalid positoin.\n");
        return 1;
    }

    node_t *walker;
    if (pos < list->size / 2) {
        walker = list->head;
        for (size_t i = 0; i < pos; i++) { // start from the head if the position is in the first half
            walker = walker->next;
        }
    } else {
        walker = list->tail;
        for (size_t i = list->size - 1; i > pos; i--) { // start from the tail if the position is in the second half
            walker = walker->prev;
        }
    }

    *val = walker->data;
    return 0;
}