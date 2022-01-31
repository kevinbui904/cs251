#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>
#include "vector.h"
#include <stdio.h>


void test1() {
    // 1.1 Create an empty vector with memory size of 100
    Vector *vector = (Vector *)malloc(sizeof(Vector));
    printf("Test 1.1...\n");
    init(vector, 100);
    printf("\tPASSED\n");

    // 1.2 Insert 50 numbers into it, producing [49, 48, 47, ..., 0]
    printf("Test 1.2...\n");
    for (int i=0; i < 50; i++) {
        assert(insert(vector, 0, i));
    }
    printf("\tPASSED\n");

    // 1.3 Make sure that the right numbers went into the right spots, e.g.,
    // 49 should be at index 0, 48 at index 1, and 0 at index 49.
    printf("Test 1.3...\n");
    int value;
    for (int i=0; i < 50; i++) {
        int status = get(vector, 50-i-1, &value);
        assert(1==status);
        assert(i==value);
    }
    printf("\tPASSED\n");

    // 1.4 Make sure 0 is returned for illegal get() calls in the form
    // of negative indices
    printf("Test 1.4...\n");
    for (int i=-5; i < -2; i++) {
        int status = get(vector, i, &value);
        assert(0==status);
    }
    printf("\tPASSED\n");

    // 1.5 Make sure 0 is returned for illegal get() calls in the form
    // of indices past the end of the actual array contents
    printf("Test 1.5...\n");
    for (int i=50; i < 53; i++) {
        int status = get(vector, i, &value);
        assert(0==status);
    }
    printf("\tPASSED\n");

    // 1.6 Clean up memory
    printf("Test 1.6...\n");
    cleanup(vector);
    free(vector);
    printf("\tPASSED\n");

}



void test2() {
    // 2.1 Create an empty vector with memory size of 10
    printf("Test 2.1...\n");
    Vector *vector = (Vector *)malloc(sizeof(Vector));
    init(vector, 10);
    printf("\tPASSED\n");

    // 2.2 Insert 50 numbers into it, which means it will
    // have to double at various points.
    printf("Test 2.2...\n");
    for (int i=0; i < 50; i++) {
        assert(insert(vector, 0, i));
    }
    printf("\tPASSED\n");

    // 2.3 Make sure that the right numbers went into the right spots, e.g.,
    // 49 should be at index 0, 48 at index 1, and 0 at index 49.
    printf("Test 2.3...\n");
    int value;
    for (int i=0; i < 50; i++) {
        int status = get(vector, 50-i-1, &value);
        assert(1==status);
        assert(i==value);
    }
    printf("\tPASSED\n");

    // 2.4 Make sure 0 is returned for illegal get() calls in the form
    // of negative indices
    printf("Test 2.4...\n");
    for (int i=-5; i < -2; i++) {
        int status = get(vector, i, &value);
        assert(0==status);
    }
    printf("\tPASSED\n");

    // 2.5 Make sure 0 is returned for illegal get() calls in the form
    // of indices past the end of the actual array contents
    printf("Test 2.5...\n");
    for (int i=50; i < 53; i++) {
        int status = get(vector, i, &value);
        assert(0==status);
    }
    printf("\tPASSED\n");

    // 2.6 Delete a few values
    printf("Test 2.6...\n");
    assert(delete(vector, 6));
    assert(delete(vector, 12));
    printf("\tPASSED\n");

    // 2.7 Location 49 should no longer be there, because the vector has 
    // shrunk due to the deletion above.
    printf("Test 2.7...\n");
    assert(!delete(vector, 49));
    printf("\tPASSED\n");

    // 2.8 Make sure everything up until location 6 is still in its
    // place, e.g., 49 in 0, 48 in 1, etc. Nothing should have shifted
    // prior to location 6, which was deleted above.
    printf("Test 2.8...\n");
    for (int i=0; i < 6; i++) {
        int status = get(vector, i, &value);
        assert(status);
        assert(50-i-1 == value);
    }
    printf("\tPASSED\n");

    // 2.9 Make sure that everything slid down correctly due to the
    // deletions above. The values now at locations between 6 and 12 
    // should have only slid down one slot.
    printf("Test 2.9...\n");
    for (int i=6; i < 12; i++) {
        int status = get(vector, i, &value);
        assert(status);
        assert(50-i-2 == value);
    }
    printf("\tPASSED\n");

    // 2.10 Make sure that everything slid down correctly due to the
    // deletions above. The values now at locations between 12 and 48 
    // should have slid down two slots.
    printf("Test 2.10...\n");
    for (int i=12; i < 48; i++) {
        int status = get(vector, i, &value);
        assert(status);
        assert(50-i-3 == value);
    }
    printf("\tPASSED\n");

    // 2.11 Ensure that, following the deltions, that 0 is returned for
    // get() calls for locations past 48.
    printf("Test 2.11...\n");
    for (int i=48; i < 53; i++) {
        int status = get(vector, i, &value);
        assert(!status);
    }
    printf("\tPASSED\n");

    // 2.12 Clean up memory
    printf("Test 2.12...\n");
    cleanup(vector);
    free(vector);
    printf("\tPASSED\n");

}

int main() {
    test1();
    test2();
}
