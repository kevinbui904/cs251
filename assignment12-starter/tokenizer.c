/*
tokenizer2.c
Written by Victor Huang and Thien K. M. Bui
Last updated 02-18-2022
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

/*isString()a
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

/*
notDelimiter()
return 1 if char is not ' ', ')', '\n', '\r', ';', EOF,
0 otherwise
*/
int notDelimiter(char c)
{
    // if (next_char != ' ' && next_char != ')' && next_char != '\n' && next_char != ';' && next_char != EOF)
    switch (c)
    {
    case ' ':
        return 0;
        break;
    case ')':
        return 0;
        break;
    case '\n':
        return 0;
    case '\r':
        return 0;
    case ';':
        return 0;
    case EOF:
        return 0;
    default:
        return 1;
    }
}

Value *tokenize()
{

    // Prepare list of tokens
    Value *tokens_list = makeNull();

    // Prepare the character stream
    char next_char;
    next_char = (char)fgetc(stdin);

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
            next_char = (char)fgetc(stdin);
        }
        // need to account for end condition in if () there no space before last )
        else if (next_char == ')')
        {
            new_token->type = CLOSE_TYPE;

            new_cons_cell = cons(new_token, tokens_list);
            tokens_list = new_cons_cell;
            next_char = (char)fgetc(stdin);
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
            while (next_char == '\n')
            {
                next_char = (char)fgetc(stdin);
            }
        }
        else if (next_char == ' ')
        {
            while (next_char == ' ')
            {
                next_char = (char)fgetc(stdin);
            }
        }
        else
        {
            // handle boolean
            if (next_char == '#')
            {
                char temp_boolean[300] = {'\0'};
                while (notDelimiter(next_char))
                {
                    // check with james, how to handle this case (building out the temp string)
                    temp_boolean[strlen(temp_boolean)] = next_char;
                    if (strlen(temp_boolean) > 2)
                    {

                        printf("Syntax error (readBoolean): boolean was not #t or #f\n");
                        texit(1);
                    }
                    next_char = (char)fgetc(stdin);
                }
                if (temp_boolean[1] == 't' || temp_boolean[1] == 'T')
                {
                    new_token->type = BOOL_TYPE;
                    new_token->i = 1;
                    new_cons_cell = cons(new_token, tokens_list);
                    tokens_list = new_cons_cell;
                }
                else if (temp_boolean[1] == 'f' || temp_boolean[1] == 'F')
                {
                    new_token->type = BOOL_TYPE;
                    new_token->i = 0;
                    new_cons_cell = cons(new_token, tokens_list);
                    tokens_list = new_cons_cell;
                }
                else
                {
                    printf("Syntax error (readBoolean): boolean ==%s== was not #t or #f\n", temp_boolean);
                    texit(1);
                }
            }
            // handle strings
            else if (next_char == '\"')
            {
                char temp_string[300] = {'\0'};
                next_char = (char)fgetc(stdin);
                while (next_char != EOF)
                {
                    // well formed string, make string literal
                    if (next_char == '\"')
                    {
                        // check for an edge case where there's a string in format ("hello"world)
                        next_char = (char)fgetc(stdin);

                        if (next_char == ' ' || next_char == ')')
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
                        temp_string[strlen(temp_string)] = next_char;

                        next_char = (char)fgetc(stdin);
                    }
                }
                // if string is well formed
                new_token->type = STR_TYPE;
                char *stored_string = talloc(sizeof(char) * strlen(temp_string) + 1);
                strcpy(stored_string, temp_string);
                new_token->s = stored_string;
                new_cons_cell = cons(new_token, tokens_list);
                tokens_list = new_cons_cell;
            }
            // handle symbols
            else
            {
                // build out a new symbol
                char temp_symbol[300] = {'\0'};
                while (notDelimiter(next_char))
                {
                    temp_symbol[strlen(temp_symbol)] = next_char;
                    next_char = (char)fgetc(stdin);
                }

                if (validNumber(temp_symbol) == 1)
                {
                    new_token->type = INT_TYPE;
                    new_token->i = strtol(temp_symbol, NULL, 10);
                    new_cons_cell = cons(new_token, tokens_list);
                    tokens_list = new_cons_cell;
                }
                // case for double
                else if (validNumber(temp_symbol) == 2)
                {
                    new_token->type = DOUBLE_TYPE;
                    new_token->d = strtod(temp_symbol, NULL);
                    new_cons_cell = cons(new_token, tokens_list);
                    tokens_list = new_cons_cell;
                }
                else // check valid symbol (cannot contains | ! | $ | % | & | * | / | : | < | = | > | ? | ~ | _ | ^)
                {
                    if (validSymbol(temp_symbol))
                    {
                        // copy over the symbol only if the symbol is not empty
                        if (strlen(temp_symbol) > 0)
                        {
                            new_token->type = SYMBOL_TYPE;
                            // store temp_symbole
                            char *stored_symbol = talloc(strlen(temp_symbol) * sizeof(char) + 1);
                            strcpy(stored_symbol, temp_symbol);
                            new_token->s = stored_symbol;
                            new_cons_cell = cons(new_token, tokens_list);
                            tokens_list = new_cons_cell;
                        }
                    }
                    else
                    {
                        printf("Syntax error (readSymbol): symbol %s does not start with an allowed first character.\n", temp_symbol);
                        texit(1);
                    }
                }
            }
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
