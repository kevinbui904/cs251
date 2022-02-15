/*
tokenizer.c
Written by Victor Huang and Thien K. M. Bui
Last updated 02-14-2022
*/

#include <stdio.h>
#include <assert.h>
#include <string.h>

#include "value.h"
#include "talloc.h"
#include "linkedlist.h"
// Read source code that is input via stdin, and return a linked list consisting of the
// tokens in the source code. Each token is represented as a Value struct instance, where
// the Value's type is set to represent the token type, while the Value's actual value
// matches the type of value, if applicable. For instance, an integer token should have
// a Value struct of type INT_TYPE, with an integer value stored in struct variable i.
// See the assignment instructions for more details.

/*isString()
helper function
return 0 if false, 1 if true
*/
int isString(char *str)
{
    // if is a string (char)34 is a " in C
    if (str[0] == (char)34 && str[strlen(str)] == (char)34)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

Value *tokenize()
{

    // Prepare list of tokens
    Value *tokens_list = makeNull();

    // Prepare the character stream
    char next_char;
    next_char = (char)fgetc(stdin);

    // used to store temporary strings
    char *temporary_string = malloc(sizeof(char) * 300);

    // Start tokenizing!
    while (next_char != EOF)
    {
        // make a new Value token
        Value *new_token = talloc(sizeof(Value));

        // reserver space for a new cons_cell (node)
        Value *new_cons_cell = talloc(sizeof(Value));
        new_cons_cell->type = CONS_TYPE;

        switch (next_char)
        {
        // make closings
        case '(':
            new_token->type = OPEN_TYPE;
            new_cons_cell = cons(new_token, tokens_list);
            tokens_list = new_cons_cell;

            break;
        // need to account for end condition in case there no space before last )
        case ')':
            printf("%s: end here\n", temporary_string);
            new_token->type = CLOSE_TYPE;
            new_cons_cell = cons(new_token, tokens_list);
            tokens_list = new_cons_cell;
            break;
        // check for empty space (used as delimiter)
        case ' ':
            // check if valid string (check for quotes at beginning and end of stirng)
            if (isString(temporary_string))
            {
                printf("valid string: %s", temporary_string);
            }
            // if there's an opening quote but no terminating
            else if (temporary_string[0] == (char)34)
            {
                printf("doesn't wo0rk");
            }
            // if there's only a terminating quote
            else if (temporary_string[strlen(temporary_string)] == (char)34)
            {
            }
            // check if valid number

            // check if valid symbol
            printf("%s\n", temporary_string);
            free(temporary_string);
            temporary_string = malloc(sizeof(char) * 300);
            break;
        // end of line character need to be catched
        case '\n':
            printf("line break");
            break;

        // by default, concatenate ALL char into a long string, concatenation stops upon first encounter wtih a whitespace character
        default:
            // assignment specificity, all strings will only be 300 characters long

            temporary_string[strlen(temporary_string)] = next_char;
        }

        next_char = (char)fgetc(stdin);
    }

    // Reverse the tokens list, to put it back in order
    Value *reversed_list = reverse(tokens_list);

    // printf("length: %i", length(reversedList));

    return reversed_list;
}

// Display the contents of the list of tokens, along with associated type information.
// The tokens are displayed one on each line, in the format specified in the instructions.
void displayTokens(Value *list)
{

    Value *current = list;
    while (!isNull(current))
    {
        switch (car(current)->type)
        {
        case OPEN_TYPE:
            printf("(:open\n");
            break;
        case CLOSE_TYPE:
            printf("):close\n");
            break;
        default:
            printf("not yet implemented");
        }
        current = cdr(current);
    }
}
