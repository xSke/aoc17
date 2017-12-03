#include <stdio.h>
#include <stdlib.h>

#define max(x, y) (x) < (y) ? (y) : (x)
#define min(x, y) (x) > (y) ? (y) : (x)

int part1(int number) {
    int x = 0;
    int y = 0;

    int i = 1;

    char reverse = 0;

    for (int step = 1;; step++) {
        int count = min(step, number - i);
        x += reverse ? -count : count;
        i += count;
        if (count != step) break;

        count = min(step, number - i);
        y += reverse ? -count : count;
        i += count;

        reverse = !reverse;
    }

    int distance = abs(x) + abs(y);
    return distance;
}

#define GRIDSIZE 1024

int part2(int number) {
    int **grid = calloc(GRIDSIZE, sizeof(int*));
    for (int i = 0; i < GRIDSIZE; i++) grid[i] = calloc(GRIDSIZE, sizeof(int*));

    int x = GRIDSIZE / 2;
    int y = GRIDSIZE / 2;

    grid[x][y] = 1;

    int i = 0;
    int step = 0;
    while (1) {
        int direction = (step % 4 >= 2) ? -1 : 1;
        int axisY = step % 2;
        int count = step / 2;

        for (int j = 0; j < count; j++) {
            if (axisY) y += direction;
            else x += direction;

            int value = 0;
            for (int xx = -1; xx <= 1; xx++) {
                for (int yy = -1; yy <= 1; yy++) {
                    value += grid[x+xx][y+yy];
                }
            }
            grid[x][y] = value;
            if (value > number) goto end;

            i++;
        }

        step++;
    }

    int val;
    end:
    val = grid[x][y];

    for (int q = 0; q < GRIDSIZE; q++) free(grid[i]);
    free(grid);

    return val;
}

int main(int argc, char **argv) {
    if (argc <= 1) return 1;

    int number = atoi(argv[1]);

    printf("%d\n", part1(number));
    printf("%d\n", part2(number));
}