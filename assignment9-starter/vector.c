/* vector.c
Written by Thien K. M. Bui and Victor Huang
Last Editted 01/30/22
*/
#include <stdio.h>
#include <stdlib.h>
#include "vector.h"

/*
init()
param:  VECTOR *vector, INT memorySize
return: void, set 
    vector.array to a C array of appropriate size
    vector.memorySize to memorySize
    vector.size to 0
*/
void init(Vector *vector, int memorySize)
{
    vector->memorySize = memorySize;
    vector->size = 0;

    //reserve space for vector->array
    vector->array = malloc(memorySize * sizeof(int));
}

/*
print()
param: VECTOR *vector;
return: void, print out vector->memorySize,size,array
*/
void print(Vector *vector)
{
    printf("Array: {");
    for (int i = 0; i < vector->size; i++)
    {
        printf("%i,", vector->array[i]);
    }
    printf("}\n");
    printf("MemorySize: %i\n", vector->memorySize);
    printf("Size: %i\n", vector->size);
}

/*
insert()
param: VECTOR *vector, INT location, INT value
return: 
    1 if insert at location is successful 
    NOTE: if there's already a value at location, move the old value AND ALL subsequent values to the right (previous value at index 0 will now be moved to index 1)
    0 if location < 0 OR location greater than vector->size
    NOTE: insert in the last's cell (e.g. location = vector->size - 1) is accepted, and will instead doubles the internal array structure to store twice the values
*/
int insert(Vector *vector, int location, int value)
{
    if (location < 0 || location > vector->size)
    {
        return 0;
    }
    else
    {
        //need to increase the size of internal array
        if (vector->size + 1 == vector->memorySize)
        {
            int *new_array = malloc(vector->memorySize * 2 * sizeof(int));
            vector->memorySize = vector->memorySize * 2;
            //copy values from old array to new array
            for (int i = 0; i < vector->size; i++)
            {
                new_array[i] = vector->array[i];
                free(vector->array);
                vector->array = new_array;
            }
        }
        //insertion at the end
        //need to move all elements down
        //inserting in the middle, will need to shift elements to the right
        if (location != vector->size)
        {
            for (int i = vector->size - 1; i >= location; i--)
            {
                //store the next value and swap with the previous one
                vector->array[i + 1] = vector->array[i];
            }
        }
        vector->array[location] = value;
        vector->size = vector->size + 1;
        return 1;
    }
}

/*
get()
param: VECTOR *vector, INT location, INT value
return: 1 if insert is successful, 0 otherwise
    insert value into location (based on index) of vector
*/
int get(Vector *vector, int location, int *value)
{
    if (location >= 0 && location <= vector->size)
    {
        //iterate through vector->array
        for (int i = 0; i < vector->size; i++)
        {
            if (i == location)
            {
                *value = vector->array[i];
                return 1;
            }
        }
    }
    return 0;
}

/* 
cleanup()
Removes the array associated with the Vector. 
param: VECTOR *vector
*/

void cleanup(Vector *vector)
{
    free(vector->array);
    vector->array = malloc(vector->memorySize * sizeof(int));
}

/* Deletes value at location inside the Vector.  Return 1 for success, otherwise 
 0 if the location is invalid (less than 0, or greater than or equal to the
 size). When an item is deleted, everything else past it in the array should be
 slid down. The internal array itself does not need to be compressed, i.e., you
 don't need to halve it in size if it becomes half full, or anything like
 that. */

int delete (Vector *vector, int location)
{
    return 0;
}

// int main()
// {
//     struct Vector *vector = (Vector *)malloc(sizeof(Vector));
//     printf("Test 1.1...\n");
//     init(vector, 100);

//     int value;

//     for (int i = 0; i < 50; i++)
//     {
//         insert(vector, 0, i);
//     }
//     print(vector);
//     for (int i = -5; i < -2; i++)
//     {
//         int status = get(vector, i, &value);
//         printf("check: %i\n", status);
//     }

//     // for (int i = 0; i < 50; i++)
//     // {
//     //     int status = get(vector, 50 - i - 1, &value);
//     //     printf("status: %i ", status);
//     //     printf("value: %i\n", value);
//     //     // assert(i == value);
//     // }
//     int status = get(vector, 0, &value);
//     printf("status: %i, value: %i\n", status, value);
// }