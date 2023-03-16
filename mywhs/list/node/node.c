#include "node.h"

#include <malloc.h>
#include <memory.h>

/**
 * node structure implementation
 */
typedef struct node {
    // value properties
    void *value;
    int size;

    // list pointers
    struct node *next;
    struct node *prev;
} node;

/**
 * Private node by pointer constructor
 * Creates new node with given pointer as value (no copy)
 * @param value pointer to use as node value
 * @return new node instance
 */
static node *new_node_by_p(const void *value);

/**
 * Private node by value constructor
 * Creates new node with shallow copy of memory,
 * pointed by value pointer, of size size
 * @param value pointer, points to memory to use as node's value
 * @param size amount of bytes to copy to node value
 */
static node *new_node_by_v(const void *value, const int size);

/**
 * node constructor implementation
 */
node *node_new(const void *value, const int size) {
    if (size == -1)
    {
        return new_node_by_p(value);
    }
    return new_node_by_v(value, size);
}

/**
 * node value getter implementation
 */
void *node_value(const node *n) {
    return n->value;
}

/**
 * node value size getter implementation
 */
int node_size(const node *n) {
    return n->size;
}

/**
 * next node getter
 */
node *node_next(const node *n) {
    return n->next;
}

/**
 * prev node getter
 */
node *node_prev(const node *n) {
    return n->prev;
}

/**
 * next node setter
 */
node *node_set_next(node *n, const node *next_node) {
    n->next = next_node;
    return n;
}

/**
 * prev node setter
 */
node *node_set_prev(node *n, const node *prev_node) {
    n->prev = prev_node;
    return n;
}

/**
 * Private node by pointer constructor implementation
 */
static node *new_node_by_p(const void *value) {
    // Create new n
    node *n = (node *)malloc(sizeof(node));
    n->value = value;
    n->size = -1;

    // Setting node pointers
    n->next = n->prev = NULL;

    // Returning _result
    return n;
}

/**
 * Private node by value constructor implementation
 */
static node *new_node_by_v(const void *value, const int size) {
    // Create new n
    node *n = (node *) malloc(sizeof(node));
    n->value = malloc(size);
    n->size = size;

    // Copy value to new n
    memcpy(n->value, value, size);

    // Setting node pointers
    n->next = n->prev = NULL;

    // Returning _result
    return n;
}
