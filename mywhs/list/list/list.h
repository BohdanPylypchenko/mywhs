#ifndef MYWHS_DEMO_LIST_H
#define MYWHS_DEMO_LIST_H

#include "../node/node.h"

/**
 * Double linked list declaration
 */
typedef struct list list;

/**
 * list constructor
 * @return new empty linked list
 */
list *list_new();

/**
 * list head getter
 * @param l list to get head from
 * @return head of list as node instance
 */
node *list_head(const list *l);

/**
 * list last getter
 * @param l list to get head from
 * @return last element of list as node
 */
node *list_last(const list *l);

/**
 * list length getter
 * @param l list to get head from
 * @return length of list
 */
int list_len(const list *l);

/**
 * Appends node to end of given list
 * @param l list to append to
 * @param n note to append
 */
node *list_append(list *l, node *n);

/**
 * Join 2-dimensional linked list (list of lists) into single list
 * @param parts 2-dimensional linked list to take lists from
 * @return single linked list, result of joining parts together
 */
list *list_join(list *parts);

/**
 * list destructor
 * @param l list to destruct
 * @param free_node_value function pointer to deallocate nodes with
 * @return NULL if successfully deallocated list, if failed - undefined
 */
list *list_free(list *l, void(*free_node_value)(void *));

#endif
