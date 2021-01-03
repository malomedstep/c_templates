#include <stdio.h>
#include "list.h"


DeclareList(int);
DeclareList(double);

void print_i(const int *i) {
    printf("%d", *i);
}

void print_d(const double *d) {
    printf("%f", *d);
}


int main() {
    List_var(ints, int);
    add(ints, 42);
    add(ints, 15);
    add(ints, 0);
    add(ints, 999);
    insert(ints, 777, 2);
    remove(ints, 0);

    foreach(ints, print_i);
    printf("\n");
    destroy(ints);


    List_var(doubles, double);
    add(doubles, 5.7);
    add(doubles, 17.2);
    foreach(doubles, print_d);
    printf("\n");
    destroy(doubles);
    return 0;
}

