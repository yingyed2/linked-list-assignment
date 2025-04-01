#include <stddef.h>

// a node structure with a void pointer with pointers to the next and prev nodes
typedef struct node_s {
    void *data;
    struct node_s *prev;
    struct node_s *next;
} node_t;

// same as a singly list structure
typedef struct list_s {
    node_t *head;
    node_t *tail;
    size_t size;
} list_t;

// functions to implement
list_t *list_alloc(void);
void list_free(list_t *list, void (*free_data)(void *data));
int list_prepend(list_t *list, void *val);
int list_append(list_t *list, void *val);
int list_insert(list_t *list, void *val, size_t pos);
int list_rm(list_t *list, void **val, size_t pos);
int list_set(list_t *list, void *val, size_t pos);
int list_get(list_t *list, void **val, size_t pos);