#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    char *linebuf = 0;
    size_t buflen = 0;
    ssize_t read;

    int count = 0;
    int count2 = 0;

    char *words[20] = {};
    char anawords[20][32];

    while ((read = getline(&linebuf, &buflen, stdin)) != -1) {
        if (read <= 1) break;
        // Kill the newline
        linebuf[read - 1] = '\0';

        char valid = 1;
        char valid2 = 1;

        char *token = strtok(linebuf, " ");
        for (int i = 0; token != NULL; i++) {
            words[i] = token;
            memset(anawords[i], 0, sizeof(anawords[1]));

            for (int j = 0; token[j] != 0; j++) {
                anawords[i][token[j] - 'a']++;
            }

            for (int j = 0; j < i; j++) {
                if (strcmp(words[j], token) == 0) {
                    valid = 0;
                }

                if (memcmp(anawords[i], anawords[j], sizeof(anawords[i])) == 0) {
                    valid2 = 0;
                }
            }

            token = strtok(NULL, " ");
        }
        if (valid) count++;
        if (valid2) count2++;

        free(linebuf);
        linebuf = NULL;
        buflen = 0;
    }

    printf("%d\n", count);
    printf("%d\n", count2);
}