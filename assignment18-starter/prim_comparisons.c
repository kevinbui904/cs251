/**
 * @file prim_comparison.c
 * @author Thien K. M. Bui <buik@carleton.edu>
 * @brief primitive comparisons (=, <, >) Scheme functions
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

/**
 * @brief primitive equal, to be used for integer/float comparison in Scheme
 *
 * @param args
 * @return Value*
 */
Value *prim_equal(Value *args)
{

    double base_for_comparison;
    if (car(args)->type == INT_TYPE)
    {
        base_for_comparison = car(args)->i;
    }
    else if (car(args)->type == DOUBLE_TYPE)
    {
        base_for_comparison = car(args)->d;
    }
    Value *current = args;

    Value *boolean = talloc(sizeof(Value));
    boolean->type = BOOL_TYPE;

    while (!isNull(current))
    {
        if (car(current)->type == DOUBLE_TYPE)
        {
            // return false
            if (base_for_comparison != car(current)->d)
            {
                boolean->i = 0;
                return boolean;
            }
        }
        else if (car(current)->type == INT_TYPE)
        {
            // return false
            if (base_for_comparison != car(current)->i)
            {
                boolean->i = 0;
                return boolean;
            }
        }
        else
        {
            printf("Evaluation error: incorrect type enum[%i] found in = operator\n", car(current)->type);
            texit(1);
        }
        current = cdr(current);
    }

    boolean->i = 1;
    return boolean;
}

/**
 * @brief primitive less than, to be used for integer/float comparison in Scheme
 *
 * @param args
 * @return Value*
 */

Value *prim_less_than(Value *args)
{
    Value *current_arg = args;

    int args_count = 0;
    while (!isNull(current_arg))
    {
        args_count = args_count + 1;
        current_arg = cdr(current_arg);
    }

    if (args_count < 2)
    {
        printf("Interpreter error: not enough arguments found in <\n");
        texit(1);
    }
    else if (args_count > 2)
    {
        printf("Interpreter error: too many arguments found in <\n");
        texit(1);
    }

    current_arg = args;

    double first_arg;
    double second_arg;

    // check that first arg is legit
    if (car(current_arg)->type == INT_TYPE)
    {
        first_arg = car(current_arg)->i;
    }
    else if (car(current_arg)->type == DOUBLE_TYPE)
    {
        first_arg = car(current_arg)->d;
    }
    else
    {
        printf("Evaluation error: incorrect type found in argument of < \n");
        texit(1);
    }

    current_arg = cdr(current_arg);
    // check that second arg is legit
    if (car(current_arg)->type == INT_TYPE)
    {
        second_arg = car(current_arg)->i;
    }
    else if (car(current_arg)->type == DOUBLE_TYPE)
    {
        second_arg = car(current_arg)->d;
    }
    else
    {
        printf("Evaluation error: incorrect type found in argument of < \n");
        texit(1);
    }

    Value *boolean = talloc(sizeof(Value));
    boolean->type = BOOL_TYPE;

    if (first_arg < second_arg)
    {
        boolean->i = 1;
    }
    else
    {
        boolean->i = 0;
    }

    return boolean;
}

/**
 * @brief primitive greater than, to be used for integer/float comparison in Scheme
 *
 * @param args
 * @return Value*
 */

Value *prim_greater_than(Value *args)
{
    Value *current_arg = args;

    int args_count = 0;
    while (!isNull(current_arg))
    {
        args_count = args_count + 1;
        current_arg = cdr(current_arg);
    }

    if (args_count < 2)
    {
        printf("Interpreter error: not enough arguments found in <\n");
        texit(1);
    }
    else if (args_count > 2)
    {
        printf("Interpreter error: too many arguments found in <\n");
        texit(1);
    }

    current_arg = args;

    double first_arg;
    double second_arg;

    // check that first arg is legit
    if (car(current_arg)->type == INT_TYPE)
    {
        first_arg = car(current_arg)->i;
    }
    else if (car(current_arg)->type == DOUBLE_TYPE)
    {
        first_arg = car(current_arg)->d;
    }
    else
    {
        printf("Evaluation error: incorrect type found in argument of < \n");
        texit(1);
    }

    current_arg = cdr(current_arg);
    // check that second arg is legit
    if (car(current_arg)->type == INT_TYPE)
    {
        second_arg = car(current_arg)->i;
    }
    else if (car(current_arg)->type == DOUBLE_TYPE)
    {
        second_arg = car(current_arg)->d;
    }
    else
    {
        printf("Evaluation error: incorrect type found in argument of < \n");
        texit(1);
    }

    Value *boolean = talloc(sizeof(Value));
    boolean->type = BOOL_TYPE;

    if (first_arg > second_arg)
    {
        boolean->i = 1;
    }
    else
    {
        boolean->i = 0;
    }

    return boolean;
}