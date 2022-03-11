/**
 * @file eval_if.c
 * @author Thien K. M. Bui, Victor Huang
 * @brief evaluate if Scheme expression to be used in interpreter.c
 * @version 0.1
 * @date 2022-03-02
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

Value *eval_if(Value *args, Frame *parent_frame)
{
    Value *check_args_count = cdr(args);
    int consequences_count = 0;
    // check that if is of valid format
    while (!isNull(check_args_count))
    {
        if (consequences_count > 2)
        {
            printf("Syntax error in (if): too many expressions in if block\n");
            texit(1);
        }
        consequences_count = consequences_count + 1;
        check_args_count = cdr(check_args_count);
    }
    if (consequences_count < 2)
    {
        printf("Evaluation error: not enough consequences following an if.\n");
        texit(1);
    }

    Value *eval_result = eval(car(args), parent_frame);
    if (eval_result->type == BOOL_TYPE)
    {
        // if true
        if (eval_result->i == 1)
        {
            Value *eval_result = eval(car(cdr(args)), parent_frame);
            return eval_result;
        }
        else if (eval_result->i == 0)
        {
            Value *eval_result = eval(car(cdr(cdr(args))), parent_frame);
            return eval_result;
        }
    }
    else
    {
        printf("Syntax Error in (if): conditional does not return valid boolean value\n");
        texit(1);
    }
    return makeNull();
}