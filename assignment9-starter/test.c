#include <stdio.h>
#include <stdlib.h>

int main()
{
    int *test1 = malloc(sizeof(int));
    test1[0] = 3;
    int *test2;
    // test2 = test1;
    *test2 = *test1;
    *test2 = 4;
    printf("%i\n", test1[0]);
    printf("%i\n", *test2);
}