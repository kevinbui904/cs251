/*
linkedlist.c
Written by Victor Huang and Thien K. M. Bui
Last modified 02/09/22
*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "linkedlist.h"

// Create a pointer to a new NULL_TYPE Value (hint: where in memory will
// the Value have to live?)
Value *makeNull()
{
    Value *new_null = malloc(sizeof(Value));
    new_null->type = NULL_TYPE;

    return new_null;
}

// Return whether the given pointer points at a NULL_TYPE Value. Use assertions
// to make sure that this is a legitimate operation. See the assignment
// instructions for further explanation on assertions.
bool isNull(Value *value)
{
    if (value->type == NULL_TYPE)
    {
        return true;
    }
    return false;
}

// Create a pointer to a new CONS_TYPE Value
Value *cons(Value *newCar, Value *newCdr)
{
    Value *new_value = malloc(sizeof(Value));
    new_value->type = CONS_TYPE;

    struct ConsCell new_cons_cell;
    new_cons_cell.car = newCar;
    new_cons_cell.cdr = newCdr;

    new_value->c = new_cons_cell;
    return new_value;
}

// Return a pointer to the car value for the cons cell at the head of the given
// linked list. Use assertions here to make sure that this is a legitimate operation
// (e.g., there is no car value at the head of an empty list). See the assignment
// instructions for further explanation.
Value *car(Value *list)
{
    // if not empty
    if (list->type == CONS_TYPE)
    {
        return list->c.car;
    }
    else if (list->type == NULL_TYPE)
    {
        return list;
    }
    // error, should never be of type int/null here
    else
    {
        assert(false != true && "Incorrect type, something went wrong --kb");
        return list;
    }
}

// Return a pointer to the cdr value for the cons cell at the head of the given linked
// list. Again use assertions to make sure that this is a legitimate operation.
Value *cdr(Value *list)
{
    // if not empty
    if (list->type == CONS_TYPE)
    {
        return list->c.cdr;
    }
    else
    {
        assert(false != true && "invalid operation on empty list --kb");
        return list;
    }
}

// Display the contents of the linked list to the screen in the
// format of a Scheme list -- e.g., ( 33 "lol" 9.9 ). It's okay
// to just use printf here, though you'll have to add the quotes in
// yourself, for strings.
void display(Value *list)
{
    bool at_end = false;
    Value *current_value = list;

    printf("( ");
    while (!at_end)
    {

        if (current_value->type == CONS_TYPE)
        {
            // copy over whatever addresses are in the current ConsCell, it'll get deleted anyway so it doesn't matter
            struct ConsCell printed_value = current_value->c;
            // check the type of the car cell (Value typed pointer)
            switch (printed_value.car->type)
            {
            case INT_TYPE:
                printf("%i ", printed_value.car->i);
                break;
            case DOUBLE_TYPE:
                printf("%f ", printed_value.car->d);
                break;
            case STR_TYPE:
                printf("\"%s\" ", printed_value.car->s);
                break;
            default:
                printf("%i", printed_value.car->i);
            }

            current_value = cdr(current_value);
        }
        else
        {
            printf(")\n");
            at_end = true;
        }
    }
}

// Return a new list that is the reverse of the one that is passed in. All
// content within the list should be duplicated; there should be no shared
// memory whatsoever between the original list and the new one. Use your
// cons(), car(), and cdr() functions from above -- but be sure that you
// don't end up pointing to memory used by the old list! Hint: this means
// that you'll need to make copies of the Value structs that serve as car
// values for the cons cells in the original list; more specifically, you'll
// want to malloc new space for them on the heap. In the case of a string,
// the strlen() function will come in handy, in addition to strcpy(); note
// that strlen() will not include the null terminator in its count. To use
// these functions, you'll need to include <string.h> above.

// FAQ: What if there are nested lists inside that list?

// ANS: There won't be for this assignment. There will be later, but that will
// be after we've set up an easier way of managing memory.
Value *reverse(Value *list)
{
    // copy over the current values into heap
    Value *head = list;
    Value *new_head = makeNull();

    // at the last node of the list
    while (!isNull(head))
    {

        Value *copy = malloc(sizeof(Value));
        switch (car(head)->type)
        {

        case INT_TYPE:
            copy->type = INT_TYPE;
            copy->i = car(head)->i;
            break;

        case DOUBLE_TYPE:
            copy->type = DOUBLE_TYPE;
            copy->d = car(head)->d;
            break;

        case STR_TYPE:
            copy->type = STR_TYPE;
            copy->s = malloc(sizeof(char) * (strlen(car(head)->s) + 1));
            strcpy(copy->s, car(head)->s);
            break;
        default:
            break;
        }

        Value *temporary = new_head;
        new_head = cons(copy, temporary);
        head = cdr(head);
    }
    return new_head;
}

// Return the length of the given list, i.e., the number of cons cells.
// Use assertions to make sure that this is a legitimate operation.
int length(Value *value)
{

    int length = 0;
    Value *current = value;
    while (!isNull(current))
    {
        length = length + 1;
        current = cdr(current);
    }
    return length;
}

// Free up all memory directly or indirectly referred to by list. This includes
// strings, because in the Value defintion these are pointers to character arrays.

// FAQ: What if a string being pointed to is a string literal? That throws an
// error when freeing.

// ANS: Don't put a string literal into the list in the first place. All strings
// added to this list should be able to be free'd by the cleanup function.

// FAQ: What if there are nested lists inside that list?

// ANS: There won't be for this assignment. There will be later, but that will
// be after we've set up an easier way of managing memory.
void cleanup(Value *list)
{
    switch (list->type)
    {
    case INT_TYPE:
        free(list);
        break;
    case DOUBLE_TYPE:
        free(list);
        break;
    case STR_TYPE:
        free(list->s);
        free(list);
        break;
    case NULL_TYPE:
        free(list);
        break;
    case CONS_TYPE:
        cleanup(car(list));
        cleanup(cdr(list));
        free(list);
        break;
    }
}