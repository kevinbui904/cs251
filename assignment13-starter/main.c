#include <stdio.h>
#include "tokenizer.h"
#include "value.h"
#include "linkedlist.h"
#include "parser.h"
#include "talloc.h"

int main()
{
    Value *tokensList = tokenize();
    Value *parseTree = parse(tokensList);

    printTree(parseTree);
    printf("\n");

    tfree();
    return 0;
}
