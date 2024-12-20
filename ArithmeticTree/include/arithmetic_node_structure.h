#ifndef ARITHMETIC_NODE_STRUCTURE_H
#define ARITHMETIC_NODE_STRUCTURE_H

#include "arithmetic_operations.h"

typedef enum ArithmeticTreeNodeType
{
    ArithmeticTreeNodeType_FUNCTION = 0,
    ArithmeticTreeNodeType_VARIABLE = 1,
    ArithmeticTreeNodeType_NUMBER   = 2,
} ArithmeticTreeNodeType;

typedef struct AriphmeticNodeData
{
    ArithmeticTreeNodeType node_type;
    union
    {
        ArithmeticFunction function;
        double             numerical_data;
        char               variable_text[TEXT_OF_FUNCTION_SIZE];
    };
} AriphmeticNode;

#define VARIABLE(tree__, text__) arithmeticTreeCreateNewNode(tree__, \
                                                             { \
                                                                .node_type = ArithmeticTreeNodeType_VARIABLE, \
                                                                .variable_text = text__ \
                                                             }, \
                                                             EMPTY_NODE, \
                                                             EMPTY_NODE)

#define NUMBER(tree__, number__) arithmeticTreeCreateNewNode(tree__, \
                                                             { \
                                                                .node_type      = ArithmeticTreeNodeType_NUMBER, \
                                                                .numerical_data = number__ \
                                                             }, \
                                                             EMPTY_NODE, \
                                                             EMPTY_NODE)

#endif // ARITHMETIC_NODE_STRUCTURE_H
