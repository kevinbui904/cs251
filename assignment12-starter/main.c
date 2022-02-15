#include <stdio.h>
#include "tokenizer.h"
#include "value.h"
#include "linkedlist.h"
#include "talloc.h"

int main() {
    Value *tokensList = tokenize();
    displayTokens(tokensList);
    tfree();
}
