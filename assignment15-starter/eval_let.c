/**
 * @file eval_let.c
 * @author Thien K. M. Bui and Victor Huang
 * @brief evaluate Scheme let expression to be used in interpreter.c
 * @version 0.1
 * @date 2022-03-02
 *
 * @copyright Copyright (c) 2022 Thien K. M. Bui <buik@carleton.edu>
 *
 *
 **/

#include <stdio.h>
#include <string.h>

#include "value.h"
#include "linkedlist.h"
#include "interpreter.h"
#include "talloc.h"

Value *eval_let(Value *args, Frame *parent_frame)
{
    Frame new_frame;
    new_frame.bindings = makeNull();
    new_frame.parent = parent_frame;

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
                    Value *eval_result = eval(value, parent_frame);

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
