#ifndef ARITHMETIC_LOGIC_H
#define ARITHMETIC_LOGIC_H

#include "arithmetic_errors.h"
#include "arithmetic_node_structure.h"
#include "tree.h"

typedef struct ArithmeticTree
{
    Tree* expression_tree;
    Tree* differentiated_tree;
} ArithmeticTree;

ArithmeticTreeErrors arithmeticTreeCtor(ArithmeticTree* arithmetic_tree);
int arithmeticTreeCreateNewNode(Tree*              arithmetic_tree,
                                AriphmeticNodeData node_data,
                                int                left_node,
                                int                right_node);
ArithmeticTreeErrors arithmeticTreeWriteInLatex(Tree* arithmetic_tree, int start_node_index, const char* file_path);
int arithmeticTreeRecursiveCopyBranch(Tree* new_tree, Tree* original_tree, int original_node_index);
ArithmeticTreeErrors arithmeticTreeDtor(ArithmeticTree* arithmetic_tree);

#endif // ARITHMETIC_LOGIC_H
