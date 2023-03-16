#ifndef MYWHS_DEMO_NODE_H
#define MYWHS_DEMO_NODE_H

/**
 * node structure declaration
 */
typedef struct node node;

/**
 * node constructor
 * value store strategy (store pointer vs perform shallow copy)
 * is defined by size value
 * @param value value to store in node
 * @param size pass -1 if pointer storage is needed
 *             pass value byte size if shallow copy strategy is needed
 * @return new node instance
 */
node *node_new(const void *value, const int size);

/**
 * node value getter
 * @param n note to get value from
 * @return
 */
void *node_value(const node *n);

/**
 * node value size getter
 */
int node_size(const node *n);

/**
 * next node getter
 * @param n node to get next from
 * @return next node pointer
 */
node *node_next(const node *n);

/**
 * previous node getter
 * @param n node to get previous from
 * @return previous node pointer
 */
node *node_prev(const node *n);

/**
 * next node setter
 * @param n node to set next for
 * @param next_node node to set as next
 * @return n node reference
 */
node *node_set_next(node *n, const node *next_node);

/**
 * previous node setter
 * @param n node to set previous for
 * @param prev_node node to set as previous
 * @return n node reference
 */
node *node_set_prev(node *n, const node *prev_node);

#endif
