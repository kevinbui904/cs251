/**
 * @file prim_and_or.c
 * @author Thien K. M. Bui
 * @brief Scheme and/or evaluation rules
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

Value *eval_and(Value *args, Frame *active_frame)
{

    Value *current_arg = args;

    Value *boolean = talloc(sizeof(Value));

    boolean->type = BOOL_TYPE;

    while (!isNull(current_arg))
    {
        Value *eval_result = eval(car(current_arg), active_frame);

        if (eval_result->type != BOOL_TYPE)
        {
            printf("Evaluation error: invalid argument type enum[%i] found in and\n", eval_result->type);
            texit(1);
        }

        // if any of the arguments evaluates to false;
        if (eval_result->i == 0)
        {
            boolean->i = 0;
            return boolean;
        }
        current_arg = cdr(current_arg);
    }

    boolean->i = 1;
    return boolean;
}

Value *eval_or(Value *args, Frame *active_frame)
{
    Value *current_arg = args;

    Value *boolean = talloc(sizeof(Value));

    boolean->type = BOOL_TYPE;

    while (!isNull(current_arg))
    {
        Value *eval_result = eval(car(current_arg), active_frame);

        if (eval_result->type != BOOL_TYPE)
        {
            printf("Evaluation error: invalid argument type enum[%i] found in and\n", eval_result->type);
            texit(1);
        }

        // if any of the arguments evaluates to false;
        if (eval_result->i == 1)
        {
            boolean->i = 1;
            return boolean;
        }
        current_arg = cdr(current_arg);
    }

    boolean->i = 0;
    return boolean;
}