/**
 * @file prim_adv_math.c
 * @author Thien K. M. Bui
 * @brief  Implementation for Scheme *, /, and modulo functions
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

Value *prim_multiply(Value *args)
{
    Value *current_arg = args;

    double product = 1;
    int make_double = 0;

    while (!isNull(current_arg))
    {
        if (car(current_arg)->type == INT_TYPE)
        {
            product = product * car(current_arg)->i;
        }
        else if (car(current_arg)->type == DOUBLE_TYPE)
        {
            make_double = 1;
            product = product * car(current_arg)->d;
        }
        else
        {
            printf("Evaluation error: incorrect type enum[%i] found in *\n", car(current_arg)->i);
            texit(1);
        }
        current_arg = cdr(current_arg);
    }

    Value *val_product = talloc(sizeof(Value));
    if (make_double == 0)
    {
        val_product->type = INT_TYPE;
        val_product->i = (int)product;
        return val_product;
    }
    else
    {
        val_product->type = DOUBLE_TYPE;
        val_product->d = product;
        return val_product;
    }
}

Value *prim_division(Value *args)
{
    // check that there's only 2 arguments
    Value *current_arg = args;
    int args_count = 0;

    while (!isNull(current_arg))
    {
        if (args_count > 2)
        {
            printf("Evaluation error: too many arguments found in / \n");
            texit(1);
        }
        args_count = args_count + 1;
        current_arg = cdr(current_arg);
    }

    double dividend, divisor;

    // set dividend
    if (car(args)->type == INT_TYPE)
    {
        dividend = car(args)->i;
    }
    else if (car(args)->type == DOUBLE_TYPE)
    {
        dividend = car(args)->d;
    }
    else
    {
        printf("Evaluation error: incorrect type found in / \n");
        texit(1);
    }

    // set divisor
    if (car(cdr(args))->type == INT_TYPE)
    {
        divisor = car(cdr(args))->i;
    }
    else if (car(cdr(args))->type == DOUBLE_TYPE)
    {
        divisor = car(cdr(args))->d;
    }
    else
    {
        printf("Evaluation error: incorrect type found in / \n");
        texit(1);
    }

    double quotient = dividend / divisor;

    Value *val_quotient = talloc(sizeof(Value));

    // check if quotient is integer
    if (quotient == (int)quotient)
    {
        val_quotient->type = INT_TYPE;
        val_quotient->i = (int)quotient;
        return val_quotient;
    }
    else
    {
        val_quotient->type = DOUBLE_TYPE;
        val_quotient->d = quotient;
        return val_quotient;
    }
}

Value *prim_modulo(Value *args)
{
    // check that there's only 2 arguments
    Value *current_arg = args;
    int args_count = 0;

    while (!isNull(current_arg))
    {
        if (args_count > 2)
        {
            printf("Evaluation error: too many arguments found in / \n");
            texit(1);
        }
        args_count = args_count + 1;
        current_arg = cdr(current_arg);
    }

    int arg1 = car(args)->i;
    int arg2 = car(cdr(args))->i;

    int modded = arg1 % arg2;

    Value *val_modded = talloc(sizeof(Value));
    val_modded->type = INT_TYPE;
    val_modded->i = modded;

    return val_modded;
}