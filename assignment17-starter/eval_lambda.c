/**
 * @file eval_lambda.c
 * @author Thien K. M. Bui and Victor Huang
 * @brief evaluate lambda Scheme expression to be used in interpreter.c
 * @version 0.1
 * @date 2022-03-06
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <stdio.h>
#include <string.h>

#include "value.h"
#include "linkedlist.h"
#include "interpreter.h"
#include "talloc.h"
Value *eval_lambda(Value *args, Value *expr, Frame *active_frame)
{
    // make new CLOSURE_TYPE
    Value *closure_value = talloc(sizeof(Value));
    closure_value->type = CLOSURE_TYPE;

    args = car(args);
    expr = car(expr);

    // check that all args are symbol typed, also check that there's no duplicate variable names
    Value *current_arg = args;
    Value *duplicated = makeNull();
    while (!isNull(current_arg))
    {
        if (car(current_arg)->type != SYMBOL_TYPE || isNull(car(current_arg)))
        {
            printf("Evaluation error: formal parameters for lambda must be symbols.\n");
            texit(1);
        }

        Value *current_duplicate = duplicated;
        while (!isNull(current_duplicate))
        {
            if (strcmp(car(current_duplicate)->s, car(current_arg)->s) == 0)
            {
                printf("Evaluation error: duplicate identifier in lambda.\n");
                texit(1);
            }
            current_duplicate = cdr(current_duplicate);
        }
        duplicated = cons(car(current_arg), duplicated);
        current_arg = cdr(current_arg);
    }

    if (isNull(expr))
    {
        printf("Evaluation error: no code in lambda following parameters.\n");
        texit(1);
    }

    struct Closure new_closure;
    new_closure.paramNames = args;
    new_closure.functionCode = expr;
    new_closure.frame = active_frame;
    closure_value->cl = new_closure;

    return closure_value;
}