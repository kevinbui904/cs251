/**
 * @file primitive_fn.c
 * @author Thien K. M. Bui and Victor Huang
 * @brief primitive Scheme fn definition: add, null, car, cdr, and cons
 * @version 0.1
 * @date 2022-03-07
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

Value *prim_add(Value *args)
{
    double sum = 0.0;
    int return_double = 0;
    Value *current_arg = args;
    while (!isNull(current_arg))
    {
        Value *current_value = car(current_arg);
        if (current_value->type != INT_TYPE && current_value->type != DOUBLE_TYPE)
        {
            printf("Interpreter Error: type enum[%i] not allowed in + operation\n", current_value->type);
            texit(1);
        }

        else if (current_value->type == DOUBLE_TYPE)
        {
            return_double = 1;
            sum = sum + current_value->d;
        }

        else
        {
            sum = sum + current_value->i;
        }
        current_arg = cdr(current_arg);
    }

    // make return value
    Value *sum_value = talloc(sizeof(Value));
    if (return_double == 1)
    {

        sum_value->type = DOUBLE_TYPE;
        sum_value->d = sum;
    }
    else
    {
        sum_value->type = INT_TYPE;
        sum_value->i = (int)sum;
    }

    return sum_value;
}

Value *prim_null(Value *arg);

Value *prim_car(Value *arg);

Value *prim_cdr(Value *arg);

Value *prim_cons(Value *args);