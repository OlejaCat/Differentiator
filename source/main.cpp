#include <stdio.h>

#include "syntax_analysis.h"
#include "differentiation_logic.h"
#include "tree_dump.h"

static const size_t SIZE_OF_EXPRESSION = 128;

int main()
{
    // printf("%d\n", GetG());

    ArithmeticTree arm_tree = {};
    arithmeticTreeCtor(&arm_tree);

    printf("Enter your expression: ");

    char input_string[SIZE_OF_EXPRESSION] = {};
    scanf("%127[^\n]", input_string);

    int node = parseString(&arm_tree, input_string);

    FILE* start_file = fopen("start.tex", "w");
    arithmeticTreeWriteInLatex(start_file, arm_tree.expression_tree, node);
    treePrintDataFromArray(arm_tree.expression_tree);

    printf("\n\n");

    FILE* end_file = fopen("end.tex", "w");
    node = recursiveDifferentiate(end_file, &arm_tree, node);
    arithmeticTreeWriteInLatex(end_file, arm_tree.differentiated_tree, node);

    treePrintDataFromArray(arm_tree.differentiated_tree);


    arithmeticTreeDtor(&arm_tree);

    fclose(start_file);
    fclose(end_file);

    return 0;
}
