#include "differentiation_logic.h"

#include <stdio.h>

#include "arithmetic_logic.h"


#define LEFT_NODE_ treeGetLeftNode(expression_tree, original_node_index)
#define RIGHT_NODE_ treeGetRightNode(expression_tree, original_node_index)

#define DIFFERENTIATE_LEFT_NODE_ \
        recursiveDifferentiate(arithmetic_tree, LEFT_NODE_)

#define DIFFERENTIATE_RIGHT_NODE_ \
        recursiveDifferentiate(arithmetic_tree, RIGHT_NODE_)

#define COPY_BRANCH_(node__) \
        arithmeticTreeRecursiveCopyBranch(differentiated_tree, expression_tree, node__)


int recursiveDifferentiate(ArithmeticTree* arithmetic_tree,
                           int             original_node_index)
{
    Tree* expression_tree     = arithmetic_tree->expression_tree;
    Tree* differentiated_tree = arithmetic_tree->differentiated_tree;
    tree_node_type data       = treeGetNodeData(expression_tree, original_node_index);

    if (data.node_type == ArithmeticTreeNodeType_NUMBER)
    {
        return NUMBER(differentiated_tree, 0);
    }
    else if (data.node_type == ArithmeticTreeNodeType_VARIABLE)
    {
        return NUMBER(differentiated_tree, 1);
    }
    else if (data.node_type == ArithmeticTreeNodeType_FUNCTION)
    {
        switch(data.function.type)
        {
            case ArithmeticFunctions_ADD:
                return ADD(differentiated_tree,
                           DIFFERENTIATE_LEFT_NODE_,
                           DIFFERENTIATE_RIGHT_NODE_);

            case ArithmeticFunctions_SUB:
                return SUB(differentiated_tree,
                           DIFFERENTIATE_LEFT_NODE_,
                           DIFFERENTIATE_RIGHT_NODE_);

            case ArithmeticFunctions_MUL:
                return ADD(differentiated_tree,
                           MUL(differentiated_tree,
                               DIFFERENTIATE_LEFT_NODE_,
                               COPY_BRANCH_(RIGHT_NODE_)),
                           MUL(differentiated_tree,
                               COPY_BRANCH_(LEFT_NODE_),
                               DIFFERENTIATE_RIGHT_NODE_));

            case ArithmeticFunctions_DIV:
                return DIV(differentiated_tree,
                           SUB(differentiated_tree,
                               MUL(differentiated_tree,
                                   DIFFERENTIATE_LEFT_NODE_,
                                   COPY_BRANCH_(RIGHT_NODE_)),
                               MUL(differentiated_tree,
                                   COPY_BRANCH_(LEFT_NODE_),
                                   DIFFERENTIATE_RIGHT_NODE_)),
                           POW(differentiated_tree,
                               COPY_BRANCH_(RIGHT_NODE_),
                               NUMBER(differentiated_tree, 2)));

            default:
                fprintf(stderr, "No instructions for differentiations...");
                exit(1);
        }
    }
    else
    {
        fprintf(stderr, "Unknown node type...");
        exit(1);
    }
}


#undef DIFFERENTIATE_LEFT_NODE_
#undef DIFFERENTIATE_RIGHT_NODE_
#undef LEFT_NODE_
#undef RIGHT_NODE_
