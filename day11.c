#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main() {
    unsigned char *buf = NULL;
    size_t len = 0;
    int slen = getline((char **) &buf, &len, stdin);
    buf[slen - 1] = '\0';

    int x = 0;
    int y = 0;
    int z = 0;

    int furthest = 0;

    // https://www.redblobgames.com/grids/hexagons/
    char *tok = strtok(buf, ",");
    while (tok != NULL) {
        if (strcmp(tok, "nw") == 0) {
            y += 1;
            x -= 1;
        }
        if (strcmp(tok, "n") == 0) {
            y += 1;
            z -= 1;
        }
        if (strcmp(tok, "ne") == 0) {
            x += 1;
            z -= 1;
        }
        if (strcmp(tok, "sw") == 0) {
            x -= 1;
            z += 1;
        }
        if (strcmp(tok, "s") == 0) {
            y -= 1;
            z += 1;
        }
        if (strcmp(tok, "se") == 0) {
            y -= 1;
            x += 1;
        }

        int dist = (abs(x) + abs(y) + abs(z)) / 2;
        if (dist > furthest) furthest = dist;

        tok = strtok(NULL, ",");
    }

    int dist = (abs(x) + abs(y) + abs(z)) / 2;
    printf("%d\n", dist);
    printf("%d\n", furthest);
}