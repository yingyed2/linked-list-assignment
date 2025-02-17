#include <stddef.h>

// creating a single node
typedef struct node_s {
    int data;
    struct node_s *next;
} node_t;

// linked list itself
typedef struct list_s {
        node_t *head;
        node_t *tail;
        size_t size;
} list_t;

// allocating memory for the linked list
list_t *list_alloc(void) {
    list_t *list = malloc(sizeof(list_t));
    if (list) { // ensures we start from clean slate
        list->head = NULL;
        list->tail = NULL;
        list->size = 0;
    }
    return list;
}

// freeing the entire list of memory
void list_free(list_t *list) {
    node_t *node = list->head; // must access the head node first
    while (node) { // iteratively freeing each node
        node_t *tmp = node;
        node = node->next;
        free(tmp);
    }
    free(list); // freeing the list itself
}

// adding a node to the front of the list
int list_prepend(list_t *list, int val) {
    node_t *node = malloc(sizeof(node_t));
    if (!node) return -1; // malloc failed
    node->data = val; // assign parameter value to node
    node->next = list->head; // point to the old head
    list->head = node; // updates the head to the new node
    if (list->size == 0) list->tail = node; // if list was empty, update tail
    list->size++; // increments by 1 bc we added a new node
    return 0;
}

// adding a node to the end of the list
int list_append(list_t *list, int val) {
    node_t *node = malloc(sizeof(node_t));
    if (!node) return -1; // malloc failed
    node->data = val; // assign parameter value to node
    node->next = NULL; // point to NULL since it will be the last node
    if (list->size == 0) { // if list is empty, update head and tail
        list->head = node;
        list->tail = node;
    } else { // otherwise, add to the end and update tail
        list->tail->next = node;
        list->tail = node;
    }
    list->size++; // increments by 1 bc we added a new node
    return 0;
}

// insert a node in a specific position of the linked list
int list_insert(list_t *list, int val, size_t pos) {
    if (pos == 0) return list_prepend(list, val); // first position is the same as prepending
    if (pos >= list->size) return list_append(list, val); // last position is the same as appending
    
    node_t *node = malloc(sizeof(node_t)); // allocating memory for the new node
    if (!node) return -1; // malloc failed
    node->data = val; // assign parameter value to node

    node_t *current = list->head; // begins at the head
    for (size_t i = 0; i < pos - 1; i++) { // iteratively traverses the nodes until it reaches the node before the position
        current = current->next;
    }

    node->next = current->next; // point to the node after the position
    current->next = node; // updates current pointer to point to the new node
    list->size++;

    return 0;
}

// remove a node from a specific position of the linked list
int list_rm(list_t *list, int *val, size_t pos) {
    if (list->size == 0) return -1; // list is empty

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
        if (pos == list->size - 1) //if the last node was removed, update tail
            list->tail = current;
    }

    free(remove); // freeing the node
    list->size--;

    return 0;
}


int list_set(list_t *list, int val, size_t pos) {
    if (pos >= list->size) return -1; // invalid position

    node_t *current = list->head;
    for (size_t i = 0; i < pos; i++) { // iteratively traverses the nodes until it reaches the position
        current = current->next;
    }

    current->data = val; // updates the node's value

    return 0;
}


int list_get(list_t *list, int *val, size_t pos) {
    if (pos >= list->size) return -1; // invalid position

    node_t *current = list->head;
    for (size_t i = 0; i < pos; i++) { // iteratively traverses the nodes until it reaches the position
        current = current->next;
    }

    *val = current->data; // stores the node's value in the parameter

    return 0;
}