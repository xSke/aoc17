#include <string.h>
#include <stdio.h>

#define GRIDSIZE 1024
char grid1[GRIDSIZE * GRIDSIZE];
char grid2[GRIDSIZE * GRIDSIZE];

void step(char *grid, int *x, int *y, int *dir, int *bursts, char part2) {
    char old_value = grid[*y * GRIDSIZE + *x];
    if (old_value == 0) *dir -= 1;
    if (old_value == 2) *dir += 1;
    if (old_value == 3) *dir += 2;

    while (*dir < 0) *dir += 4;
    while (*dir > 3) *dir -= 4;

    if (part2) {
        if (old_value == 0) grid[*y * GRIDSIZE + *x] = 1;
        else if (old_value == 1) {
            grid[*y * GRIDSIZE + *x] = 2;
            (*bursts)++;
        } else if (old_value == 2) grid[*y * GRIDSIZE + *x] = 3;
        else if (old_value == 3) grid[*y * GRIDSIZE + *x] = 0;

    } else {
        if (old_value == 2) grid[*y * GRIDSIZE + *x] = 0;
        else if (old_value == 0) {
            grid[*y * GRIDSIZE + *x] = 2;
            (*bursts)++;
        }
    }

    if (*dir == 0) (*y)--;
    if (*dir == 1) (*x)++;
    if (*dir == 2) (*y)++;
    if (*dir == 3) (*x)--;
}

int main() {
    char buf[100] = {};
    int read_y_pos = 0;
    while (strlen(fgets(buf, 100, stdin)) > 1) {
        buf[strlen(buf) - 1] = '\0';
        int len = strlen(buf);
        for (int x = 0; x < len; x++) {
            grid1[(GRIDSIZE / 2 - len / 2 + read_y_pos) * GRIDSIZE + (GRIDSIZE / 2 - len / 2 + x)] = (char) ((buf[x] == '#') ? 2 : 0);
        }
        read_y_pos++;
    }
    for (int i = 0; i < GRIDSIZE * GRIDSIZE; i++) grid2[i] = grid1[i];

    int x = GRIDSIZE / 2;
    int y = GRIDSIZE / 2;
    int bursts1 = 0;
    int dir = 0;
    for (int i = 0; i < 10000; i++) step(grid1, &x, &y, &dir, &bursts1, 0);

    x = GRIDSIZE / 2;
    y = GRIDSIZE / 2;
    int bursts2 = 0;
    dir = 0;
    for (int i = 0; i < 10000000; i++) step(grid2, &x, &y, &dir, &bursts2, 1);


    printf("%d\n", bursts1);
    printf("%d\n", bursts2);
}