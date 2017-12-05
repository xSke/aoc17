#include <stdio.h>
#include <mem.h>
#include <stdlib.h>

int main() {
    // Init list of numbers
    int numbers[2048];

    // Buffer for text reading
    char buf[8];
    // Read into numbers until 2x newline
    int i = 0;
    while (strlen(fgets(buf, 8, stdin)) > 1) {
        numbers[i++] = atoi(buf);
    }

    // Clone for use in second part
    int numbers2[2048];
    memcpy(numbers2, numbers, sizeof(numbers));

    // Loop de loop
    int pos = 0;
    int steps = 0;
    while (pos >= 0 && pos < i) {
        int jump = numbers[pos];
        numbers[pos]++;
        pos += jump;

        steps++;
    }

    pos = 0;
    int steps2 = 0;
    while (pos >= 0 && pos < i) {
        int jump = numbers2[pos];
        numbers2[pos] += jump >= 3 ? -1 : 1;
        pos += jump;

        steps2++;
    }
    printf("%d\n", steps);
    printf("%d\n", steps2);
}