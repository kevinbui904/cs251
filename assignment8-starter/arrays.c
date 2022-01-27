/* arrays.c
Written by Thien K. M. Bui
Last modified 01/26/22
*/

#include <stdio.h>

int main() {
    int x = 0;
    int array[10];
    int i;

    for(i = 0; i < 10; i++){
        array[i] = i;
    }

    for(i = 0; i < 10; i++){
        printf("%i ", array[i]);
    }
    
    printf("\n");

    int sum = 0;

    // Use pointer arithmetic to access the elements of the array
    printf("Array address: %p\n", array);
    for (i = 0; i < 10; i++) {
        sum = sum + *(array + i);     
    }
    printf("sum: %i\n", sum);
}