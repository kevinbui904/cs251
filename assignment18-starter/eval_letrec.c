/**
 * @file eval_letrec.c
 * @author Thien K. M. Bui
 * @brief eval_letrec expression, to be used in interpreter.c
 * @version 0.1
 * @date 2022-03-11
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

Value *eval_letrec(Value *args, Value *expr, Frame *parent_frame)
{
    Frame *new_frame = talloc(sizeof(Frame));
    new_frame->parent = parent_frame;
    new_frame->bindings = makeNull();

    Value *current_arg = car(args);

    while (!isNull(current_arg))
    {
        Value *current_binding_pair = car(current_arg);

        Value *symbol = car(current_binding_pair);

        Value *unspecified = talloc(sizeof(Value));
        unspecified->type = UNSPECIFIED_TYPE;

        new_frame->bindings = cons(cons(symbol, unspecified), new_frame->bindings);
        current_arg = cdr(current_arg);
    }

    current_arg = car(args);

    Value *new_bindings = makeNull();
    while (!isNull(current_arg))
    {
        Value *current_binding_pair = car(current_arg);
        Value *symbol = car(current_binding_pair);
        Value *value = eval(car(cdr(current_binding_pair)), new_frame);

        if (value->type == UNSPECIFIED_TYPE)
        {
            printf("Evaluation error: symbol not yet defined\n");
            texit(1);
        }
        else
        {
            new_bindings = cons(cons(symbol, value), new_bindings);
        }
        current_arg = cdr(current_arg);
    }
    new_frame->bindings = new_bindings;

    Value *body = expr;
    Value *eval_result;

    while (!isNull(body))
    {
        eval_result = eval(car(body), new_frame);
        body = cdr(body);
    }
    return eval_result;
}