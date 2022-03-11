/**
 * @file eval_letrec.c
 * @author Thien K. M. Bui
 * @brief eval_letrec expression, to be used in interpreter.c
 * @version 0.1
 * @date 2022-03-10
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

    Value *bounded = new_frame->bindings;
    while (!isNull(current_arg))
    {
        Value *current_binding_pair = car(current_arg);
        Value *value = eval(car(cdr(current_binding_pair)), new_frame);

        if (value->type == UNSPECIFIED_TYPE)
        {
            printf("Evaluation error: symbol not yet defined\n");
            texit(1);
        }
        else
        {
            Value *old_unspecified_bind = car(bounded);
            *old_unspecified_bind = *cons(car(old_unspecified_bind), value);
        }
        bounded = cdr(bounded);
        current_arg = cdr(current_arg);
    }

    Value *body = expr;
    Value *eval_result;

    while (!isNull(body))
    {
        printf("segfaulted here\n");
        eval_result = eval(car(body), new_frame);
        printf("definitely\n");
        body = cdr(body);
    }
    return eval_result;
}