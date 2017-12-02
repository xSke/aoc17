#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int main() {
    char *linebuf = 0;
    size_t buflen = 0;
    ssize_t read;

    unsigned int sum = 0;
    unsigned int sum2 = 0;

    while ((read = getline(&linebuf, &buflen, stdin)) != -1) {
        if (read <= 1) break;
        linebuf[read] = '\0';

        unsigned int smallest = 0xFFFFFFFF;
        unsigned int largest = 0;

        int numbers[100];

        int ii = 0;
        char *token = strtok(strdup(linebuf), "\t ");
        while (token != NULL) {
            unsigned int i = (unsigned int) atoi(token);

            if (i < smallest) smallest = i;
            if (i > largest) largest = i;
            numbers[ii++] = i;

            token = strtok(NULL, "\t ");
        }

        for (int i = 0; i < ii; i++) {
            for (int j = 0; j < ii; j++) {
                if (i == j) continue;
                double div = ((double) numbers[i] / numbers[j]);
                if (rint(div) == div) {
                    sum2 += numbers[i] / numbers[j];
                }
            }
        }

        sum += largest - smallest;

        free(linebuf);
        linebuf = 0;
        buflen = 0;
    }

    printf("%u\n", sum);
    printf("%u\n", sum2);
}