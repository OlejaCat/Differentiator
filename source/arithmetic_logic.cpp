#include "arithmetic_logic.h"

#include <assert.h>


ArithmeticTreeErrors arithmeticTreeCtor(ArithmeticTree* arithmetic_tree)
{
    assert(arithmetic_tree != NULL);

    arithmetic_tree->tree = treeCtor();

    return ArithmeticTreeErrors_OK;
}


int arithmeticTreeCreateNewNode(ArithmeticTree*    arithmetic_tree,
                                AriphmeticNodeData node_data,
                                int                left_node,
                                int                right_node)
{
    assert(arithmetic_tree != NULL);

    int node = treeCreateNewNode(arithmetic_tree->tree, node_data);
    if (node == EMPTY_NODE)
    {
        return EMPTY_NODE;
    }

    if (left_node != EMPTY_NODE)
    {
        treeInsertOnLeft(arithmetic_tree->tree, node, left_node);
    }

    if (right_node != EMPTY_NODE)
    {
        treeInsertOnRight(arithmetic_tree->tree, node, right_node);
    }

    return node;
}


ArithmeticTreeErrors arithmeticTreeDtor(ArithmeticTree* arithmetic_tree)
{
    if (arithmetic_tree == NULL)
    {
        return ArithmeticTreeErrors_ERROR;
    }

    treeDtor(arithmetic_tree->tree);

    return ArithmeticTreeErrors_OK;
}
