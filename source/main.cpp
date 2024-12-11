#include <stdlib.h>
#include <stdio.h>
#include "arithmetic_tree_structure.h"


const char* s = "5+10*((6+10)/2)$";
int         p = 0;

int GetN();
int GetG();
int GetE();
int GetT();
int GetP();

int GetG()
{
    int val = GetE();
    if (s[p] != '$')
    {
        printf("Ошибка!");
        exit(0);
    }
    p++;
    return val;
}


int GetE()
{
    int val = GetT();
    while (s[p] == '+' || s[p] == '-')
    {
        int op = s[p];
        p++;
        int val2 = GetT();
        if (op == '+')
        {
            val += val2;
        }

        if (op == '-')
        {
            val -= val2;
        }
    }
    return val;
}


int GetT()
{
    int val = GetP();
    while (s[p] == '*' || s[p] == '/')
    {
        int op = s[p];
        p++;
        int val2 = GetP();
        if (op == '*')
        {
            val *= val2;
        }

        if (op == '/')
        {
            val /= val2;
        }
    }
    return val;
}


int GetP()
{
    if (s[p] == '(')
    {
        p++;
        int val = GetE();
        if (s[p] != ')')
        {
            printf("Ошибка!");
            exit(0);
        }
        p++;
        return val;
    }
    else
    {
        return GetN();
    }
}


int GetN()
{
    int val = 0;
    int old_p = p;
    while ('0' <= s[p] && s[p] <= '9')
    {
        val = val * 10 + (s[p] - '0');
        p++;
    }
    if (old_p != p)
    {
        return val;
    }
    else
    {
        printf("Ошибка!");
        exit(0);
    }
}


#include "lexical_analysis.h"
#include "syntax_analysis.h"

#include "tree_dump.h"


int main()
{
    // printf("%d\n", GetG());

    ArithmeticTree arm_tree = {};
    arithmeticTreeCtor(&arm_tree);

    const char* input_string = "x^2 * x";
    parseString(&arm_tree, input_string);

    treePrintDataFromArray(arm_tree.tree);

    arithmeticTreeDtor(&arm_tree);

    return 0;
}
