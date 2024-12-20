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
    ArithmeticFunctions_EXP  =  11,
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
    {
        .type = ArithmeticFunctions_EXP,
        .text = "exp",
    },
};

const int FUNCTIONS_QUANTITY = sizeof(ARITHMETIC_FUNCTIONS_ARRAY) / sizeof(ArithmeticFunction);

#define ADD(tree__, left_node__, right_node__) \
        arithmeticTreeCreateNewNode(tree__, \
                                    { \
                                         .node_type = ArithmeticTreeNodeType_FUNCTION, \
                                         .function  = { \
                                                        .type = ArithmeticFunctions_ADD, \
                                                        .text = "+", \
                                                      } \
                                    }, left_node__, right_node__)

#define SUB(tree__, left_node__, right_node__) \
        arithmeticTreeCreateNewNode(tree__, \
                                    { \
                                         .node_type = ArithmeticTreeNodeType_FUNCTION, \
                                         .function  = { \
                                                        .type = ArithmeticFunctions_SUB, \
                                                        .text = "-", \
                                                      } \
                                    }, left_node__, right_node__)

#define MUL(tree__, left_node__, right_node__) \
        arithmeticTreeCreateNewNode(tree__, \
                                    { \
                                         .node_type = ArithmeticTreeNodeType_FUNCTION, \
                                         .function  = { \
                                                        .type = ArithmeticFunctions_MUL, \
                                                        .text = "*", \
                                                      } \
                                    }, left_node__, right_node__)

#define DIV(tree__, left_node__, right_node__) \
        arithmeticTreeCreateNewNode(tree__, \
                                    { \
                                         .node_type = ArithmeticTreeNodeType_FUNCTION, \
                                         .function  = { \
                                                        .type = ArithmeticFunctions_DIV, \
                                                        .text = "/", \
                                                      } \
                                    }, left_node__, right_node__)

#define POW(tree__, left_node__, right_node__) \
        arithmeticTreeCreateNewNode(tree__, \
                                    { \
                                         .node_type = ArithmeticTreeNodeType_FUNCTION, \
                                         .function  = { \
                                                        .type = ArithmeticFunctions_POW, \
                                                        .text = "^", \
                                                      } \
                                    }, left_node__, right_node__)

#define COS(tree__, left_node__) \
        arithmeticTreeCreateNewNode(tree__, \
                                    { \
                                         .node_type = ArithmeticTreeNodeType_FUNCTION, \
                                         .function  = { \
                                                        .type = ArithmeticFunctions_COS, \
                                                        .text = "cos", \
                                                      } \
                                    }, left_node__, EMPTY_NODE)

#define SIN(tree__, left_node__) \
        arithmeticTreeCreateNewNode(tree__, \
                                    { \
                                         .node_type = ArithmeticTreeNodeType_FUNCTION, \
                                         .function  = { \
                                                        .type = ArithmeticFunctions_SIN, \
                                                        .text = "sin", \
                                                      } \
                                    }, left_node__, EMPTY_NODE)

#define LN(tree__, left_node__) \
        arithmeticTreeCreateNewNode(tree__, \
                                    { \
                                         .node_type = ArithmeticTreeNodeType_FUNCTION, \
                                         .function  = { \
                                                        .type = ArithmeticFunctions_LN, \
                                                        .text = "ln", \
                                                      } \
                                    }, left_node__, EMPTY_NODE)

#define TG(tree__, left_node__) \
        arithmeticTreeCreateNewNode(tree__, \
                                    { \
                                         .node_type = ArithmeticTreeNodeType_FUNCTION, \
                                         .function  = { \
                                                        .type = ArithmeticFunctions_TG, \
                                                        .text = "tg", \
                                                      } \
                                    }, left_node__, EMPTY_NODE)

#define CTG(tree__, left_node__) \
        arithmeticTreeCreateNewNode(tree__, \
                                    { \
                                         .node_type = ArithmeticTreeNodeType_FUNCTION, \
                                         .function  = { \
                                                        .type = ArithmeticFunctions_CTG, \
                                                        .text = "ctg", \
                                                      } \
                                    }, left_node__, EMPTY_NODE)

#define SQRT(tree__, left_node__) \
        arithmeticTreeCreateNewNode(tree__, \
                                    { \
                                         .node_type = ArithmeticTreeNodeType_FUNCTION, \
                                         .function  = { \
                                                        .type = ArithmeticFunctions_SQRT, \
                                                        .text = "sqrt", \
                                                      } \
                                    }, left_node__, EMPTY_NODE)

#define EXP(tree__, left_node__) \
        arithmeticTreeCreateNewNode(tree__, \
                                    { \
                                         .node_type = ArithmeticTreeNodeType_FUNCTION, \
                                         .function  = { \
                                                        .type = ArithmeticFunctions_EXP, \
                                                        .text = "exp", \
                                                      } \
                                    }, left_node__, EMPTY_NODE)


#endif // ARITHMETIC_OPEERATIONS_H
