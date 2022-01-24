// PRogram demonstrating how to use printf

#include <stdio.h>

int main() {
    char c = 'a';
    int i = 5;
    long l = ( 1 << 16);
    float f = 42.67;
    double d = 109.2;
    char *s = "hello";
    int *p = &i; 

    int subtracted = 15 - 87;

    printf("Here is an int %i and a char %c and a long %li\n", i, c, l);
    printf("and a float %f and a double %f\n", f, d);
    printf("and a string %s and a pointer %p\n", s, p);

    printf("this is 15 minus 87, %i\n", subtracted);
    return 0;
}