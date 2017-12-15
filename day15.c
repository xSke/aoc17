#include <stdio.h>

int twist(unsigned long long int* val, int factor, int mult) {
    do {
        *val *= factor;
        *val %= 2147483647;
    } while (*val % mult != 0);
}

int main() {
    int startA;
    int startB;
    scanf("Generator A starts with %i\n", &startA);
    scanf("Generator B starts with %i", &startB);

    unsigned long long int a = (unsigned long long int) startA;
    unsigned long long int b = (unsigned long long int) startB;

    int matches = 0;
    for (int i = 0; i < 40000000; i++) {
        twist(&a, 16807, 1);
        twist(&b, 48271, 1);

        if ((a & 0xffff) == (b & 0xffff)) {
            matches++;
        }
    }

    printf("%d\n", matches);

    a = (unsigned long long int) startA;
    b = (unsigned long long int) startB;

    int matches2 = 0;
    for (int i = 0; i < 5000000; i++) {
        twist(&a, 16807, 4);
        twist(&b, 48271, 8);

        if ((a & 0xffff) == (b & 0xffff)) {
            matches2++;
        }
    }

    printf("%d\n", matches2);
}