/*
interpreter.c
Written by Victor Huang and Thien K. M. Bui
Last editted 02-23-22
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
        // iterate through all parents frame and look for symbol
        Frame *current_frame = frame;
        while (current_frame != NULL)
        {
            // iterate through all the bindings of this frame
            Value *current_binding = current_frame->bindings;
            while (!isNull(current_binding))
            {
                if (current_binding->type == CONS_TYPE)
                {
                    char *symbol = car(current_binding)->s;
                    Value *value = cdr(current_binding);

                    if (strcmp(symbol, expr->s))
                    {
                        return value;
                    }
                    else
                    {
                        current_binding = cdr(current_binding);
                    }
                }
                else
                {
                    printf("Interpreter error: incorrect type found in frame\n");
                    texit(1);
                    return makeNull();
                }
            }
            current_frame = current_frame->parent;
        }
        printf("Syntax error: symbol %s not defined\n", expr->s);
        texit(1);
        return makeNull();
        // return lookUpSymbol(expr, frame);
        break;
    }
    case CONS_TYPE:
    {
        Value *first = car(expr);
        Value *args = cdr(expr);

        // if first is "if"
        if (strcmp(first->s, "if"))
        {
            // Frame *result = evalIf(args, frame);
        }
        else if (strcmp(first->s, "let"))
        {
            Frame *let_frame;
            let_frame->parent = frame; 
            let_frame->bindings = makeNull();

            Value *current_arg = car(args);
            if(current_arg->type == CONS_TYPE){
                printf("this works\n");
                texit(1);
            }
            // evalLet (assign all the symbols to their values and push onto the Frame stack)
            while (!isNull(current_arg))
            {
                // iterate through ALL binding pairs
                if (current_arg->type == CONS_TYPE)
                {
                    // valid symbol
                    if (car(current_arg)->type == SYMBOL_TYPE)
                    {
                        // binding i in list of bindings
                        Value *binding = car(current_arg);

                        Value *symbol = car(binding);
                        Value *value = cdr(binding);

                        if (!isNull(cdr(cdr(current_arg))))
                        {
                            printf("Syntax Error in (let): too many arguments\n");
                            texit(1);
                        }
                        // add bindings to the frame
                        else
                        {
                            let_frame->bindings = cons(cons(symbol, binding), let_frame->bindings);
                        }
                    }
                    // leave nodes
                    else
                    {
                        printf("Syntax Error in (let): incorrect form\n");
                        texit(1);
                    }
                    current_arg = cdr(current_arg);
                }
                else
                {
                    printf("Syntax Error: incorrect number of arguments for function let\n");
                    texit(1);
                }
                current_arg = cdr(current_arg);
            }

            Value *body = cdr(args);
            return eval(body, let_frame);
        }
        // Other special forms go here...
        else
        {
            // 'first' is not a recognized special form
            // evalationError();
            printf("Symbol not recognized\n");
            texit(1);
        }
        break;
    }
    default:
    {
        printf("this hits here\n");
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
    Value *current_top_level = tree;

    while (!isNull(current_top_level))
    {
        // make empty Frame
        Frame *empty_frame;
        empty_frame->bindings = makeNull();
        empty_frame->parent = NULL;

        Value *eval_result = eval(car(current_top_level), empty_frame);

        // if (eval_result->type == INT_TYPE)
        // {
        //     printf("god bless\n");
        // }
        // else if (eval_result->type == CONS_TYPE)
        // {
        //     printf("interesting\n");
        // }
        // else if (eval_result->type == NULL_TYPE)
        // {
        //     printf("what\n");
        // }
        // else
        // {
        //     printf("Something is very wrong")
        // }
        current_top_level = cdr(current_top_level);
    }
}
