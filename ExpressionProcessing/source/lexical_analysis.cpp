#include "lexical_analysis.h"

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>


// static --------------------------------------------------------------------------------------------------------------


// static void buildKMPTable(const char* pattern, int* lps, size_t pattern_length); // NOTE алгоритм КМP для поиска
                                                                                    //      подстроки в строке
// static int isKnowmFunctionKMP(const char* input_string); - оставим до лучших времен...
static ArithmeticFunction isKnownFunction(const char* input_string);
static int isOperator(const char c);

static const size_t TOKENS_QUANTITY = 128;


// public --------------------------------------------------------------------------------------------------------------


Token* getTokens(const char* input_string, int* token_count)
{
    assert(input_string != NULL);
    assert(token_count  != NULL);

    const char* current_char = input_string;
    Token* token_array       = (Token*)calloc(TOKENS_QUANTITY, sizeof(Token));
    *token_count = 0;

    while (*current_char != '\0')
    {
        if (isspace(*current_char))
        {
            current_char++;
            continue;
        }

        Token current_token = {
            .type  = TokenType_UNKNOWN,
            .value  = "",
        };
        if (isdigit(*current_char)
         || *current_char == '.'
         || *current_char == ',')
        {
            int token_length = 0;
            while (isdigit(*current_char)
                || *current_char == '.'
                || *current_char == ',')
            {
                if (token_length < MAX_TOKEN_SIZE - 1) {
                    current_token.value[token_length++] = *current_char;
                }
                current_char++;
            }
            current_token.value[token_length] = '\0';
            current_token.type = TokenType_NUMBER;
        }
        else if (isalpha(*current_char) || isOperator(*current_char))
        {
            int token_length = 0;
            if (isOperator(*current_char))
            {
                current_token.value[token_length++] = *current_char;
                current_char++;
            }
            else
            {
                while (isalpha(*current_char))
                {
                    if (token_length < MAX_TOKEN_SIZE - 1)
                    {
                        current_token.value[token_length++] = *current_char;
                    }
                    current_char++;
                }
            }
            current_token.value[token_length] = '\0';

            ArithmeticFunction processed_operation = isKnownFunction(current_token.value);
            if (processed_operation.type != ArithmeticFunctions_END)
            {
                current_token.type = TokenType_FUNCTION;
                current_token.function = processed_operation;
            }
            else
            {
                current_token.type = TokenType_IDENTIFIER;
            }
        }
        else if (*current_char == '(')
        {
            current_token.type = TokenType_LPAREN;
            current_token.value[0] = '(';
            current_token.value[1] = '\0';
            current_char++;
        }
        else if (*current_char == ')')
        {
            current_token.type = TokenType_RPAREN;
            current_token.value[0] = ')';
            current_token.value[1] = '\0';
            current_char++;
        }
        else
        {
            fprintf(stderr, "Error during lexical analysis...\n");
            exit(1);
        }

        token_array[(*token_count)++] = current_token;
    }

    token_array = (Token*)realloc(token_array, ((size_t)(*token_count + 1)) * sizeof(Token));
    token_array[*token_count] = END_TOKEN;

    return token_array;
}


void printTokens(Token* token_array, int token_count)
{
    assert(token_array != NULL);

    for (int i = 0; i < token_count; i++)
    {
        printf("Token %d: Type = ", i + 1);
        switch (token_array[i].type)
        {
            case TokenType_NUMBER:     printf("NUMBER");     break;
            case TokenType_FUNCTION:   printf("FUNCTION");   break;
            case TokenType_IDENTIFIER: printf("IDENTIFIER"); break;
            case TokenType_LPAREN:     printf("LPAREN");     break;
            case TokenType_RPAREN:     printf("RPAREN");     break;
            default: printf("UNKNOWN");
        }
        if (token_array[i].type == TokenType_FUNCTION)
        {
            printf(", Value = %s\n", token_array[i].function.text);
        }
        else
        {
            printf(", Value = %s\n", token_array[i].value);
        }
    }
}


// static --------------------------------------------------------------------------------------------------------------

// static void buildKMPTable(const char* pattern, int* lps, size_t pattern_length)
// {
//     int prefix_length = 0;
//     lps[0] = 0;
//     size_t i = 1;
//
//     while (i < pattern_length)
//     {
//         if (pattern[i] == pattern[prefix_length])
//         {
//             prefix_length++;
//             lps[i] = prefix_length;
//             i++;
//         }
//         else
//         {
//             if (prefix_length != 0)
//             {
//                 prefix_length = lps[prefix_length - 1];
//             }
//             else
//             {
//                 lps[i] = 0;
//                 i++;
//             }
//         }
//     }
// }


// static int isKnowmFunctionKMP(const char* input_string)
// {
//     for (int i = 0; i < OPERATIONS_QUANTITY; i++)
//     {
//         const char* known_function = ARITHMETIC_OPERATIONS_ARRAY[i].value;
//         size_t known_function_length = strlen(known_function);
//         size_t input_string_length = strlen(input_string);
//
//         int* lps = (int*)calloc(known_function_length, sizeof(int));
//         buildKMPTable(known_function, lps, known_function_length);
//
//         int j = 0;
//         for (int k = 0; k < (int)input_string_length; k++)
//         {
//             while (j > 0 && input_string[k] != known_function[j])
//             {
//                 j = lps[j - 1];
//             }
//
//             if (input_string[k] == known_function[j])
//             {
//                 j++;
//             }
//
//             if (j == (int)known_function_length)
//             {
//                 free(lps);
//                 return 1;
//             }
//         }
//         free(lps);
//     }
//     return 0;
// }

static ArithmeticFunction isKnownFunction(const char* input_string)
{
    assert(input_string != NULL);

    size_t input_string_length = strlen(input_string);
    for (int i = 0; i < FUNCTIONS_QUANTITY; i++)
    {
        const char* known_function = ARITHMETIC_FUNCTIONS_ARRAY[i].text;
        size_t known_function_length = strlen(known_function);

        if (input_string_length < known_function_length)
        {
            continue;
        }

        if (strncmp(input_string, known_function, known_function_length) == 0)
        {
            if (input_string[known_function_length] == '\0'
             || !isalnum(input_string[known_function_length]))
            {
                return ARITHMETIC_FUNCTIONS_ARRAY[i];
            }
        }
    }
    return EMPTY_FUNCTION;
}


static int isOperator(const char c)
{
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '^';
}
