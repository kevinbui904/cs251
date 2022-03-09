/**
 * @file look_up_symbol.c
 * @author Thien K. M. Bui and Victor Huang
 * @brief
 * @version 0.1
 * @date 2022-03-08
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

Value *look_up_symbol(Value *expr, Frame *frame)
{
    // iterate through all parents frame and look for symbol (this is lookup symbol)
    Frame *active_frame = frame;
    while (active_frame != NULL)
    {

        // iterate through all the bindings of this frame
        Value *current_binding = active_frame->bindings;
        while (!isNull(current_binding))
        {
            if (current_binding->type == CONS_TYPE)
            {

                Value *symbol = car(car(current_binding));
                Value *value = cdr(car(current_binding));
                if (strcmp(symbol->s, expr->s) == 0)
                {
                    // if x is storing a linked list
                    if (value->type == CONS_TYPE)
                    {
                        return value;
                    }

                    return eval(value, frame);
                }
                current_binding = cdr(current_binding);
            }
            else
            {
                printf("Interpreter error: incorrect type enum[%i] found in frame\n", current_binding->type);
                texit(1);
                return makeNull();
            }
        }
        active_frame = active_frame->parent;
    }
    printf("Evaluation error: symbol '%s' not found.\n", expr->s);
    texit(1);
    return makeNull();
}