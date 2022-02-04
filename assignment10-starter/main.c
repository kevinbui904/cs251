// Tester for linked list.

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "linkedlist.h"
#include "value.h"


// This is a helper function used by main(), which includes
// the actual test cases. Jump down to main() to view those,
// and ignore this function unless it appears to be causing
// tests to fail, in which case you can inspect it further.
void testForward(Value *head, int correctLength) {

  Value *value = head;
  assert(CONS_TYPE == value->type);
  assert(DOUBLE_TYPE == car(value)->type);
  assert(1 == car(value)->d);

  value = cdr(value);
  assert(CONS_TYPE == value->type);
  assert(STR_TYPE == car(value)->type);
  assert(!strcmp("2.0s", car(value)->s));

  value = cdr(value);
  assert(CONS_TYPE == value->type);
  assert(STR_TYPE == car(value)->type);
  assert(!strcmp("3.0s", car(value)->s));

  value = cdr(value);
  assert(CONS_TYPE == value->type);
  assert(DOUBLE_TYPE == car(value)->type);
  assert(4 == car(value)->d);

  value = cdr(value);
  assert(CONS_TYPE == value->type);
  assert(STR_TYPE == car(value)->type);
  assert(!strcmp("5.0s", car(value)->s));

  value = cdr(value);
  assert(CONS_TYPE == value->type);
  assert(DOUBLE_TYPE == car(value)->type);
  assert(6 == car(value)->d);

  value = cdr(value);
  assert(CONS_TYPE == value->type);
  assert(INT_TYPE == car(value)->type);
  assert(7 == car(value)->i);

  value = cdr(value);
  assert(NULL_TYPE == value->type);

  assert(correctLength == length(head));
  assert(!isNull(head));
}


// This is a helper function used by main(), which includes
// the actual test cases. Jump down to main() to view those,
// and ignore this function unless it appears to be causing
// tests to fail, in which case you can inspect it further.
void testBackward(Value *head, int correctLength) {
  Value *value = head;

  assert(CONS_TYPE == value->type);
  assert(INT_TYPE == car(value)->type);
  assert(7 == car(value)->i);

  value = cdr(value);
  assert(CONS_TYPE == value->type);
  assert(DOUBLE_TYPE == car(value)->type);
  assert(6 == car(value)->d);

  value = cdr(value);
  assert(CONS_TYPE == value->type);
  assert(STR_TYPE == car(value)->type);
  assert(!strcmp("5.0s", car(value)->s));

  value = cdr(value);
  assert(CONS_TYPE == value->type);
  assert(DOUBLE_TYPE == car(value)->type);
  assert(4 == car(value)->d);

  value = cdr(value);
  assert(CONS_TYPE == value->type);
  assert(STR_TYPE == car(value)->type);
  assert(!strcmp("3.0s", car(value)->s));

  value = cdr(value);
  assert(CONS_TYPE == value->type);
  assert(STR_TYPE == car(value)->type);
  assert(!strcmp("2.0s", car(value)->s));

  value = cdr(value);
  assert(CONS_TYPE == value->type);
  assert(DOUBLE_TYPE == car(value)->type);
  assert(1 == car(value)->d);

  value = cdr(value);
  assert(NULL_TYPE == value->type);

  assert(correctLength == length(head));
  assert(!isNull(head));
}


// This contains the actual test cases, which the comments delineate.
int main() { 

  // 1. Create a null value (representing an empty list)
  printf("Test 1...\n");
  Value *head = makeNull();
  int correctLength = 0;
  assert(length(head) == correctLength);
  printf("\tPASSED\n\n");

  // 2. Reverse the empty list: ( )
  printf("Test 2...\n");
  Value *reverseLengthZero = reverse(head);
  assert(length(reverseLengthZero) == correctLength);
  cleanup(reverseLengthZero);
  printf("\tPASSED\n\n");

  // 3.1 Cons a new cell at the head of the list: ( 7 )
  printf("Test 3.1...\n");
  Value *val1 = malloc(sizeof(Value));  // This will have to be freed eventually!
  val1->type = INT_TYPE;
  val1->i = 7;
  head = cons(val1, head);
  correctLength++;
  assert(length(head) == correctLength);
  printf("\tPASSED\n\n");

  // 3.2. Display the list of one element: ( 7 )
  printf("Test 3.2....\n");
  printf("\t\t");
  display(head);
  printf("\tPASSED\n\n");

  // 4.1 Reverse this list of one element: ( 7 )
  printf("Test 4.1...\n");
  Value *reverseLengthOne = reverse(head);
  assert(length(reverseLengthOne) == correctLength);
  printf("\tPASSED\n\n");

  // 4.2. Display the reversed list of one element: ( 7 )
  printf("Test 4.2...\n");
  printf("\t\t");
  display(reverseLengthOne);
  printf("\tPASSED\n\n");

  // 4.3. Call cleanup() on the reversed list
  printf("Test 4.3...\n");
  cleanup(reverseLengthOne);
  printf("\tPASSED\n\n");

  // 5. Cons a new cell at the front of the existing list: ( 6.00 7 )
  printf("Test 5...\n");
  Value *val2 = malloc(sizeof(Value));  // This will have to be freed eventually!
  val2->type = DOUBLE_TYPE;
  val2->d = 6.00;
  head = cons(val2, head);
  correctLength++;
  assert(length(head) == correctLength);
  printf("\t\t");
  display(head);
  printf("\tPASSED\n\n");

  // 6. Cons a new cell at the front of the list: ( "5.0s" 6.00 7 )
  printf("Test 6...\n");
  Value *val3 = malloc(sizeof(Value));  // This will have to be freed eventually!
  val3->type = STR_TYPE;
  char *text = "5.0s";
  val3->s = malloc(sizeof(char)*(strlen(text) + 1));  // This will have to be freed eventually!
  strcpy(val3->s,text);
  head = cons(val3,head);
  correctLength++;
  assert(length(head) == correctLength);
  printf("\t\t");
  display(head);
  printf("\tPASSED\n\n");

  // 7. Cons a new cell at the front of the list: ( 4.00000 "5.0s" 6.00 7 )
  printf("Test 7...\n");
  Value *val4 = malloc(sizeof(Value));  // This will have to be freed eventually!
  val4->type = DOUBLE_TYPE;
  val4->d = 4.00000;
  head = cons(val4,head);
  correctLength++;
  assert(length(head) == correctLength);
  printf("\t\t");
  display(head);
  printf("\tPASSED\n\n");

  // 8. Cons a new cell at the front of the list: ( "3.0s" 4.00000 "5.0s" 6.00 7 )
  printf("Test 8...\n");
  Value *val5 = malloc(sizeof(Value));  // This will have to be freed eventually!
  val5->type = STR_TYPE;
  text = "3.0s";
  val5->s = malloc(sizeof(char)*(strlen(text) + 1));  // This will have to be freed eventually!
  strcpy(val5->s,text);
  head = cons(val5,head);
  correctLength++;
  assert(length(head) == correctLength);
  printf("\t\t");
  display(head);
  printf("\tPASSED\n\n");
  
  // 9. Cons a new cell at the front of the list: ( "2.0s" "3.0s" 4.00000 "5.0s" 6.00 7 )
  printf("Test 9...\n");
  Value *val6 = malloc(sizeof(Value));  // This will have to be freed eventually!
  val6->type = STR_TYPE;
  text = "2.0s";
  val6->s = malloc(sizeof(char)*(strlen(text) + 1));  // This will have to be freed eventually!
  strcpy(val6->s,text);
  head = cons(val6,head);
  correctLength++;
  assert(length(head) == correctLength);
  printf("\t\t");
  display(head);
  printf("\tPASSED\n\n");

  // 10. Cons a new cell at the front of the list: ( 1.0 "2.0s" "3.0s" 4.00000 "5.0s" 6.00 7 )
  printf("Test 10...\n");
  Value *val7 = malloc(sizeof(Value));  // This will have to be freed eventually!
  val7->type = DOUBLE_TYPE;
  val7->d = 1.0;
  head = cons(val7,head);
  correctLength++;
  assert(length(head) == correctLength);
  printf("\t\t");
  display(head);
  printf("\tPASSED\n\n");

  // 11. Display the contents of the list: ( 1.0 "2.0s" "3.0s" 4.00000 "5.0s" 6.00 7 )
  printf("Test 11...\n");
  printf("\t\t");
  display(head);
  printf("\tPASSED\n\n");

  // 12. Confirm that everything is in the expected order
  printf("Test 12...\n");
  testForward(head, correctLength);
  printf("\tPASSED\n\n");

  // 13. Reverse the entire list and display the result: ( 7 6.00 "5.0s" 4.00000 "3.0s" "2.0s" 1.0 )
  printf("Test 13...\n");
  Value *rev = reverse(head);
  printf("\t\t");
  display(rev);
  printf("\tPASSED\n\n");

  // 14. Work through the reversed list to ensure it is in the expected order
  printf("Test 14...\n");
  testBackward(rev, correctLength);
  printf("\tPASSED\n\n");

  // 15. Free all the memory
  printf("Test 15...\n");
  cleanup(head);
  cleanup(rev);
  printf("\tPASSED\n\n");

  head = NULL;
  rev = NULL;
}
