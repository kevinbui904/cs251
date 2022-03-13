/**
 * @file apply.c
 * @author Thien K. M. Bui and Victor Huang
 * @brief make a new stack_frame using args and then return an eval of (function, new_frame);
 * @version 0.1
 * @date 2022-03-09
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
    // Frame *parent_frame = function->cl.frame;

    Frame *new_frame = talloc(sizeof(Frame));
    new_frame->parent = function->cl.frame;
    new_frame->bindings = makeNull();
    while (!isNull(params))
    {
        Value *current_param = car(params);
        printf("inside apply: [%s,%i]\n", current_param->s, car(args)->i);

        Value *new_binding = cons(current_param, car(args));
        new_frame->bindings = cons(new_binding, new_frame->bindings);

        args = cdr(args);
        params = cdr(params);
    }

    printf("before evaluating inside apply==============================\n");
    Value *test = new_frame->bindings;
    while (!isNull(test))
    {
        Value *bounded = car(test);
        printf("bounded pairs: [%s, %i]\n", car(bounded)->s, cdr(bounded)->i);
        test = cdr(test);
    }

    Frame *parent = new_frame->parent;
    Value *test2 = parent->bindings;

    while (!isNull(test2))
    {
        Value *bounded = car(test2);
        printf("bounded parent pairs: [%s, %i]\n", car(bounded)->s, cdr(bounded)->i);
        test2 = cdr(test2);
    }
    printf("===============================\n");
    Value *eval_result = eval(fn_code, new_frame);

    *function->cl.frame = *new_frame;

    return eval_result;
}