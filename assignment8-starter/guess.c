/*guess.c
Written by Thien K. M. Bui
Last editted 01/26/22
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    unsigned int seed;
    printf("Enter the random seed: ");
    scanf("%u", &seed);
    // seed = time(NULL);
    srandom(seed);
    int random_number = random()%100 + 1;
    printf("%i\n", random_number);

    printf("Guess my number: ");
    int user_guess;
    int count = 1;
    scanf("%i", &user_guess);

    while (user_guess != random_number){
        if(user_guess > random_number){
            printf("Too high!\n");
            printf("Guess my number: ");
            scanf("%i", &user_guess);
        }else{
            printf("Too low!\n");
            printf("Guess my number: ");

            scanf("%i", &user_guess);
        }
        count = count + 1;
    }
    printf("Correct!");
    printf("Total guesses = %i\n", count);
}