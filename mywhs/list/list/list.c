#include "list.h"

#include <malloc.h>

/**
 * list structure implementation
 */
typedef struct list {
    // main pointers
    node *head;
    node *last;

    // list length
    int len;
} list;

/**
 * Private zero element adder declaration
 * @param l list to add to note to
 * @param n node to add to list as zero element
 */
static void add_z(list *l, node *n);

/**
 * list constructor implementation
 */
list *list_new() {
    // Allocating memory
    list *l = (list *) malloc(sizeof(list));

    // Setting up length
    l->len = 0;

    // Setting pointers
    l->head = l->last = NULL;

    // Returning
    return l;
}

/**
 * list head getter
 */
node *list_head(const list *l) {
    return l->head;
}

/**
 * list last getter
 */
node *list_last(const list *l) {
    return l->last;
}

/**
 * list length getter
 */
int list_len(const list *l) {
    return l->len;
}

/**
 * Append implementation
 */
node *list_append(list *l, node *n) {
    // Checking for zero add
    if (l->len == 0) {
        add_z(l, n);
        return n;
    }

    // General list_append
    node_set_next(l->last, n);
    node_set_next(n, NULL);
    node_set_prev(n, l->last);
    l->last = n;
    l->len++;
    return n;
}

/**
 * list join implementation
 */
list *list_join(list *parts) {
    // Creating list to store result
    list *result = list_new();

    // Appending temp element
    list_append(result, node_new(NULL, -1));

    // Appending parts
    node *current_parts_node = list_head(parts);
    list *current_list;
    while(current_parts_node != NULL) {
        // Obtaining current part
        current_list = (list *) node_value(current_parts_node);

        // Checking length
        if (list_len(current_list) == 0) {
            // Zero -> ignore, move forward
            current_parts_node = node_next(current_parts_node);
            continue;
        }

        // Not zero, appending
        result->len += current_list->len;
        node_set_next(result->last, current_list->head);
        node_set_prev(current_list->head, result->last);
        result->last = current_list->last;
        current_parts_node = node_next(current_parts_node);
    }

    // Removing temp element
    if (result->len == 1) {
        free(result->head);
        result->head = result->last = NULL;
        result->len = 0;
    } else {
        result->head = node_next(result->head);
        free(node_prev(result->head));
        result->len--;
    }

    // Returning
    return result;
}

/**
 * list destructor implementation
 */
list *list_free(list *l, void(*free_node_value)(void *)) {
    // No list -> do nothing
    if (l == NULL) {
        return NULL;
    }

    // empty list -> just free it
    if (l->len == 0) {
        free(l);
        return NULL;
    }

    // General liberation
    node *current = l->head;
    while (current != NULL)
    {
        node *temp = current;
        current = node_next(current);
        free_node_value(node_value(temp));
        free(temp);
    }
    free(l);

    // Returning
    return NULL;
}

/**
 * Private zero element adder implementation
 */
static void add_z(list *l, node *n) {
    node_set_next(n, NULL);
    node_set_prev(n, NULL);

    l->head = n;
    l->last = n;
    l->len++;
}

