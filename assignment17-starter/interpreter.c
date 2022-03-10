/**
 * @file interpreter.c
 * @author Thien K. M. Bui and Victor Huang
 * @brief
 * @version 0.2
 * @date 2022-03-09
 *
 * @copyright Copyright (c) 2022 Thien K. M. Bui <buik@carleton.edu>
 *
 */

#include <string.h>
#include <stdio.h>

#include "value.h"
#include "linkedlist.h"
#include "talloc.h"
#include "eval_let.h"
#include "eval_if.h"
#include "look_up_symbol.h"
#include "eval_quote.h"
#include "eval_define.h"
#include "eval_lambda.h"
#include "apply.h"
#include "primitive_fn.h"

Value *eval(Value *expr, Frame *frame)
{
    switch (expr->type)
    {
    case SYMBOL_TYPE:
    {
        return look_up_symbol(expr, frame);

        break;
    }
    // should happens when there is a new sub-level (set of parenthesis)
    case CONS_TYPE:
    {
        Value *first = car(expr);
        Value *args = cdr(expr);

        if (strcmp(first->s, "if") == 0)
        {
            return eval_if(args, frame);
        }
        // strcmp returns 0 if the 2 strings matches
        else if (strcmp(first->s, "let") == 0)
        {
            return eval_let(args, frame);
        }
        else if (strcmp(first->s, "quote") == 0)
        {
            return eval_quote(args);
        }
        else if (strcmp(first->s, "define") == 0)
        {
            Value *value = cdr(args);
            return eval_define(args, value, frame);
        }
        else if (strcmp(first->s, "lambda") == 0)
        {
            Value *body = cdr(args);
            return eval_lambda(args, body, frame);
        }
        // unrecognized forms goes here
        else
        {
            // If it's not a special form, evaluate
            // 'first', evaluate the args, then
            // apply 'first' on the args.
            Value *evaluated_operator = eval(first, frame);
            Value *evaluated_args = makeNull();

            Value *current_cons = args;
            while (!isNull(current_cons))
            {
                Value *evaled = eval(car(current_cons), frame);
                evaluated_args = cons(evaled, evaluated_args);
                current_cons = cdr(current_cons);
            }
            evaluated_args = reverse(evaluated_args);

            // call primitive function if it is, otherwise apply
            if (evaluated_operator->type == PRIMITIVE_TYPE)
            {
                struct Value *(*fn_to_call)(struct Value *) = evaluated_operator->pf;
                return (*fn_to_call)(evaluated_args);
            }
            else
            {
                return apply(evaluated_operator, evaluated_args);
            }
        }

        return makeNull();
        break;
    }
    // atomic values
    default:
    {
        return expr;
    }
    }
}

/**
 * @brief helper for printing out eval return types
 *
 * @param value
 */
void print_helper(Value *value)
{
    switch (value->type)
    {

    case INT_TYPE:
        printf("%i ", value->i);
        break;
    case DOUBLE_TYPE:
        printf("%f ", value->d);

        break;
    case STR_TYPE:
        printf("\"%s\" ", value->s);

        break;
    case NULL_TYPE:
        printf("()");

        break;
    case PTR_TYPE:
        printf("%p ", value->p);

        break;
    case BOOL_TYPE:
        if (value->i == 0)
        {
            printf("#f ");
        }
        else
        {
            printf("#t ");
        }
        break;
    case SYMBOL_TYPE:
        printf("%s ", value->s);
        break;
    case CLOSURE_TYPE:
        printf("#<procedure> ");
        break;
    default:
        printf("Interpreter error: print type [%i] not supported\n", value->type);
        texit(1);
    }
}
/**
 * @brief helper for printing out CONS return_type
 *
 * @param value
 */
void print_cons_helper(Value *value)
{
    Value *current = value;

    // Special Print for Dotted Pairs
    if (cdr(current)->type != CONS_TYPE && !isNull(cdr(current)))
    {
        printf("(");
        if(car(current)->type == CONS_TYPE){
            print_cons_helper(car(current));
        }else{
            print_helper(car(current));
        }
        
        printf(" . ");
        print_helper(cdr(current));
        printf(")");
    }
    else
    {
        printf("(");
        while (!isNull(current))
        {
            if (car(current)->type == CONS_TYPE)
            {
                print_cons_helper(car(current));
            }
            else
            {
                print_helper(car(current));
            }
            current = cdr(current);
        }
        printf(")");
    }
}

/**
 * @brief bind primitive function to global_frame
 *
 * @param name
 * @param function
 * @param frame
 */
void bind_primitive_fn(char *name, Value *(*function)(struct Value *), Frame *frame)
{

    Value *prim_symbol = talloc(sizeof(Value));
    prim_symbol->type = SYMBOL_TYPE;
    prim_symbol->s = name;

    Value *prim_fn = talloc(sizeof(Value));
    prim_fn->type = PRIMITIVE_TYPE;
    prim_fn->pf = function;

    // Bind 'name' to 'function' in 'frame'

    Value *prim_binding = cons(prim_symbol, prim_fn);
    frame->bindings = cons(prim_binding, frame->bindings);
}
/*
interpret()
call eval() on EVERY top-level node
*/
void interpret(Value *tree)
{
    // make empty Frame
    Frame global_frame;
    global_frame.bindings = makeNull();
    global_frame.parent = NULL;

    // Create bindings in the global frame for all of
    // the built-in functions.
    // bind_primitive_fn("car", &builtInCar, globalFrame);
    // bind_primitive_fn("cons", &builtInCdr, globalFrame);
    bind_primitive_fn("+", &prim_add, &global_frame);
    bind_primitive_fn("null?", &prim_null, &global_frame);
    bind_primitive_fn("car", &prim_car, &global_frame);
    bind_primitive_fn("cdr", &prim_cdr, &global_frame);
    bind_primitive_fn("cons", &prim_cons, &global_frame);

    while (!isNull(tree))
    {
        Value *eval_result = eval(car(tree), &global_frame);
        // print out result

        if (eval_result->type == CONS_TYPE)
        {
            print_cons_helper(eval_result);
            printf("\n");
        }
        else if (eval_result->type == VOID_TYPE)
        {
            global_frame.bindings = eval_result->p;
        }
        else
        {
            print_helper(eval_result);
            printf("\n");
        }
        tree = cdr(tree);
    }
}