/*
tokenizer2.c
Written by Victor Huang and Thien K. M. Bui
Last updated 02-17-2022
*/

#include <stdio.h>
#include <string.h>
#include <ctype.h>

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
validInitialCharacter()
*/
int validInitialCharacter(char c)
{
    if (isalpha(c) ||
        (c == '!') ||
        (c == '$') ||
        (c == '%') ||
        (c == '&') ||
        (c == '*') ||
        (c == '/') ||
        (c == ':') ||
        (c == '<') ||
        (c == '=') ||
        (c == '>') ||
        (c == '?') ||
        (c == '~') ||
        (c == '_') ||
        (c == '^') ||
        (c == '+') ||
        (c == '-'))

    {
        return 1;
    }
    else
    {
        return 0;
    }
}

/*
validSubsequentCharacters()
*/
int validSubsequentCharacters(char *s)
{
    for (int i = 0; i < strlen(s); i++)
    {
        if (isalpha(s[i]) ||
            isdigit(s[i]) ||
            (s[i] == '!') ||
            (s[i] == '$') ||
            (s[i] == '%') ||
            (s[i] == '&') ||
            (s[i] == '*') ||
            (s[i] == '/') ||
            (s[i] == ':') ||
            (s[i] == '<') ||
            (s[i] == '=') ||
            (s[i] == '>') ||
            (s[i] == '?') ||
            (s[i] == '~') ||
            (s[i] == '_') ||
            (s[i] == '^') ||
            (s[i] == '.') ||
            (s[i] == '+') ||
            (s[i] == '-'))
        {
            return 1;
        }
    }
    return 0;
}

/*
validSymbol(char* s)
helper function to check for malformatted symbols
multi-char symbol can ONLY contains | ! | $ | % | & | * | / | : | < | = | > | ? | ~ | _ | ^|LETTER|NUMBER
single-char symbols cannot be a number

<identifier> ->  <initial> <subsequent>* | + | -
<initial>    ->  <letter> | ! | $ | % | & | * | / | : | < | = | > | ? | ~ | _ | ^
<subsequent> ->  <initial> | <digit> | . | + | -
<letter>     ->  a | b | ... | z | A | B | ... | Z
<digit>      ->  0 | 1 | ... | 9
*/
int validSymbol(char *s)
{
    // check that initial is of a valid character
    if (strlen(s) > 1)
    {
        if (validInitialCharacter(s[0]) && validSubsequentCharacters(s))
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
    else
    {
        if (validInitialCharacter(s[0]))
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
}

/*
validNumber()
<number>   ->  <sign> <ureal> | <ureal>
<sign>     ->  + | -
<ureal>    ->  <uinteger> | <udecimal>
<uinteger> ->  <digit>+
<udecimal> ->  . <digit>+ | <digit>+ . <digit>*
<digit>    ->  0 | 1 | ... | 9
*/
int validNumber(char *s)
{
    if (s[0] == '+' || s[0] == '-' || isdigit(s[0]))
    {
        if ((s[0] == '+' || s[0] == '-') && (strlen(s) == 1))
        {
            return 0;
        }
        int decimal_point_count = 0;

        for (int i = 1; i < strlen(s); i++)
        {
            // if char is not "." or isn't a digit
            if (s[i] != '.' && !isdigit(s[i]))
            {
                return 0;
            }
            if (s[i] == '.')
            {
                decimal_point_count = decimal_point_count + 1;
            }
            if (decimal_point_count > 1)
            {
                return 0;
            }
        }

        if (decimal_point_count == 1)
        {
            return 2;
        }
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
    char temp_symbol[300] = {'\0'};
    // Start tokenizing!
    while (next_char != EOF)
    {
        // make a new Value token
        Value *new_token = talloc(sizeof(Value));

        // reserver space for a new cons_cell (node)
        Value *new_cons_cell = talloc(sizeof(Value));
        new_cons_cell->type = CONS_TYPE;

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
                // check if valid number (see grammar up top)
                if (validNumber(temp_symbol) == 1)
                {
                    new_token->type = INT_TYPE;
                    new_token->i = strtol(temp_symbol, NULL, 10);
                    new_cons_cell = cons(new_token, tokens_list);
                    tokens_list = new_cons_cell;
                    memset(temp_symbol, '\0', strlen(temp_symbol));
                }
                else if (validNumber(temp_symbol) == 2)
                {
                    new_token->type = DOUBLE_TYPE;
                    new_token->d = strtod(temp_symbol, NULL);
                    new_cons_cell = cons(new_token, tokens_list);
                    tokens_list = new_cons_cell;
                    memset(temp_symbol, '\0', strlen(temp_symbol));
                }
                else if (validSymbol(temp_symbol))
                {
                    new_token->type = SYMBOL_TYPE;

                    // store temp_symbol
                    char *stored_symbol = talloc(strlen(temp_symbol) * sizeof(char));
                    strcpy(stored_symbol, temp_symbol);
                    new_token->s = stored_symbol;

                    new_cons_cell = cons(new_token, tokens_list);
                    tokens_list = new_cons_cell;

                    memset(temp_symbol, '\0', strlen(temp_symbol));
                }
                else
                {

                    printf("TokenizeError( '(' ): symbol contains a non allowed character\n");
                    texit(1);
                }
                // special case
                Value *null_token = talloc(sizeof(Value));
                null_token->type = CLOSE_TYPE;
                new_cons_cell = cons(null_token, tokens_list);
                tokens_list = new_cons_cell;
            }
            else
            {
                new_token->type = CLOSE_TYPE;

                new_cons_cell = cons(new_token, tokens_list);
                tokens_list = new_cons_cell;
            }
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
            while (next_char == '\n' || next_char == ' ')
            {
                next_char = (char)fgetc(stdin);
            }
            temp_symbol[strlen(temp_symbol)] = next_char;
        }
        // check for string (special else if (next_char ==since double quotes are not to be used as a symbol)
        else if (next_char == '"')
        {
            // if it's a malformed string (mismatched double quotes), throw an error

            // need to set to the next character right away else the check for terminating double quotes won't work
            next_char = (char)fgetc(stdin);
            while (next_char != EOF)
            {
                // well formed string, make string literal
                if (next_char == '"')
                {
                    // check for an edge case where there's a string in format ("hello"world)
                    char temporary = (char)fgetc(stdin);
                    if (temporary == ' ')
                    {
                        break;
                    }
                    else
                    {

                        printf("TokenizeError: malformatted string literals, double quotes not supported\n");
                        texit(1);
                    }
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

                printf("TokenizeError: malformatted string literals\n");
                texit(1);
            }
            else
            {
                // store temp symbol
                char *stored_symbol = talloc(strlen(temp_symbol) * sizeof(char));
                strcpy(stored_symbol, temp_symbol);
                new_token->s = stored_symbol;
                new_token->type = STR_TYPE;
                new_cons_cell = cons(new_token, tokens_list);
                tokens_list = new_cons_cell;

                memset(temp_symbol, '\0', strlen(temp_symbol));
            }
        }
        // check for empty space (used as delimiter), if hit, just restart the temporary symbol
        else if (next_char == ' ' && (strlen(temp_symbol) > 0))
        {
            // check if valid number (see grammar up top)
            if (validNumber(temp_symbol) == 1)
            {
                new_token->type = INT_TYPE;
                new_token->i = strtol(temp_symbol, NULL, 10);
                new_cons_cell = cons(new_token, tokens_list);
                tokens_list = new_cons_cell;
                memset(temp_symbol, '\0', strlen(temp_symbol));
            }
            else if (validNumber(temp_symbol) == 2)
            {
                new_token->type = DOUBLE_TYPE;
                new_token->d = strtod(temp_symbol, NULL);
                new_cons_cell = cons(new_token, tokens_list);
                tokens_list = new_cons_cell;
                memset(temp_symbol, '\0', strlen(temp_symbol));
            }
            else // check valid symbol (cannot contains | ! | $ | % | & | * | / | : | < | = | > | ? | ~ | _ | ^)
                if (validSymbol(temp_symbol))
                {
                    // copy over the symbol only if the symbol is not empty
                    if (strlen(temp_symbol) > 0)
                    {
                        new_token->type = SYMBOL_TYPE;

                        // store temp_symbole
                        char *stored_symbol = talloc(strlen(temp_symbol) * sizeof(char));
                        strcpy(stored_symbol, temp_symbol);
                        new_token->s = stored_symbol;
                        new_cons_cell = cons(new_token, tokens_list);
                        tokens_list = new_cons_cell;
                        memset(temp_symbol, '\0', strlen(temp_symbol));
                    }
                }
                else
                {

                    printf("TokenizeError ('[empty]'): symbol contains a non allowed character\n");
                    texit(1);
                }
        }
        else if (next_char == '#')
        {
            while (next_char != ' ' && next_char != EOF && next_char != ')')
            {
                temp_symbol[strlen(temp_symbol)] = next_char;
                if (strlen(temp_symbol) > 2)
                {

                    printf("Syntax error (readBoolean): boolean was not #t or #f\n");
                    texit(1);
                }
                next_char = (char)fgetc(stdin);
            }
            if (temp_symbol[1] == 't' || temp_symbol[1] == 'T')
            {
                new_token->type = BOOL_TYPE;
                new_token->i = 1;
                new_cons_cell = cons(new_token, tokens_list);
                tokens_list = new_cons_cell;
                memset(temp_symbol, '\0', strlen(temp_symbol));
            }
            else if (temp_symbol[1] == 'f' || temp_symbol[1] == 'F')
            {
                new_token->type = BOOL_TYPE;
                new_token->i = 0;
                new_cons_cell = cons(new_token, tokens_list);
                tokens_list = new_cons_cell;
                memset(temp_symbol, '\0', strlen(temp_symbol));
            }
            else
            {

                printf("Syntax error (readBoolean): boolean was not #t or #f\n");
                texit(1);
            }
        }
        // by default, concatenate ALL char into a long string, concatenation stops upon first encounter wtih a whitespace character
        else
        {
            if (next_char != ' ')
            {
                temp_symbol[strlen(temp_symbol)] = next_char;
            }
        }
        next_char = (char)fgetc(stdin);
    }
    if (strlen(temp_symbol) > 0)
    {
        Value *new_token = talloc(sizeof(Value));
        Value *new_cons_cell = talloc(sizeof(Value));

        // check if valid number (see grammar up top)
        if (validNumber(temp_symbol) == 1)
        {
            new_token->type = INT_TYPE;
            new_token->i = strtol(temp_symbol, NULL, 10);
            new_cons_cell = cons(new_token, tokens_list);
            tokens_list = new_cons_cell;
        }
        else if (validNumber(temp_symbol) == 2)
        {
            new_token->type = DOUBLE_TYPE;
            new_token->d = strtod(temp_symbol, NULL);
            new_cons_cell = cons(new_token, tokens_list);
            tokens_list = new_cons_cell;
        }
        else if (validSymbol(temp_symbol))
        {

            // copy over the symbol only if the symbol is not empty
            if (strlen(temp_symbol) > 0)
            {
                new_token->type = SYMBOL_TYPE;
                char *stored_symbol = talloc(sizeof(char) * strlen(temp_symbol));
                strcpy(stored_symbol, temp_symbol);
                new_token->s = temp_symbol;
                new_cons_cell = cons(new_token, tokens_list);
                tokens_list = new_cons_cell;
            }
        }
        else
        {

            printf("Syntax error: %s symbol not supported\n", temp_symbol);
            texit(1);
        }
    }

    // Reverse the tokens list, to put it back in order
    Value *reversed_list = reverse(tokens_list);

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
        case BOOL_TYPE:
            if (car(current)->i == 1)
            {
                printf("#t:boolean\n");
            }
            else if (car(current)->i == 0)
            {
                printf("#f:boolean\n");
            }
            else
            {
                printf("Syntax error (readBoolean): boolean was not #t or #f\n");
                texit(1);
            }
            break;
        case INT_TYPE:
            printf("%i:integer\n", car(current)->i);
            break;
        case DOUBLE_TYPE:
            printf("%f:double\n", car(current)->d);
            break;
        default:
            printf("not yet implemented\n");
        }
        current = cdr(current);
    }
}
