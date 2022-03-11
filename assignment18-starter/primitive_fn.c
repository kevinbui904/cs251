/**
 * @file primitive_fn.c
 * @author Thien K. M. Bui and Victor Huang
 * @brief primitive Scheme fn definition: add, null, car, cdr, and cons
 * @version 0.1
 * @date 2022-03-10
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
 * @brief built in addition, to be used in interpreter.c
 *
 * @param args
 * @return Value*
 */
Value *prim_add(Value *args)
{
    double sum = 0.0;
    int return_double = 0;
    Value *current_arg = args;
    while (!isNull(current_arg))
    {
        Value *current_value = car(current_arg);
        if (current_value->type != INT_TYPE && current_value->type != DOUBLE_TYPE)
        {
            printf("Evaluation error: + must take numbers.\n");
            texit(1);
        }

        else if (current_value->type == DOUBLE_TYPE)
        {
            return_double = 1;
            sum = sum + current_value->d;
        }

        else
        {
            sum = sum + current_value->i;
        }
        current_arg = cdr(current_arg);
    }

    // make return value
    Value *sum_value = talloc(sizeof(Value));
    if (return_double == 1)
    {

        sum_value->type = DOUBLE_TYPE;
        sum_value->d = sum;
    }
    else
    {
        sum_value->type = INT_TYPE;
        sum_value->i = (int)sum;
    }

    return sum_value;
}

/**
 * @brief built in null, check whether value is of null type, to be used in interpreter.c
 *
 * @param arg
 * @return Value*
 */
Value *prim_null(Value *arg)
{

    Value *current = arg;
    Value *boolean = talloc(sizeof(Value));
    int args_count = 0;
    while (!isNull(current))
    {
        current = cdr(current);
        args_count = args_count + 1;
    }
    if (args_count < 1)
    {
        printf("Evaluation error: no arguments supplied to null?\n");
        texit(1);
    }
    else if (args_count > 1)
    {
        printf("Evaluation error: null? takes one argument\n");
        texit(1);
    }
    boolean->type = BOOL_TYPE;
    if (isNull(car(arg)))
    {
        boolean->i = 1;
        return boolean;
    }
    else
    {
        boolean->i = 0;
        return boolean;
    }
}

/**
 * @brief primitive car function to be used for list in scheme
 *
 * @param arg
 * @return Value*
 */
Value *prim_car(Value *arg)
{
    Value *current = arg;
    int count = 0;
    while (!isNull(current))
    {
        current = cdr(current);
        count = count + 1;
    }
    if (count > 1)
    {
        printf("Evaluation error: car takes one argument\n");
        texit(1);
    }
    if (car(arg)->type != CONS_TYPE)
    {
        printf("Evaluation error: car takes a pair.\n");
        texit(1);
    }
    return car(car(arg));
}

/**
 * @brief primitive cdr function to be used for scheme lists
 *
 * @param arg
 * @return Value*
 */

Value *prim_cdr(Value *arg)
{
    Value *current = arg;
    // display(arg);
    int args_count = 0;
    while (!isNull(current))
    {
        current = cdr(current);
        args_count = args_count + 1;
    }

    if (args_count < 1)
    {
        printf("Evaluation error: no arguments supplied to cdr.\n");
        texit(1);
    }
    else if (args_count > 1)
    {
        printf("Syntax Error: prim_cdr, too many arguments in cdr \n");
        texit(1);
    }

    if (car(arg)->type != CONS_TYPE || isNull(car(arg)))
    {
        printf("Syntax Error: prim_cdr bad type enum[%i, %i] \n", car(arg)->type, car(arg)->i);
        texit(1);
    }

    return cdr(car(arg));
}

/**
 * @brief primitive cons function, used to make scheme pairs
 *
 * @param args
 * @return Value*
 */

Value *prim_cons(Value *args)
{
    int args_count = 0;
    Value *current = args;
    while (!isNull(current))
    {
        current = cdr(current);
        args_count = args_count + 1;
    }
    if (args_count == 0)
    {
        printf("Evaluation error: no arguments supplied to cons.\n");
        texit(1);
    }
    else if (args_count >= 3)
    {
        printf("Evaluation error: cons takes two arguments, three or more supplied.\n");
        texit(1);
    }
    else if (args_count < 2)
    {
        printf("Evaluation error: cons takes two arguments, only one supplied.\n");
        texit(1);
    }

    Value *lst1 = car(args);
    Value *lst2 = car(cdr(args));

    Value *new_cons = cons(lst1, lst2);

    return new_cons;
}

/**
 * @brief built in subtraction method, to be used in interpreter.c
 *
 * @param args
 * @return Value*
 */
Value *prim_subtract(Value *args)
{
    double difference = 0.0;
    int return_double = 0;
    Value *current_arg = args;
    while (!isNull(current_arg))
    {
        Value *current_value = car(current_arg);
        if (current_value->type != INT_TYPE && current_value->type != DOUBLE_TYPE)
        {
            printf("Evaluation error: + must take numbers.\n");
            texit(1);
        }

        else if (current_value->type == DOUBLE_TYPE)
        {
            return_double = 1;
            difference = difference - current_value->d;
        }

        else
        {
            difference = difference - current_value->i;
        }
        current_arg = cdr(current_arg);
    }

    // make return value
    Value *difference_value = talloc(sizeof(Value));
    if (return_double == 1)
    {

        difference_value->type = DOUBLE_TYPE;
        difference_value->d = difference;
    }
    else
    {
        difference_value->type = INT_TYPE;
        difference_value->i = (int)difference;
    }

    return difference_value;
}

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
