/* pointers.c 
Written by Thien K. M. Bui
Last modified 01/26/22
*/

#include <stdio.h>

int main() {
    int a = 5;
    int b = 6;

    int *p = &a;
    int *q = &b;

    int **pp = &p;

    *q += *p;
    (**pp)++;

    q = p;
    *pp = &b;
    *p += 3;
    *q *= 2;

    printf("Final values of a and b: %i, %i\n", a, b);

    //b higher than a
    if(p > q){
        printf("higher\n");
        
    }else{
        printf("lower\n");
    }
}