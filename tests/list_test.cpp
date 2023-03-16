#include "gtest/gtest.h"

extern "C" {
#include "list/node/node.h"
#include "list/list/list.h"

#include <malloc.h>
}

/*
 * Empty creation test
 */
TEST(list, empty_creation) {
    list *l = list_new();

    ASSERT_EQ(NULL, list_head(l));
    ASSERT_EQ(NULL, list_last(l));
    ASSERT_EQ(0, list_len(l));

    list_free(l, NULL);
}

/*
 * To free char (node -1)
 */
static void free_char_no_copy(void *v) {
    return;
}

/*
 * To free char (node 1)
 */
static void free_char(void *v) {
    free(v);
}

/*
 * Free list ptr (node -1)
 */
static void free_list_ptr(void *v) {
    free(v);
}

/*
 * append test
 */
TEST(list, append_no_copy) {
    list *l = list_new();

    char a = 'a';
    node *n1 = node_new(&a, -1);
    list_append(l, n1);

    char b = 'b';
    node *n2 = node_new(&b, -1);
    list_append(l, n2);

    ASSERT_EQ(2, list_len(l));
    ASSERT_EQ(-1, node_size(list_head(l)));
    ASSERT_EQ(-1, node_size(list_last(l)));
    ASSERT_EQ('a', *((char *)node_value(list_head(l))));
    ASSERT_EQ('b', *((char *)node_value(list_last(l))));

    list_free(l, &free_char_no_copy);
}

/*
 * append with copy test
 */
TEST(list, append_with_copy) {
    list *l = list_new();

    char a = 'a';
    node *n1 = node_new(&a, 1);
    list_append(l, n1);

    char b = 'b';
    node *n2 = node_new(&b, 1);
    list_append(l, n2);

    ASSERT_EQ(2, list_len(l));
    ASSERT_EQ(1, node_size(list_head(l)));
    ASSERT_EQ(1, node_size(list_last(l)));
    ASSERT_EQ('a', *((char *)node_value(list_head(l))));
    ASSERT_EQ('b', *((char *)node_value(list_last(l))));

    list_free(l, &free_char);
}

/*
 * Empty parts join test
 */
TEST(list, empty_join) {
    // Creating empty parts list
    list *parts = list_new();

    // Joining
    list *result = list_join(parts);

    // Asserting
    ASSERT_EQ(0, list_len(result));
    ASSERT_EQ(NULL, list_head(result));
    ASSERT_EQ(NULL, list_last(result));

    // Deallocating
    free(parts);
    free(result);
}

/*
 * join test
 */
TEST(list, join) {
    // Creating lists
    list *l1, *l2, *l3;
    l1 = list_new();
    l2 = list_new();
    l3 = list_new();

    char values[10] = { 'a', 'b', 'c', 'd', 'e', 'f',
                        'g', 'h', 'i', 'j' };

    list_append(l1, node_new(&values[0], 1));
    list_append(l1, node_new(&values[1], 1));

    list_append(l2, node_new(&values[2], 1));
    list_append(l2, node_new(&values[3], 1));
    list_append(l2, node_new(&values[4], 1));

    list_append(l3, node_new(&values[5], 1));
    list_append(l3, node_new(&values[6], 1));
    list_append(l3, node_new(&values[7], 1));
    list_append(l3, node_new(&values[8], 1));
    list_append(l3, node_new(&values[9], 1));

    // Joining
    list *parts = list_new();
    list_append(parts, node_new(l1, -1));
    list_append(parts, node_new(l2, -1));
    list_append(parts, node_new(l3, -1));
    list *result = list_join(parts);

    // Asserting
    node *current = list_head(result);
    for (int i = 0; i < list_len(result); i++) {
        ASSERT_EQ(values[i], *(char *)node_value(current));
        current = node_next(current);
    }

    // Deallocating
    list_free(result, &free_char);
    list_free(parts, &free_list_ptr);
}

/*
 * Empty parts join test
 */
TEST(list, empty_parts_join) {
    // Creating parts
    list *parts = list_new();
    for (int i = 0; i < 10; i++){
        list_append(parts, node_new(list_new(), -1));
    }

    // Joining
    list *result = list_join(parts);

    // Asserting
    ASSERT_EQ(0, list_len(result));

    // Deallocating
    list_free(result, &free_char);
    list_free(parts, &free_list_ptr);
}

/*
 * Mix join test
 */
TEST(list, join_mix) {
    // Creating list
    list *lm2, *lm1, *l0, *l1, *l2, *l3, *l4, *l5;
    lm2 = list_new(); // can't clear
    lm1 = list_new(); // can't clear
    l1 = list_new();
    l2 = list_new();
    l3 = list_new();
    l4 = list_new();
    l5 = list_new();


    char values[10] = { 'a', 'b', 'c', 'd', 'e', 'f',
                        'g', 'h', 'i', 'j' };

    list_append(l1, node_new(&values[0], 1));
    list_append(l1, node_new(&values[1], 1));

    list_append(l2, node_new(&values[2], 1));
    list_append(l2, node_new(&values[3], 1));
    list_append(l2, node_new(&values[4], 1));

    list_append(l3, node_new(&values[5], 1));
    list_append(l3, node_new(&values[6], 1));
    list_append(l3, node_new(&values[7], 1));
    list_append(l3, node_new(&values[8], 1));
    list_append(l3, node_new(&values[9], 1));

    // Joining
    list *parts = list_new();
    list_append(parts, node_new(lm2, -1));
    list_append(parts, node_new(lm1, -1));
    list_append(parts, node_new(l1, -1));
    list_append(parts, node_new(l2, -1));
    list_append(parts, node_new(l3, -1));
    list_append(parts, node_new(l4, -1));
    list_append(parts, node_new(l5, -1));
    list *result = list_join(parts);

    // Asserting
    node *current = list_head(result);
    for (int i = 0; i < list_len(result); i++) {
        ASSERT_EQ(values[i], *(char *)node_value(current));
        current = node_next(current);
    }

    // Deallocating
    list_free(result, &free_char);
    list_free(parts, &free_list_ptr);
}