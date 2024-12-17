#include "arithmetic_logic.h"

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>


// static --------------------------------------------------------------------------------------------------------------


static ArithmeticTreeErrors recursivlyWriteNodeInformationToFile(FILE* file, Tree* arithmetic_tree, int node);


// public --------------------------------------------------------------------------------------------------------------


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


ArithmeticTreeErrors arithmeticTreeWriteInLatex(FILE* file, Tree* arithmetic_tree, int start_node_index)
{
    assert(arithmetic_tree != NULL);
    assert(file            != NULL);

    if (file == NULL)
    {
        return ArithmeticTreeErrors_ERROR;
    }

    fprintf(file, "\\documentclass{article}\n\\begin{document}\n\\begin{equation}\n");

    recursivlyWriteNodeInformationToFile(file, arithmetic_tree, start_node_index);
    fprintf(file, "\n");

    fprintf(file, "\\end{equation}\n\\end{document}");

    return ArithmeticTreeErrors_OK;
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


// static --------------------------------------------------------------------------------------------------------------


static ArithmeticTreeErrors recursivlyWriteNodeInformationToFile(FILE* file, Tree* arithmetic_tree, int node)
{
    assert(file            != NULL);
    assert(arithmetic_tree != NULL);

    if (node == EMPTY_NODE)
    {
        return ArithmeticTreeErrors_OK;
    }

    AriphmeticNodeData node_data = treeGetNodeData(arithmetic_tree, node);
    int left_node_index = treeGetLeftNode(arithmetic_tree, node);
    int right_node_index = treeGetRightNode(arithmetic_tree, node);

    if (node_data.node_type == ArithmeticTreeNodeType_FUNCTION)
    {
        if (node_data.function.type == ArithmeticFunctions_DIV)
        {
            fprintf(file, " \\frac{");
            recursivlyWriteNodeInformationToFile(file, arithmetic_tree, left_node_index);
            fprintf(file, "}{");
            recursivlyWriteNodeInformationToFile(file, arithmetic_tree, right_node_index);
            fprintf(file, "}");
        }
        else if (node_data.function.type == ArithmeticFunctions_TG
              || node_data.function.type == ArithmeticFunctions_CTG
              || node_data.function.type == ArithmeticFunctions_COS
              || node_data.function.type == ArithmeticFunctions_SIN
              || node_data.function.type == ArithmeticFunctions_LN
              || node_data.function.type == ArithmeticFunctions_EXP
              || node_data.function.type == ArithmeticFunctions_SQRT)
        {
            fprintf(file, "%s{(", node_data.function.text);
            recursivlyWriteNodeInformationToFile(file, arithmetic_tree, left_node_index);
            fprintf(file, ")}");
        }
        else
        {
            fprintf(file, "{(");
            recursivlyWriteNodeInformationToFile(file, arithmetic_tree, left_node_index);
            if (node_data.function.type == ArithmeticFunctions_MUL)
            {
                fprintf(file, ")}\\cdot{(");
            }
            else
            {
                fprintf(file, ")}%s{(", node_data.function.text);
            }
            recursivlyWriteNodeInformationToFile(file, arithmetic_tree, right_node_index);
            fprintf(file, ")}");
        }
    }

    if (node_data.node_type == ArithmeticTreeNodeType_NUMBER)
    {
        double number = node_data.numerical_data;

        if (number >= 0)
        {
            fprintf(file, "%lg", number);
        }
        else
        {
            fprintf(file, "(%lg)", number);
        }
    }

    if (node_data.node_type == ArithmeticTreeNodeType_VARIABLE)
    {
        fprintf(file, "x");
    }

    return ArithmeticTreeErrors_OK;
}
