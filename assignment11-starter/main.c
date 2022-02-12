// Tester for linked list.

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "linkedlist.h"
#include "value.h"
#include "talloc.h"

void testForward(Value *head, int correctLength)
{
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

void testBackward(Value *head, int correctLength)
{
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

int main()
{

  // 1. Create a null value (representing an empty list)
  printf("Test 1...\n");
  Value *head = makeNull();
  int correctLength = 0;
  assert(0 == length(head));
  assert(isNull(head));
  printf("\tPASSED\n\n");

  // 2. Reverse the empty list
  printf("Test 2...\n");
  Value *reverseEmpty = reverse(head);
  assert(0 == length(reverseEmpty));
  assert(isNull(reverseEmpty));
  printf("\tPASSED\n\n");

  // 3. Cons a new cell at the head of the list: ( 7 )
  printf("Test 3...\n");
  Value *val1 = talloc(sizeof(Value));
  val1->type = INT_TYPE;
  val1->i = 7;
  head = cons(val1, head);
  correctLength++;
  printf("\t\t");
  display(head);
  printf("\tPASSED\n\n");

  // 4. Cons a new cell at the front of the existing list: ( 6.00 7 )
  printf("Test 4...\n");
  Value *val2 = talloc(sizeof(Value));
  val2->type = DOUBLE_TYPE;
  val2->d = 6.00;
  head = cons(val2, head);
  correctLength++;
  printf("\t\t");
  display(head);
  printf("\tPASSED\n\n");

  // 5. Cons a new cell at the front of the existing list: ( "5.0s" 6.00 7 )
  printf("Test 5...\n");
  Value *val3 = talloc(sizeof(Value));
  val3->type = STR_TYPE;
  char *text = "5.0s";
  val3->s = talloc(sizeof(char) * (strlen(text) + 1));
  strcpy(val3->s, text);
  head = cons(val3, head);
  correctLength++;
  printf("\t\t");
  display(head);
  printf("\tPASSED\n\n");

  // 6. Cons a new cell at the front of the existing list: ( 4.00000 "5.0s" 6.00 7 )
  printf("Test 6...\n");
  Value *val4 = talloc(sizeof(Value));
  val4->type = DOUBLE_TYPE;
  val4->d = 4.00000;
  head = cons(val4, head);
  correctLength++;
  printf("\t\t");
  display(head);
  printf("\tPASSED\n\n");

  // 7. Cons a new cell at the front of the existing list: ( "3.0s" 4.00000 "5.0s" 6.00 7 )
  printf("Test 7...\n");
  Value *val5 = talloc(sizeof(Value));
  val5->type = STR_TYPE;
  text = "3.0s";
  val5->s = talloc(sizeof(char) * (strlen(text) + 1));
  strcpy(val5->s, text);
  head = cons(val5, head);
  correctLength++;
  printf("\t\t");
  display(head);
  printf("\tPASSED\n\n");

  // 8. Cons a new cell at the front of the existing list: ( "2.0s" "3.0s" 4.00000 "5.0s" 6.00 7 )
  printf("Test 8...\n");
  Value *val6 = talloc(sizeof(Value));
  val6->type = STR_TYPE;
  text = "2.0s";
  val6->s = talloc(sizeof(char) * (strlen(text) + 1));
  strcpy(val6->s, text);
  head = cons(val6, head);
  correctLength++;
  printf("\t\t");
  display(head);
  printf("\tPASSED\n\n");

  // 9. Cons a new cell at the front of the existing list: ( 1.0 "2.0s" "3.0s" 4.00000 "5.0s" 6.00 7 )
  printf("Test 9...\n");
  Value *val7 = talloc(sizeof(Value));
  val7->type = DOUBLE_TYPE;
  val7->d = 1.0;
  head = cons(val7, head);
  correctLength++;
  printf("\t\t");
  display(head);
  printf("\tPASSED\n\n");

  // 10. Make sure everything is in the correct order
  printf("Test 10...\n");
  testForward(head, correctLength);
  printf("\tPASSED\n\n");

  // 11. Reverse the list and display the result: ( 7 6.00 "5.0s" 4.00000 "3.0s" "2.0s" 1.0 )
  printf("Test 11...\n");
  Value *rev = reverse(head);
  printf("\t\t");
  display(rev);
  printf("\tPASSED\n\n");

  // 12. Make sure the reversed list is in the correct order
  printf("Test 12...\n");
  testBackward(rev, correctLength);
  printf("\tPASSED\n\n");

  // 13. Verify that neither of the lists share identical cons cells
  printf("Test 13...\n");
  Value *headcur = head;
  while (headcur->type != NULL_TYPE)
  {
    Value *revcur = rev;
    while (revcur->type != NULL_TYPE)
    {
      assert(headcur != revcur);
      revcur = revcur->c.cdr;
    }
    headcur = headcur->c.cdr;
  }
  printf("\tPASSED\n\n");

  // 14. Test tfree
  printf("Test 14...\n");
  tfree();
  printf("\tPASSED\n\n");

  // 15. Test texit (this should cause the program to smoothly terminate)
  printf("Test 15...\n");
  printf("\tIf no errors follow this line... PASSED\n\n");
  Value *justOneByte = talloc(1);
  texit(0);
}
