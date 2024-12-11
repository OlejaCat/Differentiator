#ifndef LEXICAL_ANALYSIS_H
#define LEXICAL_ANALYSIS_H

#include <stdlib.h>

#include "arithmetic_operations.h"

const int MAX_TOKEN_SIZE = 64;

typedef enum TokenType
{
    TokenType_END        = -1,
    TokenType_NUMBER     =  0,
    TokenType_FUNCTION   =  1,
    TokenType_IDENTIFIER =  2,
    TokenType_LPAREN     =  3,
    TokenType_RPAREN     =  4,
    TokenType_UNKNOWN    =  5,
} TokenType;

typedef struct Token
{
    TokenType type;
    union
    {
        ArithmeticFunction function;
        char               value[MAX_TOKEN_SIZE];
    };
} Token;


const Token END_TOKEN = {.type = TokenType_END};

Token* getTokens(const char* input_string, int* token_count);
void printTokens(Token* token_array, int token_count);

#endif // LEXICAL_ANALYSIS_H
