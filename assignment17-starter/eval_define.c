/**
 * @file eval_define.c
 * @author Thien K. M. Bui and Victor Huang
 * @brief modify the current active Frame with new bindings
 * @version 0.1
 * @date 2022-03-06
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

Value *eval_define(Value *symbol, Value *value, Frame *active_frame)
{
    // check that expression is in valid form (define var expr)
    if (!isNull(cdr(value)))
    {
        printf("Syntax Error: bad form in define expression\n");
        texit(1);
    }

    symbol = car(symbol);
    value = car(value);

    if (isNull(symbol))
    {
        printf("Evaluation error: no args following define.\n");
        texit(1);
    }
    else if (symbol->type != SYMBOL_TYPE)
    {
        printf("Evaluation error: define must bind to a symbol.\n");
        texit(1);
    }

    if (isNull(value))
    {
        printf("Evaluation error: no value following the symbol in define.\n");
        texit(1);
    }

    Value *value_to_bind = eval(value, active_frame);
    // look up value in frame if Value is of type symbol, make sure that it's good.

    char *symbol_str = symbol->s;
    Value *current_binding = active_frame->bindings;

    // return a VOID_TYPE Value with address of new bindings
    Value *void_type = talloc(sizeof(Value));
    void_type->type = VOID_TYPE;
    // search through active_frame->bindings to see if the symbol already exists
    while (!isNull(current_binding))
    {
        Value *bounded = car(current_binding);
        if (strcmp(car(bounded)->s, symbol_str) == 0)
        {
            bounded = cons(symbol, value_to_bind);
            void_type->p = active_frame->bindings;
            return void_type;
        }
        current_binding = cdr(current_binding);
    }
    Value *new_binding = cons(symbol, value_to_bind);
    active_frame->bindings = cons(new_binding, active_frame->bindings);
    void_type->p = active_frame->bindings;
    return void_type;
}