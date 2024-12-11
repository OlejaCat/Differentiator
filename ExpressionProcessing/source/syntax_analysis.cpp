#include "syntax_analysis.h"

#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <errno.h>

#include "lexical_analysis.h"


// static --------------------------------------------------------------------------------------------------------------


static int parseNumber(ArithmeticTree* arithmetic_tree, Token* token_array, int* ip);
static int parseExpression(ArithmeticTree* arithmetic_tree, Token* token_array, int* ip);
static int parseTerm(ArithmeticTree* arithmetic_tree, Token* token_array, int* ip);
static int parsePower(ArithmeticTree* arithmetic_tree, Token* token_array, int* ip);
static int parseParen(ArithmeticTree* arithmetic_tree, Token* token_array, int* ip);


// public --------------------------------------------------------------------------------------------------------------


int parseString(ArithmeticTree* arithmetic_tree, const char* input_string)
{
    assert(arithmetic_tree != NULL);
    assert(input_string    != NULL);

    int token_count = 0;
    Token* token_array = getTokens(input_string, &token_count);

    int ip = 0;
    int node = parseExpression(arithmetic_tree, token_array, &ip);

    printTokens(token_array, token_count);
    fprintf(stderr, "How we get hear...\n");

    if (token_array[ip].type != TokenType_END)
    {
        free(token_array);
        fprintf(stderr, "Syntax error on last step...\n");
        exit(1);
    }

    free(token_array);

    return node;
}


// static --------------------------------------------------------------------------------------------------------------


static int parseNumber(ArithmeticTree* arithmetic_tree, Token* token_array, int* ip)
{
    assert(arithmetic_tree != NULL);
    assert(token_array     != NULL);
    assert(ip              != NULL);

    if (token_array[*ip].type == TokenType_IDENTIFIER)
    {
        if (!strcmp(token_array[*ip].value, "x"))
        {
            (*ip)++;
            return VARIABLE("x");
        }
        else
        {
            fprintf(stderr, "Variable: '%s'\n", token_array[*ip].value);
            fprintf(stderr, "Syntax error unknown variable\n");
            exit(1);
        }
    }
    else
    {
        char* end = 0;
        double number = strtod(token_array[*ip].value, &end);
        if (errno == ERANGE || token_array[*ip].value == end)
        {
            fprintf(stderr, "Syntax error reading double...\n");
            exit(1);
        }
        (*ip)++;
        return NUMBER(number);
    }
}


static int parseExpression(ArithmeticTree* arithmetic_tree, Token* token_array, int* ip)
{
    assert(arithmetic_tree != NULL);
    assert(token_array     != NULL);
    assert(ip              != NULL);

    int left_node = parseTerm(arithmetic_tree, token_array, ip);
    while (token_array[*ip].type == TokenType_FUNCTION
       && (token_array[*ip].function.type == ArithmeticFunctions_ADD
        || token_array[*ip].function.type == ArithmeticFunctions_SUB))
    {
        Token token = token_array[*ip];
        (*ip)++;

        int rigth_node = parseTerm(arithmetic_tree, token_array, ip);

        if (token.function.type == ArithmeticFunctions_ADD)
        {
            left_node = ADD(left_node, rigth_node);
        }
        else
        {
            left_node = SUB(left_node, rigth_node);
        }
    }

    return left_node;
}


static int parseTerm(ArithmeticTree* arithmetic_tree, Token* token_array, int* ip)
{
    assert(arithmetic_tree != NULL);
    assert(token_array     != NULL);
    assert(ip              != NULL);

    int left_node = parsePower(arithmetic_tree, token_array, ip);
    while (token_array[*ip].type == TokenType_FUNCTION
       && (token_array[*ip].function.type == ArithmeticFunctions_MUL
        || token_array[*ip].function.type == ArithmeticFunctions_DIV))
    {
        Token token = token_array[*ip];
        (*ip)++;

        int rigth_node = parsePower(arithmetic_tree, token_array, ip);

        if (token.function.type == ArithmeticFunctions_MUL)
        {
            left_node = MUL(left_node, rigth_node);
        }
        else
        {
            left_node = DIV(left_node, rigth_node);
        }
    }

    return left_node;
}


static int parsePower(ArithmeticTree* arithmetic_tree, Token* token_array, int* ip)
{
    assert(arithmetic_tree != NULL);
    assert(token_array     != NULL);
    assert(ip              != NULL);

    int left_node = parseParen(arithmetic_tree, token_array, ip);
    while (token_array[*ip].type == TokenType_FUNCTION
        && 
        token_array[*ip].function.type == ArithmeticFunctions_POW)
    {
        (*ip)++;

        int rigth_node = parseParen(arithmetic_tree, token_array, ip);
        left_node = POW(left_node, rigth_node);
    }

    return left_node;
}


static int parseParen(ArithmeticTree* arithmetic_tree, Token* token_array, int* ip)
{
    assert(arithmetic_tree != NULL);
    assert(token_array     != NULL);
    assert(ip              != NULL);

    if (token_array[*ip].type == TokenType_LPAREN)
    {
        (*ip)++;
        int node = parseExpression(arithmetic_tree, token_array, ip);

        if (token_array[*ip].type != TokenType_RPAREN)
        {
            fprintf(stderr, "Syntax error... brackets\n");
            exit(1);
        }
        return node;
    }
    else
    {
        return parseNumber(arithmetic_tree, token_array, ip);
    }
}



// int GetP()
// {
//     if (s[p] == '(')
//     {
//         p++;
//         int val = GetE();
//         if (s[p] != ')')
//         {
//             printf("Ошибка!");
//             exit(0);
//         }
//         p++;
//         return val;
//     }
//     else
//     {
//         return GetN();
//     }
// }
//
//
// const char* s = "5+10*((6+10)/2)$";
// int         p = 0;
//
// int GetN();
// int GetG();
// int GetE();
// int GetT();
// int GetP();
//
// int GetG()
// {
//     int val = GetE();
//     if (s[p] != '$')
//     {
//         printf("Ошибка!");
//         exit(0);
//     }
//     p++;
//     return val;
// }
//
//
// int GetE()
// {
//     int val = GetT();
//     while (s[p] == '+' || s[p] == '-')
//     {
//         int op = s[p];
//         p++;
//         int val2 = GetT();
//         if (op == '+')
//         {
//             val += val2;
//         }
//
//         if (op == '-')
//         {
//             val -= val2;
//         }
//     }
//     return val;
// }
//
//
// int GetT()
// {
//     int val = GetP();
//     while (s[p] == '*' || s[p] == '/')
//     {
//         int op = s[p];
//         p++;
//         int val2 = GetP();
//         if (op == '*')
//         {
//             val *= val2;
//         }
//
//         if (op == '/')
//         {
//             val /= val2;
//         }
//     }
//     return val;
// }
//
//
//
//
// int GetN()
// {
//     int val = 0;
//     int old_p = p;
//     while ('0' <= s[p] && s[p] <= '9')
//     {
//         val = val * 10 + (s[p] - '0');
//         p++;
//     }
//     if (old_p != p)
//     {
//         return val;
//     }
//     else
//     {
//         printf("Ошибка!");
//         exit(0);
//     }
// }
