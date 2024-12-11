#ifndef ARITHMETIC_OPERATIONS_H
#define ARITHMETIC_OPERATIONS_H

#include <stdlib.h>

const size_t TEXT_OF_FUNCTION_SIZE = 8;

typedef enum ArithmeticFunctions
{
    ArithmeticFunctions_END  = -1,
    ArithmeticFunctions_ADD  =  0,
    ArithmeticFunctions_SUB  =  1,
    ArithmeticFunctions_MUL  =  2,
    ArithmeticFunctions_DIV  =  3,
    ArithmeticFunctions_SIN  =  4,
    ArithmeticFunctions_COS  =  5,
    ArithmeticFunctions_TG   =  6,
    ArithmeticFunctions_CTG  =  7,
    ArithmeticFunctions_POW  =  8,
    ArithmeticFunctions_LN   =  9,
    ArithmeticFunctions_SQRT =  10,
} ArithmeticFunctions;

typedef struct ArithmeticFunction
{
    ArithmeticFunctions type;
    char                text[TEXT_OF_FUNCTION_SIZE];
} ArithmeticFunction;

const ArithmeticFunction EMPTY_FUNCTION = {
    .type = ArithmeticFunctions_END,
    .text = "",
};

const ArithmeticFunction ARITHMETIC_FUNCTIONS_ARRAY[] = {
    {
        .type = ArithmeticFunctions_ADD,
        .text = "+",
    },
    {
        .type = ArithmeticFunctions_SUB,
        .text = "-",
    },
    {
        .type = ArithmeticFunctions_MUL,
        .text = "*",
    },
    {
        .type = ArithmeticFunctions_DIV,
        .text = "/",
    },
    {
        .type = ArithmeticFunctions_SIN,
        .text = "sin",
    },
    {
        .type = ArithmeticFunctions_COS,
        .text = "cos",
    },
    {
        .type = ArithmeticFunctions_TG,
        .text = "tg",
    },
    {
        .type = ArithmeticFunctions_CTG,
        .text = "ctg",
    },
    {
        .type = ArithmeticFunctions_POW,
        .text = "^",
    },
    {
        .type = ArithmeticFunctions_LN,
        .text = "ln",
    },
    {
        .type = ArithmeticFunctions_SQRT,
        .text = "sqrt",
    },
};

const int FUNCTIONS_QUANTITY = sizeof(ARITHMETIC_FUNCTIONS_ARRAY) / sizeof(ArithmeticFunction);

#define ADD(left_node__, right_node__) \
        arithmeticTreeCreateNewNode(arithmetic_tree, \
                                    { \
                                         .node_type = ArithmeticTreeNodeType_FUNCTION, \
                                         .function  = { \
                                                        .type = ArithmeticFunctions_ADD, \
                                                        .text = "+", \
                                                      } \
                                    }, left_node__, right_node__)

#define SUB(left_node__, right_node__) \
        arithmeticTreeCreateNewNode(arithmetic_tree, \
                                    { \
                                         .node_type = ArithmeticTreeNodeType_FUNCTION, \
                                         .function  = { \
                                                        .type = ArithmeticFunctions_SUB, \
                                                        .text = "-", \
                                                      } \
                                    }, left_node__, right_node__)

#define MUL(left_node__, right_node__) \
        arithmeticTreeCreateNewNode(arithmetic_tree, \
                                    { \
                                         .node_type = ArithmeticTreeNodeType_FUNCTION, \
                                         .function  = { \
                                                        .type = ArithmeticFunctions_MUL, \
                                                        .text = "*", \
                                                      } \
                                    }, left_node__, right_node__)

#define DIV(left_node__, right_node__) \
        arithmeticTreeCreateNewNode(arithmetic_tree, \
                                    { \
                                         .node_type = ArithmeticTreeNodeType_FUNCTION, \
                                         .function  = { \
                                                        .type = ArithmeticFunctions_DIV, \
                                                        .text = "/", \
                                                      } \
                                    }, left_node__, right_node__)

#define POW(left_node__, right_node__) \
        arithmeticTreeCreateNewNode(arithmetic_tree, \
                                    { \
                                         .node_type = ArithmeticTreeNodeType_FUNCTION, \
                                         .function  = { \
                                                        .type = ArithmeticFunctions_POW, \
                                                        .text = "^", \
                                                      } \
                                    }, left_node__, right_node__)

#endif // ARITHMETIC_OPEERATIONS_H
