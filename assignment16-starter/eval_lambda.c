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
    struct Closure new_closure;
    new_closure.paramNames = args;
    new_closure.functionCode = expr;
    new_closure.frame = active_frame;
    closure_value->cl = new_closure;

    return closure_value;
}