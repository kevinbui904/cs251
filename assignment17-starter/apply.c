/**
 * @file apply.c
 * @author Thien K. M. Bui and Victor Huang
 * @brief make a new stack_frame using args and then return an eval of (function, new_frame);
 * @version 0.1
 * @date 2022-03-06
 *
 * @copyright Copyright (c) 2022 Thien K. M. Bui <buik@carleton.edu>
 *
 */

/**
 * @brief
 *
 * @param function
 * @param args
 * @return Value*
 */

#include <stdio.h>
#include <string.h>

#include "value.h"
#include "linkedlist.h"
#include "interpreter.h"
#include "talloc.h"

Value *apply(Value *function, Value *args)
{
    if (function->type != CLOSURE_TYPE)
    {
        printf("Interpreter Error: incorrect type enum[%i] found in apply\n", function->type);
        texit(1);
    }
    Value *params = function->cl.paramNames;
    Value *fn_code = function->cl.functionCode;
    Frame *active_frame = function->cl.frame;
    while (!isNull(params))
    {
        printf("param: %s\n", car(params)->s);
        int bounded = 0;
        Value *bindings = active_frame->bindings;

        Value *current_param = car(params);
        // search for the param in the active_frame to rebind

        while (!isNull(bindings))
        {
            printf("bindings: %s, %i\n", car(car(bindings))->s, cdr(car(bindings))->type);
            Value *current_binding = car(bindings);
            if (cdr(current_binding)->type == SYMBOL_TYPE)
            {
                char *symbol = cdr(current_binding)->s;
                if (strcmp(current_param->s, symbol) == 0)
                {
                    current_binding = cons(current_binding, car(args));
                    bounded = 1;
                    break;
                }
            }

            bindings = cdr(bindings);
        }
        // new binding
        if (bounded == 0)
        {
            Value *new_binding = cons(current_param, car(args));
            active_frame->bindings = cons(new_binding, active_frame->bindings);
        }

        args = cdr(args);
        params = cdr(params);
    }
    printf("------------------------------------\n");
    // printf("fn_code: %i, %i, %s, %s, %s\n", fn_code->type, car(fn_code)->type, car(fn_code)->s, car(cdr(fn_code))->s, car(cdr(cdr(fn_code)))->s);
    Value *eval_result = eval(fn_code, active_frame);
    printf("eval_result: %i\n", eval_result->type);
    return eval_result;
    // call eval on function->expr, but the frame is constructed from args
}