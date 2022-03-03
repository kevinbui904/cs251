/**
 * @file eval_quote.c
 * @author Thien K. M. Bui and Victor Huang
 * @brief evaluate Scheme quote expression to be used in interpreter.c
 * @version 0.1
 * @date 2022-03-03
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

Value *eval_quote(Value *args)
{
    // check that number of args is correct
    Value *current_arg = args;

    if (isNull(current_arg))
    {
        printf("Evaluation error: missing arguments in quote\n");
        texit(1);
    }

    int args_count = 0;
    while (!isNull(current_arg))
    {
        if (args_count >= 1)
        {
            printf("Evaluation error: too many arguments in quote\n");
            texit(1);
        }
        args_count = args_count + 1;
        current_arg = cdr(current_arg);
    }

    return car(args);
}