/*
interpreter.c
Written by Victor Huang and Thien K. M. Bui
Last editted 02-23-22
*/

#include <string.h>

#include "value.h"
#include "linkedlist.h"
#include "talloc.h"

Value *eval(Value *expr, Frame *frame)
{

    switch (expr->type)
    {
    case INT_TYPE:
    {
        return expr;
        break;
    }
    case SYMBOL_TYPE:
    {
        return expr;
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

            Value *current = car(args);
            // evalLet
            while (!isNull(current))
            {
                if (current->type == CONS_TYPE)
                {
                    // valid symbol
                    if (car(current)->type == SYMBOL_TYPE)
                    {
                        Value *current_binding = car(current);

                        // need to skip ahead twice so that our check for invalid binding works
                        current = cdr(current);
                        if (isNull(current))
                        {
                            printf("Syntax Error: incorrect number of arguments for function let\n");
                            texit(1);
                        }
                        else
                        {
                            Value *current_value = car(current);
                            // add this to the frame
                            let_frame->bindings = cons(cons(current_binding, current_value), let_frame->bindings);

                            current = cdr(current);
                        }
                    }
                    else
                    {
                        char symbol_type[10];
                        switch (car(current)->type)
                        {
                        case INT_TYPE:
                            strcpy(symbol_type, "INT");
                            break;
                        case DOUBLE_TYPE:
                            strcpy(symbol_type, "DOUBLE");
                            break;
                        case STR_TYPE:
                            strcpy(symbol_type, "STR");
                            break;
                        default:
                            strcpy(symbol_type, "OTHER");
                        }
                        printf("Syntax Error: symbol of type %s not supported, unable to bind\n", symbol_type);
                        texit(1);
                    }
                }
                else
                {
                    printf("Syntax Error: incorrect number of arguments for function let\n");
                    texit(1);
                }
                current = cdr(current);
            }
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
    }
}

/*
interpret()
call eval() on EVERY top-level node
*/
void interpret(Value *tree)
{
    Value *current = tree;
    while (!isNull(current))
    {
        // make empty Frame
        Frame *empty_frame;
        empty_frame->bindings = makeNull();
        eval(car(current), empty_frame);
        current = cdr(current);
    }
}
