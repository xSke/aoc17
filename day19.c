#include <string.h>
#include <stdio.h>

int main() {
    char buf[1000];

    char *lines[500] = {};
    int line_count = 0;
    while (strlen(fgets(buf, 1000, stdin)) > 1) {
        buf[strlen(buf) - 1] = '\0';
        lines[line_count++] = strdup(buf);
    }

    int x = 0;
    int y = 0;
    // down = 0, right = 1, up = 2, left = 3
    int dir = 0;
    for (int xx = 0; xx < strlen(lines[0]); xx++) if (lines[0][xx] == '|') x = xx;

    char hit[26] = {};
    int hit_count = 0;

    int steps = 1;

    while (1) {
        if (dir == 0) y++;
        if (dir == 1) x++;
        if (dir == 2) y--;
        if (dir == 3) x--;

        if (lines[y][x] == '+') {
            if (y < line_count-1 && (lines[y+1][x] == '|' || (lines[y+1][x] >= 'A' && lines[y+1][x] <= 'Z')) && dir != 2) dir = 0;
            else if (x < strlen(lines[y]) - 1 && (lines[y][x+1] == '-' || (lines[y][x+1] >= 'A' && lines[y][x+1] <= 'Z')) && dir != 3) dir = 1;
            else if (y > 0 && (lines[y-1][x] == '|' || (lines[y-1][x] >= 'A' && lines[y-1][x] <= 'Z')) && dir != 0) dir = 2;
            else if (x > 0 && (lines[y][x-1] == '-' || (lines[y][x-1] >= 'A' && lines[y][x-1] <= 'Z')) && dir != 1) dir = 3;
        } else if (lines[y][x] == ' ') {
            break;
        } else if (lines[y][x] >= 'A' && lines[y][x] <= 'Z') {
            hit[hit_count++] = lines[y][x];
        }

        steps++;
    }
    hit[hit_count] = '\0';

    printf("%s\n", hit);
    printf("%d\n", steps);
}