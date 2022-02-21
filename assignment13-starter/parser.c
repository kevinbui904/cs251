/*
parser.c
Written by Thien K. M. Bui
Last editted 02-20-22
*/

#include <stdio.h>
#include <string.h>

#include "value.h"
#include "parser.h"
#include "talloc.h"
#include "tokenizer.h"
#include "linkedlist.h"

// Return a pointer to a parse tree representing the structure of a Scheme
// program, given a list of tokens in the program.
Value *parse(Value *tokens)
{
    // create a temporary linked-stack on the parse() memory stack
    Value *parse_tree = makeNull();

    Value *current_node = tokens;

    int depth = 0;

    if (isNull(current_node))
    {
        printf("ParseError: null pointer\n");
    }
    else
    {
        while (current_node->type != NULL_TYPE)
        {
            Value *current_token = car(current_node);

            // start popping from the type
            if (current_token->type == CLOSE_TYPE)
            {
                if (depth == 0)
                {
                    printf("Syntax error: too many close parens\n");
                    texit(1);
                }
                Value *current_right_most = makeNull();
                // pop UNTIL an open parenthesis is detected
                // ignore the parenthesis
                while (car(parse_tree)->type != OPEN_TYPE && parse_tree->type != NULL_TYPE)
                {
                    current_right_most = cons(car(parse_tree), current_right_most);
                    parse_tree = cdr(parse_tree);
                }
                if (car(parse_tree)->type == OPEN_TYPE)
                {
                    // handle the case where there's nothing between open and close param

                    parse_tree = cons(current_right_most, cdr(parse_tree));

                    depth = depth - 1;
                }
            }
            // push onto the stack
            else if (current_token->type == OPEN_TYPE)
            {
                depth = depth + 1;
                parse_tree = cons(current_token, parse_tree);
            }
            else
            {
                parse_tree = cons(current_token, parse_tree);
            }
            current_node = cdr(current_node);
        }
    }

    // stack is the parse tree in reverse
    parse_tree = reverse(parse_tree);
    if (depth != 0)
    {
        // displayTokens(stack);
        printf("Syntax error (depth %i): missing closing parenthesis\n", depth);
        texit(1);
        return parse_tree;
    }
    else
    {
        return parse_tree;
    }
}

// Print a parse tree to the screen in a readable fashion. It should look
// just like Scheme code (use parentheses to mark subtrees).
void printTree(Value *tree)
{
    // should be CONS_TYPE
    if (tree->type != NULL_TYPE)
    {
        switch (tree->type)
        {
        case STR_TYPE:
            printf("\"%s\" ", tree->s);
            break;
        case SYMBOL_TYPE:
            printf("%s ", tree->s);
            break;
        case BOOL_TYPE:
            if (tree->i == 1)
            {
                printf("#t ");
            }
            else if (tree->i == 0)
            {
                printf("#f ");
            }
            else
            {
                printf("Syntax error (readBoolean): boolean was not #t or #f\n");
                texit(1);
            }
            break;
        case INT_TYPE:
            printf("%i ", tree->i);
            break;
        case DOUBLE_TYPE:
            printf("%f ", tree->d);
            break;
        case CONS_TYPE:
            if (car(tree)->type == CONS_TYPE)
            {
                printf("( ");
                printTree(car(tree));
                printf(") ");
                printTree(cdr(tree));
            }
            else if (car(tree)->type == NULL_TYPE)
            {
                printf("(");
                printf(") ");
                printTree(cdr(tree));
            }
            else
            {
                printTree(car(tree));
                printTree(cdr(tree));
            }

            break;
        default:
            printf("Syntax Error: read type not supported\n");
            texit(1);
        }
    }
}
