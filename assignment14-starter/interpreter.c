/*
interpreter.c
Written by Victor Huang and Thien K. M. Bui
Last editted 02-28-22
*/

#include <string.h>
#include <stdio.h>

#include "value.h"
#include "linkedlist.h"
#include "talloc.h"

Value *eval(Value *expr, Frame *frame)
{
    switch (expr->type)
    {
    case SYMBOL_TYPE:
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
                        return value;
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
        // return lookUpSymbol(expr, frame);
        break;
    }
    // should happens when there is a new sub-level (set of parenthesis)
    case CONS_TYPE:
    {
        Value *first = car(expr);
        Value *args = cdr(expr);
        // if first is "if"
        if (strcmp(first->s, "if") == 0)
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

            Value *eval_result = eval(car(args), frame);
            if (eval_result->type == BOOL_TYPE)
            {
                // if true
                if (eval_result->i == 1)
                {
                    Value *eval_result = eval(car(cdr(args)), frame);
                    return eval_result;
                }
                else if (eval_result->i == 0)
                {
                    Value *eval_result = eval(car(cdr(cdr(args))), frame);
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
        // strcmp returns 0 if the 2 strings matches
        else if (strcmp(first->s, "let") == 0)
        {
            Frame new_frame;
            new_frame.bindings = makeNull();
            new_frame.parent = frame;

            Value *current_arg = car(args);

            // evalLet (assign all the symbols to their values and push onto the Frame stack)
            // iterate through ALL binding pairs
            while (!isNull(current_arg))
            {
                if (current_arg->type == CONS_TYPE)
                {
                    Value *current_binding = car(current_arg);
                    Value *symbol = car(current_binding);
                    // valid symbol
                    if (symbol->type == SYMBOL_TYPE)
                    {

                        Value *value = car(cdr(current_binding));
                        if (!isNull(cdr(cdr(current_binding))))
                        {
                            printf("Syntax Error in (let): too many arguments\n");
                            texit(1);
                        }
                        // add bindings to the frame
                        else
                        {
                            // check that bindings have not already been declared
                            Value *current_binding = new_frame.bindings;
                            while (!isNull(current_binding))
                            {
                                Value *already_bounded_symbol = car(car(current_binding));
                                if (strcmp(already_bounded_symbol->s, symbol->s) == 0)
                                {
                                    printf("Evaluation error: duplicate variable in let\n");
                                    texit(1);
                                }
                                current_binding = cdr(current_binding);
                            }

                            // apply eval to the value
                            Value *eval_result = eval(value, frame);

                            new_frame.bindings = cons(cons(symbol, eval_result), new_frame.bindings);
                        }
                    }
                    else
                    {
                        if (symbol->type == NULL_TYPE)
                        {
                            printf("Evaluation error: null binding in let.\n");
                            texit(1);
                        }
                        printf("Evaluation error: bad form in let.\n");
                        texit(1);
                    }
                }
                else
                {
                    printf("Evaluation error: bad form in let.\n");
                    texit(1);
                }
                current_arg = cdr(current_arg);
            }
            Value *body = cdr(args);
            Value *eval_result;

            if (body->type == NULL_TYPE)
            {
                printf("Evaluation error: no args following the bindings in let.\n");
                texit(1);
            }
            while (!isNull(body))
            {
                eval_result = eval(car(body), &new_frame);
                body = cdr(body);
            }
            return eval_result;
        }
        // Other special forms go here...
        else
        {
            printf("first: %s\n", car(first)->s);
            printf("Syntax Error: symbol not recognized\n");
            texit(1);
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

/*
interpret()
call eval() on EVERY top-level node
*/
void interpret(Value *tree)
{
    while (!isNull(tree))
    {
        // make empty Frame
        Frame empty_frame;
        empty_frame.bindings = makeNull();
        empty_frame.parent = NULL;

        Value *eval_result = eval(car(tree), &empty_frame);
        // print out result
        switch (eval_result->type)
        {
        case INT_TYPE:
            printf("%i\n", eval_result->i);
            break;
        case DOUBLE_TYPE:
            printf("%f\n", eval_result->d);

            break;
        case STR_TYPE:
            printf("\"%s\"\n", eval_result->s);

            break;
        case NULL_TYPE:
            printf("()\n");

            break;
        case PTR_TYPE:
            printf("%p\n", eval_result->p);

            break;
        case BOOL_TYPE:
            if (eval_result->i == 0)
            {
                printf("#f\n");
            }
            else
            {
                printf("#t\n");
            }
            break;
        default:
            printf("Interpreter error: print type [%i] not supported\n", eval_result->type);
            texit(1);
        }
        tree = cdr(tree);
    }
}
