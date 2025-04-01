#include "doubly.h"
#include <stdio.h>
#include <stdlib.h>

void free_data(void *data);
int** matrix(int x);
void print_matrix(void *data);

int main() {
    list_t* list = list_alloc();
    printf("making sure list is empty: %zu\n", list->size); // good to go

    list_prepend(list, matrix(1));
    print_matrix(list->tail->data);
    // list: 1

    list_prepend(list, matrix(2));
    print_matrix(list->head->data); // prepend working
    print_matrix(list->tail->prev->data); // prev pointer working
    // list: 2, 1

    list_append(list, matrix(3));
    print_matrix(list->tail->data); // append working
    print_matrix(list->head->next->next->data); // next pointer working
    // list: 2, 1, 3

    list_insert(list, matrix(4), 2);
    print_matrix(list->head->next->next->data); // insert working
    print_matrix(list->tail->prev->data); // prev pointer working
    // list: 2, 1, 4, 3

    list_insert(list, matrix(5), 5); // invalid position working

    list_set(list, matrix(9), 2);
    print_matrix(list->head->next->next->data); // set working
    print_matrix(list->tail->prev->data); // prev pointer working
    // list: 2, 1, 9, 3

    void *gotten_val;
    list_get(list, &gotten_val, 2);
    printf("The gotten node data pointer is: %p\n", gotten_val); // working
    print_matrix(gotten_val);

    void *removed_val;
    list_rm(list, &removed_val, 2);
    printf("the removed node data is: %p\n", removed_val); // working
    print_matrix(removed_val);
    free(removed_val); // Free the removed data
    // list: 2, 1, 3

    printf("Iterating through the list:\n");
    node_t *current = list->head;
    while (current != NULL) {
        print_matrix(current->data);
        current = current->next;
    } // CORRECT!

    printf("Removing all nodes in the list:\n");
    while (list->size > 0) {
        list_rm(list, &removed_val, 0);
        print_matrix(removed_val);
        free(removed_val);
    }

    printf("Checking...\n");
    node_t *temp = list->head;
    while (temp != NULL) {
        print_matrix(temp->data);
        temp = temp->next;
    } // CORRECT!

    list_free(list, free_data); // working

    return 0;
}

// write your own print function for this data type
void print_matrix(void *data) {
    int **matrix = (int **)data; // cast void* to int**
    /*
        int a;
        double b;
        int c;
        c = a + b; // WRONG (compiler will get mad)
        c = a + (int)b;
    */

    for (int i = 0; i < 3; i++) { // nested loop to print each element
        for (int j = 0; j < 3; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

int** matrix(int x) {
    int **arr = malloc(3 * sizeof(int *));

    for (int i = 0; i < 3; i++) {
        *(arr + i) = malloc(3 * sizeof(int));

        for (int j = 0; j < 3; j++) {
            *(*(arr + i) + j) = x;
            //arr[i][j] = x;
            //arr[i] -> *(arr +i) // block of 3 integers
        }
    }

    return arr;
}

void free_data(void *data) {
    free(data);
}