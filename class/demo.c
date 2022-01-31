double f1(int x){
    x *= 2;
    return x * 0.25;
}

double f2(int *y){
    *y = *y 2;
    return *y * 1.5;
}

int main() {
    int *y;
    int z = 6;
    y = &z; 
}


int *f() {
    *int my_array = malloc(10*sizeof(int));
    my_array[0] = 3;
    my_array[1] = 4;
    my_array[2] = 5;
    return my_array;
} 
