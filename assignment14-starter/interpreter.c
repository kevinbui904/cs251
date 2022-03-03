/**
 * @file interpreter.c
 * @author Thien K. M. Bui and Victor Huang
 * @brief
 * @version 0.1
 * @date 2022-03-02
 *
 * @copyright Copyright (c) 2022 Thien K. M. Bui <buik@carleton.edu>
 *
 */

#include <string.h>
#include <stdio.h>

#include "value.h"
#include "linkedlist.h"
#include "talloc.h"
#include "eval_let.h"
#include "eval_if.h"
#include "look_up_symbol.h"

Value *eval(Value *expr, Frame *frame)
{
    switch (expr->type)
    {
    case SYMBOL_TYPE:
    {
        return look_up_symbol(expr, frame);

        break;
    }
    // should happens when there is a new sub-level (set of parenthesis)
    case CONS_TYPE:
    {
        Value *first = car(expr);
        Value *args = cdr(expr);
        // if first is "if"
        if (strcmp(first->s, "if") == 0)
        {
            return eval_if(args, frame);
        }
        // strcmp returns 0 if the 2 strings matches
        else if (strcmp(first->s, "let") == 0)
        {
            return eval_let(args, frame);
        }
        // Other special forms go here...
        else
        {
            printf("first: %s\n", car(first)->s);
            printf("Syntax Error: symbol not recognized\n");
            texit(1);
        }
        return makeNull();
        break;
    }
    // atomic values
    default:
    {
        return expr;
    }
    }
}

/*
interpret()
call eval() on EVERY top-level node
*/
void interpret(Value *tree)
{
    while (!isNull(tree))
    {
        // make empty Frame
        Frame empty_frame;
        empty_frame.bindings = makeNull();
        empty_frame.parent = NULL;

        Value *eval_result = eval(car(tree), &empty_frame);
        // print out result
        switch (eval_result->type)
        {
        case INT_TYPE:
            printf("%i\n", eval_result->i);
            break;
        case DOUBLE_TYPE:
            printf("%f\n", eval_result->d);

            break;
        case STR_TYPE:
            printf("\"%s\"\n", eval_result->s);

            break;
        case NULL_TYPE:
            printf("()\n");

            break;
        case PTR_TYPE:
            printf("%p\n", eval_result->p);

            break;
        case BOOL_TYPE:
            if (eval_result->i == 0)
            {
                printf("#f\n");
            }
            else
            {
                printf("#t\n");
            }
            break;
        default:
            printf("Interpreter error: print type [%i] not supported\n", eval_result->type);
            texit(1);
        }
        tree = cdr(tree);
    }
}
