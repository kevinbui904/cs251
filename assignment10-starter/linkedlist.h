#include <stdbool.h>
#include "value.h"

#ifndef _LINKEDLIST_H
#define _LINKEDLIST_H


// Create a pointer to a new NULL_TYPE Value (hint: where in memory will 
// the value have to live?)
Value *makeNull();

// Return whether the given pointer points at a NULL_TYPE Value. Use assertions 
// to make sure that this is a legitimate operation. See the assignment
// instructions for further explanation on assertions.
bool isNull(Value *value);

// Create a pointer to a new CONS_TYPE Value
Value *cons(Value *newCar, Value *newCdr);

// Return a pointer to the car value for the cons cell at the head of the given 
// linked list. Use assertions here to make sure that this is a legitimate operation 
// (e.g., there is no car value at the head of an empty list). See the assignment 
// instructions for further explanation.
Value *car(Value *list);

// Return a pointer to the cdr value for the cons cell at the head of the given linked
// list. Again use assertions to make sure that this is a legitimate operation.
Value *cdr(Value *list);

// Display the contents of the linked list to the screen in the
// format of a Scheme list -- e.g., ( 33 "lol" 9.9 ). It's okay
// to just use printf here, though you'll have to add the quotes in
// yourself, for strings.
void display(Value *list);

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
Value *reverse(Value *list);

// Return the length of the given list, i.e., the number of cons cells. 
// Use assertions to make sure that this is a legitimate operation.
int length(Value *value);

// Free up all memory directly or indirectly referred to by list. This includes 
// strings, because in the Value defintion these are pointers to character arrays.

// FAQ: What if a string being pointed to is a string literal? That throws an
// error when freeing.

// ANS: Don't put a string literal into the list in the first place. All strings
// added to this list should be able to be free'd by the cleanup function.

// FAQ: What if there are nested lists inside that list?

// ANS: There won't be for this assignment. There will be later, but that will
// be after we've set up an easier way of managing memory.
void cleanup(Value *list);


#endif
