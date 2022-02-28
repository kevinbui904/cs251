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
        printf("check this\n");
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
                active_frame = active_frame->parent;
            }
        }
        printf("Syntax error: symbol %s not defined\n", expr->s);
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
            // Frame *result = evalIf(args, frame);
        }
        // strcmp returns 0 if the 2 strings matches
        else if (strcmp(first->s, "let") == 0)
        {
            Frame *active_frame;
            active_frame->parent = frame;
            active_frame->bindings = makeNull();

            Value *current_arg = car(args);

            // evalLet (assign all the symbols to their values and push onto the Frame stack)
            while (!isNull(current_arg))
            {
                printf("inside while: %i\n", current_arg->type);
                // iterate through ALL binding pairs
                if (current_arg->type == CONS_TYPE)
                {
                    Value *current_binding = car(current_arg);
                    Value *symbol = car(current_binding);
                    // valid symbol
                    printf("check symbol: %i,%s\n", symbol->type, symbol->s);

                    if (symbol->type == SYMBOL_TYPE)
                    {
                        // binding i in list of bindings
                        Value *value = car(cdr(current_binding));
                        printf("check value: %i, %i\n", value->type, value->i);
                        if (!isNull(cdr(cdr(current_binding))))
                        {
                            printf("Syntax Error in (let): too many arguments\n");
                            texit(1);
                        }
                        // add bindings to the frame
                        else
                        {
                            // apply eval to the value
                            Value *eval_result = eval(value, active_frame);
                            printf("eval_result: %i\n", eval_result->type);
                            active_frame->bindings = cons(cons(symbol, value), active_frame->bindings);
                        }
                    }
                    // leaves nodes
                    else
                    {
                        printf("Syntax Error in (let) parameter: invalid type for symbol declaration\n");
                        texit(1);
                    }
                    current_arg = cdr(current_arg);
                }
                else
                {
                    printf("Syntax Error in (let) parameter: incorrect format\n");
                    texit(1);
                }
            }

            Value *body = cdr(args);
            printf("body: %i\n", body->type);
            return eval(body, active_frame);
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
        // printf("hits here\n");
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
        Frame *empty_frame;
        empty_frame->bindings = makeNull();
        empty_frame->parent = NULL;

        Value *eval_result = eval(car(tree), empty_frame);

        tree = cdr(tree);
    }
}
