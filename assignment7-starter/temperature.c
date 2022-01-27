/*temperature.c
Written by Thien K. M. Bui
Last modified 01-25-22
*/

#include <stdio.h>

int main() {
    float input;
    printf("What is the temperature in degrees Fahrenheit? ");
    scanf("%f", &input);

    if (input  <= -459.67){
        printf("Invalid temperature!\n");
    }else{
        float temp_celsius = (input - 32) * 5/9;
        printf("%f degrees Fahrenheit is %f Celsius\n", input, temp_celsius);
    }
    return 0;
}
