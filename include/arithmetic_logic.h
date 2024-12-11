#ifndef ARITHMETIC_LOGIC_H
#define ARITHMETIC_LOGIC_H

#include "arithmetic_errors.h"
#include "arithmetic_tree_structure.h"
#include "tree.h"

typedef struct ArithmeticTree
{
    Tree* tree;
} ArithmeticTree;

ArithmeticTreeErrors arithmeticTreeCtor(ArithmeticTree* arithmetic_tree);
int arithmeticTreeCreateNewNode(ArithmeticTree*    arithmetic_tree,
                                AriphmeticNodeData node_data,
                                int                left_node,
                                int                right_node);
ArithmeticTreeErrors arithmeticTreeDtor(ArithmeticTree* arithmetic_tree);

#endif // ARITHMETIC_LOGIC_H
