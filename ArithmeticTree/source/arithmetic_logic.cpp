#include "arithmetic_logic.h"

#include <assert.h>


ArithmeticTreeErrors arithmeticTreeCtor(ArithmeticTree* arithmetic_tree)
{
    assert(arithmetic_tree != NULL);

    arithmetic_tree->expression_tree     = treeCtor();
    arithmetic_tree->differentiated_tree = treeCtor();

    return ArithmeticTreeErrors_OK;
}


int arithmeticTreeCreateNewNode(Tree*              arithmetic_tree,
                                AriphmeticNodeData node_data,
                                int                left_node,
                                int                right_node)
{
    assert(arithmetic_tree != NULL);

    int node = treeCreateNewNode(arithmetic_tree, node_data);
    if (node == EMPTY_NODE)
    {
        return EMPTY_NODE;
    }

    if (left_node != EMPTY_NODE)
    {
        treeInsertOnLeft(arithmetic_tree, node, left_node);
    }

    if (right_node != EMPTY_NODE)
    {
        treeInsertOnRight(arithmetic_tree, node, right_node);
    }

    return node;
}


int arithmeticTreeRecursiveCopyBranch(Tree* new_tree, Tree* original_tree, int original_node_index)
{
    assert(new_tree      != NULL);
    assert(original_tree != NULL);

    if (original_node_index == EMPTY_NODE)
    {
        return EMPTY_NODE;
    }

    return arithmeticTreeCreateNewNode(new_tree,
        treeGetNodeData(original_tree, original_node_index),
        arithmeticTreeRecursiveCopyBranch(new_tree,
                                          original_tree,
                                          treeGetLeftNode(original_tree, original_node_index)),
        arithmeticTreeRecursiveCopyBranch(new_tree,
                                          original_tree,
                                          treeGetRightNode(original_tree, original_node_index)));
}


ArithmeticTreeErrors arithmeticTreeDtor(ArithmeticTree* arithmetic_tree)
{
    if (arithmetic_tree == NULL)
    {
        return ArithmeticTreeErrors_ERROR;
    }

    treeDtor(arithmetic_tree->expression_tree);
    treeDtor(arithmetic_tree->differentiated_tree);

    return ArithmeticTreeErrors_OK;
}
