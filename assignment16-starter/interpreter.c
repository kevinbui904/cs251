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
#include "eval_quote.h"
#include "eval_define.h"

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
        if (first->type == SYMBOL_TYPE)
        {
            if (strcmp(first->s, "if") == 0)
            {
                return eval_if(args, frame);
            }
            // strcmp returns 0 if the 2 strings matches
            else if (strcmp(first->s, "let") == 0)
            {
                return eval_let(args, frame);
            }
            else if (strcmp(first->s, "quote") == 0)
            {
                return eval_quote(args);
            }
            else if (strcmp(first->s, "define") == 0)
            {
                Value *value = cdr(args);
                return eval_define(args, value, frame);
            }
            // unrecognized forms goes here
            else
            {
                printf("Syntax Error: symbol not recognized\n");
                texit(1);
            }
        }
        else
        {
            printf("Syntax Error: symbol in bad form\n");
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

/**
 * @brief helper for printing out eval return types
 *
 * @param value
 */
void print_helper(Value *value)
{
    switch (value->type)
    {

    case INT_TYPE:
        printf("%i ", value->i);
        break;
    case DOUBLE_TYPE:
        printf("%f ", value->d);

        break;
    case STR_TYPE:
        printf("\"%s\" ", value->s);

        break;
    case NULL_TYPE:
        printf("()");

        break;
    case PTR_TYPE:
        printf("%p ", value->p);

        break;
    case BOOL_TYPE:
        if (value->i == 0)
        {
            printf("#f ");
        }
        else
        {
            printf("#t ");
        }
        break;
    case SYMBOL_TYPE:
        printf("%s ", value->s);
        break;
    default:
        printf("Interpreter error: print type [%i] not supported\n", value->type);
        texit(1);
    }
}
/**
 * @brief helper for printing out CONS return_type
 *
 * @param value
 */
void print_cons_helper(Value *value)
{
    Value *current = value;
    printf("(");
    while (!isNull(current))
    {
        if (car(current)->type == CONS_TYPE)
        {
            print_cons_helper(car(current));
        }
        else
        {

            print_helper(car(current));
        }
        current = cdr(current);
    }
    printf(")");
}

/*
interpret()
call eval() on EVERY top-level node
*/
void interpret(Value *tree)
{
    // make empty Frame
    Frame parent_frame;
    parent_frame.bindings = makeNull();
    parent_frame.parent = NULL;
    while (!isNull(tree))
    {
        Value *eval_result = eval(car(tree), &parent_frame);
        // print out result

        if (eval_result->type == CONS_TYPE)
        {
            print_cons_helper(eval_result);
            printf("\n");
        }
        else if (eval_result->type == VOID_TYPE)
        {
            parent_frame.bindings = eval_result->p;
        }
        else
        {
            print_helper(eval_result);
            printf("\n");
        }
        tree = cdr(tree);
    }
}