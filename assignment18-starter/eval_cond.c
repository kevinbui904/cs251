/**
 * @file eval_cond.c
 * @author Thien K. M. Bui
 * @brief  Scheme eval for cond special form
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

Value *eval_cond(Value *args, Frame *active_frame)
{

    Value *current_arg = args;

    while (!isNull(cdr(current_arg)))
    {
        Value *current_cond_statement = car(current_arg);

        Value *boolean = eval(car(current_cond_statement), active_frame);
        if (boolean->i == 1)
        {
            return eval(car(cdr(current_cond_statement)), active_frame);
        }

        current_arg = cdr(current_arg);
    }

    // evaluate the else statement
    Value *current_cond_statement = car(current_arg);

    if (strcmp(car(current_cond_statement)->s, "else") == 0)
    {
        return eval(car(cdr(current_cond_statement)), active_frame);
    }
    else
    {
        Value *current_cond_statement = car(current_arg);

        Value *boolean = eval(car(current_cond_statement), active_frame);
        if (boolean->i == 1)
        {
            return eval(car(cdr(current_cond_statement)), active_frame);
        }
        // return VOID_TYPE since there's nothing to do here
        else
        {
            Value *new_void = talloc(sizeof(Value));
            new_void->type = VOID_TYPE;
            new_void->p = NULL;
            return new_void;
        }
    }
}