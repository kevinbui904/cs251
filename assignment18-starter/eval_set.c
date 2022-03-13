/**
 * @file eval_set.c
 * @author Thien K. M. Bui
 * @brief  rebind the nearest ancestral var binding (Scheme set function)
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

Value *eval_set(Value *args, Frame *active_frame)
{
    Value *current_arg = args;

    int args_count = 0;

    while (!isNull(current_arg))
    {
        if (args_count > 2)
        {
            printf("Evaluation error: too many arguments in set\n");
            texit(1);
        }
        args_count = args_count + 1;
        current_arg = cdr(current_arg);
    }

    Value *variable = car(args);
    Value *bind_value = eval(car(cdr(args)), active_frame);

    Frame *current_frame = active_frame;

    Value *void_type = talloc(sizeof(Value));
    void_type->type = VOID_TYPE;

    while (current_frame != NULL)
    {
        Value *current_binding = current_frame->bindings;

        while (!isNull(current_binding))
        {
            Value *bounded = car(current_binding);
            Value *bounded_var = car(bounded);
            Value *bounded_value = cdr(bounded);

            if (strcmp(bounded_var->s, variable->s) == 0)
            {
                *bounded_value = *bind_value;
                void_type->p = NULL;
                return void_type;
            }
            current_binding = cdr(current_binding);
        }
        current_frame = current_frame->parent;
    }

    printf("Evaluation error: variable %s not found\n", variable->s);
    texit(1);
    return makeNull();
}