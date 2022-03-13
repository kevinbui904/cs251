/**
 * @file eval_begin.c
 * @author Thien K. M. Bui
 * @brief   run eval on every arguments found in begin and return the final evaluation (Scheme begin eval)
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
Value *eval_begin(Value *args, Frame *active_frame)
{
    Value *current_arg = args;

    Value *eval_result;

    while (!isNull(current_arg))
    {
        printf("begin: %s\n", car(car(current_arg))->s);

        Value *test = eval(car(cdr(car(current_arg))), active_frame);
        printf("args: %i\n", test->i);
        if (car(current_arg)->type == SYMBOL_TYPE)
        {
            printf("symbol: %s\n", car(current_arg)->s);
        }
        eval_result = eval(car(current_arg), active_frame);
        printf("==============================\n");
        current_arg = cdr(current_arg);
    }
    return eval_result;
}