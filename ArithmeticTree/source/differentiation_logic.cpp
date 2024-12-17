#include "differentiation_logic.h"

#include <stdio.h>
#include <assert.h>

#include "arithmetic_logic.h"


#define LEFT_NODE_ treeGetLeftNode(expression_tree, original_node_index)
#define RIGHT_NODE_ treeGetRightNode(expression_tree, original_node_index)

#define DIFFERENTIATE_LEFT_NODE_ \
        recursiveDifferentiate(file, arithmetic_tree, LEFT_NODE_)

#define DIFFERENTIATE_RIGHT_NODE_ \
        recursiveDifferentiate(file, arithmetic_tree, RIGHT_NODE_)

#define COPY_BRANCH_(node__) \
        arithmeticTreeRecursiveCopyBranch(differentiated_tree, expression_tree, node__)


int recursiveDifferentiate(FILE*           file,
                           ArithmeticTree* arithmetic_tree,
                           int             original_node_index)
{
    assert(file            != NULL);
    assert(arithmetic_tree != NULL);

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

            case ArithmeticFunctions_POW: {
                AriphmeticNodeData node = treeGetNodeData(expression_tree, RIGHT_NODE_);
                if (node.node_type == ArithmeticTreeNodeType_NUMBER)
                {
                    return MUL(differentiated_tree,
                               NUMBER(differentiated_tree,
                                      node.numerical_data),
                               MUL(differentiated_tree,
                                   POW(differentiated_tree,
                                        COPY_BRANCH_(LEFT_NODE_),
                                        NUMBER(differentiated_tree,
                                               node.numerical_data - 1)),
                                   DIFFERENTIATE_LEFT_NODE_));
                }
                printf("No instructions for differentiations...\n");
                return EMPTY_NODE;
            }

            case ArithmeticFunctions_SIN:
                return MUL(differentiated_tree,
                           COS(differentiated_tree,
                               COPY_BRANCH_(LEFT_NODE_)),
                           DIFFERENTIATE_LEFT_NODE_);

            case ArithmeticFunctions_COS:
                return MUL(differentiated_tree,
                           MUL(differentiated_tree,
                               NUMBER(differentiated_tree, -1),
                               SIN(differentiated_tree,
                                   COPY_BRANCH_(LEFT_NODE_))),
                           DIFFERENTIATE_LEFT_NODE_);

            case ArithmeticFunctions_TG:
                return MUL(differentiated_tree,
                           DIV(differentiated_tree,
                               NUMBER(differentiated_tree, 1),
                               POW(differentiated_tree,
                                   COS(differentiated_tree,
                                       COPY_BRANCH_(LEFT_NODE_)),
                                       NUMBER(differentiated_tree, 2))),
                           DIFFERENTIATE_LEFT_NODE_);

            case ArithmeticFunctions_CTG:
                return MUL(differentiated_tree,
                           DIV(differentiated_tree,
                               NUMBER(differentiated_tree, 1),
                               MUL(differentiated_tree,
                                   NUMBER(differentiated_tree, -1),
                                   POW(differentiated_tree,
                                       SIN(differentiated_tree,
                                           COPY_BRANCH_(LEFT_NODE_)),
                                           NUMBER(differentiated_tree, 2)))),
                           DIFFERENTIATE_LEFT_NODE_);

            case ArithmeticFunctions_EXP:
                return MUL(differentiated_tree,
                           EXP(differentiated_tree,
                               COPY_BRANCH_(LEFT_NODE_)),
                           DIFFERENTIATE_LEFT_NODE_);

            case ArithmeticFunctions_LN:
                return MUL(differentiated_tree,
                           DIV(differentiated_tree,
                               NUMBER(differentiated_tree, 1),
                               COPY_BRANCH_(LEFT_NODE_)),
                           DIFFERENTIATE_LEFT_NODE_);

            default:
                fprintf(stderr, "No instructions for differentiations...\n");
                exit(1);
        }
    }
    else
    {
        fprintf(stderr, "Unknown node type...\n");
        exit(1);
    }
}


#undef DIFFERENTIATE_LEFT_NODE_
#undef DIFFERENTIATE_RIGHT_NODE_
#undef LEFT_NODE_
#undef RIGHT_NODE_
#undef COPY_BRANCH_
