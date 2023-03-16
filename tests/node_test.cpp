#include "gtest/gtest.h"

extern "C" {
#include "list/node/node.h"
}

/*
 * node creation by pointer test
 */
TEST(node, pointer_creation) {
    char original_value = 'v';
    node *n = node_new(&original_value, -1);

    ASSERT_EQ('v', *((char *) node_value(n)));
    ASSERT_EQ(-1, node_size(n));
    ASSERT_EQ(NULL, node_next(n));
    ASSERT_EQ(NULL, node_prev(n));

    original_value = 'a';
    ASSERT_EQ('a', *((char *) node_value(n)));

    free(n);
}

/*
 * node creation by value test
 */
TEST(node, value_creation) {
    char original_value = 'v';
    node *n = node_new(&original_value,sizeof(char));

    ASSERT_EQ('v', *((char *) node_value(n)));
    ASSERT_EQ(sizeof(char), node_size(n));
    ASSERT_EQ(NULL, node_next(n));
    ASSERT_EQ(NULL, node_prev(n));

    original_value = 'a';
    ASSERT_EQ('v', *((char *) node_value(n)));

    free(node_value(n));
    free(n);
}

/*
 * node pointers get and set test
 */
TEST(node, p_get_and_set) {
    char v1 = 'a';
    node *n1 = node_new(&v1, -1);

    char v2 = 'b';
    node *n2 = node_new(&v2, -1);

    node_set_next(n1, n2);
    node_set_prev(n2, n1);

    ASSERT_EQ('b', *((char*)node_value(node_next(n1))));
    ASSERT_EQ('a', *((char*)node_value(node_prev(n2))));

    free(n1);
    free(n2);
}
