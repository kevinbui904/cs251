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

/*
validSymbol(char* s)
helper function to check for malformatted symbols
multi-char symbol cannot contains | ! | $ | % | & | * | / | : | < | = | > | ? | ~ | _ | ^
single-char symbols cannot be a number
*/
int validSymbol(char *s)
{
    return 1;
}

Value *tokenize()
{

    // Prepare list of tokens
    Value *tokens_list = makeNull();

    // Prepare the character stream
    char next_char;
    next_char = (char)fgetc(stdin);

    // used to store temporary strings
    char *temp_symbol = malloc(sizeof(char) * 300);

    // Start tokenizing!
    while (next_char != EOF)
    {
        // make a new Value token
        Value *new_token = talloc(sizeof(Value));

        // reserver space for a new cons_cell (node)
        Value *new_cons_cell = talloc(sizeof(Value));
        new_cons_cell->type = CONS_TYPE;

        // make closings
        if (next_char == '(')
        {

            new_token->type = OPEN_TYPE;
            new_cons_cell = cons(new_token, tokens_list);
            tokens_list = new_cons_cell;
        }
        // need to account for end condition in if () there no space before last )
        else if (next_char == ')')
        {
            // if temp_symbol is not freed (no space before closing is allowed)
            if (strlen(temp_symbol) > 0)
            {
                if (validSymbol(temp_symbol))
                {
                    new_token->type = SYMBOL_TYPE;

                    char *copy = talloc((sizeof(char)) * strlen(temp_symbol));
                    for (int i = 0; i < strlen(temp_symbol); i++)
                    {
                        copy[i] = temp_symbol[i];
                    }
                    new_token->s = copy;

                    new_cons_cell = cons(new_token, tokens_list);
                    tokens_list = new_cons_cell;
                    free(temp_symbol);
                    temp_symbol = malloc(sizeof(char) * 300);

                    // special case
                    Value *null_token = talloc(sizeof(Value));
                    null_token->type = CLOSE_TYPE;
                    new_cons_cell = cons(null_token, tokens_list);
                    tokens_list = new_cons_cell;
                }
                else
                {
                    assert(1 == 0 && "TokenizeError: symbol contains a non allowed character");
                }
            }
            else
            {
                new_token->type = CLOSE_TYPE;
                new_cons_cell = cons(new_token, tokens_list);
                tokens_list = new_cons_cell;
            }
        }

        // check for string (special else if (next_char ==since double quotes are not to be used as a symbol)
        else if (next_char == '"')
        {
            // if it's a malformed string (mismatched double quotes), throw an error

            // need to set to the next character right away else the check for terminating double quotes won't work
            next_char = (char)fgetc(stdin);
            while (next_char != EOF && 1)
            {
                // well formed string, make string literal
                if (next_char == '"')
                {
                    break;
                }
                else
                {
                    temp_symbol[strlen(temp_symbol)] = next_char;
                    next_char = (char)fgetc(stdin);
                }
            }
            // if malformed string just throw error
            if (next_char == EOF)
            {
                assert(1 == 0 && "TokenizeError: malformatted string literals");
            }
            else
            {
                // copy over string
                // NOTE: only - 1 because the temp_string DOES NOT include the first double quote
                char *copy = talloc((sizeof(char)) * strlen(temp_symbol));

                for (int i = 0; i < strlen(temp_symbol); i++)
                {
                    copy[i] = temp_symbol[i];
                }

                // store string (char*) into Value new_string

                free(temp_symbol);
                temp_symbol = malloc(sizeof(char) * 300);

                new_token->type = STR_TYPE;
                new_token->s = copy;

                new_cons_cell = cons(new_token, tokens_list);
                tokens_list = new_cons_cell;
            }
        }
        // check for empty space (used as delimiter), if hit, just restart the temporary symbol
        else if (next_char == ' ')
        {
            // check valid symbol (cannot contains | ! | $ | % | & | * | / | : | < | = | > | ? | ~ | _ | ^)
            if (validSymbol(temp_symbol))
            {
                new_token->type = SYMBOL_TYPE;

                // copy over the symbol only if the symbol is not empty
                if (strlen(temp_symbol) > 0)
                {
                    char *copy = talloc((sizeof(char)) * strlen(temp_symbol));
                    for (int i = 0; i < strlen(temp_symbol); i++)
                    {
                        copy[i] = temp_symbol[i];
                    }
                    new_token->s = copy;

                    new_cons_cell = cons(new_token, tokens_list);
                    tokens_list = new_cons_cell;
                    free(temp_symbol);
                    temp_symbol = malloc(sizeof(char) * 300);
                }
            }
            else
            {
                assert(1 == 0 && "TokenizeError: symbol contains a non allowed character");
            }

            // end of line character need to be catched
        }
        // if semicolon is seen, ignore the rest of this line
        else if (next_char == ';')
        {
            while (next_char != '\n' && next_char != EOF)
            {
                next_char = (char)fgetc(stdin);
            }
        }
        // ignore newline characters
        else if (next_char == '\n')
        {
            while (next_char != '\n' && next_char != EOF)
            {
                next_char = (char)fgetc(stdin);
            }
        }
        // by default, concatenate ALL char into a long string, concatenation stops upon first encounter wtih a whitespace character
        else
        {
            // assignment specificity, all strings will only be 300 characters long

            temp_symbol[strlen(temp_symbol)] = next_char;
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
        case STR_TYPE:
            printf("\"%s\":string\n", car(current)->s);
            break;
        case SYMBOL_TYPE:
            printf("%s:symbol\n", car(current)->s);
            break;
        default:
            printf("not yet implemented\n");
        }
        current = cdr(current);
    }
}
