/**
 * @file eval_let_star.c
 * @author Thien K. M. Bui and Victor Huang
 * @brief
 * @version 0.1
 * @date 2022-03-12
 *
 * @copyright Copyright (c) 2022 Thien K. M. Bui <buik@carleton.edu>
 *
 */

#include <stdio.h>
#include <string.h>

#include "value.h"
#include "linkedlist.h"
#include "interpreter.h"
#include "talloc.h"
Value *eval_let_star(Value *args, Value *expr, Frame *parent_frame)
{
    Value *current_arg = car(args);

    Frame *prev_frame = talloc(sizeof(Frame));
    prev_frame->bindings = makeNull();
    prev_frame->parent = parent_frame;

    while (!isNull(current_arg))
    {
        Value *current_binding_pair = car(current_arg);
        if (current_binding_pair->type != CONS_TYPE)
        {
            printf("Interpreter error: incorrect type enum[%i, %s] found in let*\n", current_binding_pair->type, current_binding_pair->s);
            texit(1);
        }

        Value *symbol = car(current_binding_pair);
        Value *value = eval(car(cdr(current_binding_pair)), prev_frame->parent);

        if (!isNull(cdr(cdr(current_binding_pair))))
        {
            printf("Syntax Error in (let): too many arguments\n");
            texit(1);
        }

        prev_frame->bindings = cons(cons(symbol, value), prev_frame->bindings);

        Frame *new_frame = talloc(sizeof(Frame));
        new_frame->bindings = makeNull();
        new_frame->parent = prev_frame;

        prev_frame = new_frame;
        current_arg = cdr(current_arg);
    }

    Value *body = expr;
    Value *eval_result;

    while (!isNull(body))
    {
        eval_result = eval(car(body), prev_frame);
        body = cdr(body);
    }
    return eval_result;
}