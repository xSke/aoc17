#include <stdlib.h>
#include <mem.h>
#include <stdio.h>

typedef struct Pattern {
    int input_size;
    char *input;
    int output_size;
    char *output;
} Pattern;

void cut_block(char *out, int x, int y, int size, const char *in, int in_size) {
    for (int xx = 0; xx < size; xx++) {
        for (int yy = 0; yy < size; yy++) {
            out[yy * size + xx] = in[(yy + (y * size)) * in_size + (xx + (x * size))];
        }
    }
}

void paste_block(char *out, int out_size, int x, int y, int size, const char *in) {
    for (int xx = 0; xx < size; xx++) {
        for (int yy = 0; yy < size; yy++) {
            out[(yy + (y * size)) * out_size + (xx + (x * size))] = in[yy * size + xx];
        }
    }
}

int flip_h(char *out, const char *in, int size) {
    for (int x = 0; x < size; x++) {
        for (int y = 0; y < size; y++) {
            out[y * size + x] = in[y * size + (size - x - 1)];
        }
    }
}

int flip_v(char *out, const char *in, int size) {
    for (int x = 0; x < size; x++) {
        for (int y = 0; y < size; y++) {
            out[y * size + x] = in[(size - y - 1) * size + x];
        }
    }
}

int rotate(char *out, const char *in, int size) {
    for (int x = 0; x < size; x++) {
        for (int y = 0; y < size; y++) {
            out[y * size + x] = in[x * size + (size - y - 1)];
        }
    }
}

void print(const char *grid, int size) {
    for (int y = 0; y < size; y++) {
        for (int x = 0; x < size; x++) {
            putchar(grid[y * size + x] ? '#' : '.');
        }
        putchar('\n');
    }
    putchar('\n');
}

int matches(char *haystack, int haystack_size, int hx, int hy, Pattern *pattern) {
    int size = pattern->input_size;
    char input[size * size];
    cut_block(input, hx, hy, size, haystack, haystack_size);

    char tmp[size * size];

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < sizeof(tmp); j++) tmp[j] = input[j];
        if (memcmp(tmp, pattern->input, sizeof(char) * size * size) == 0) return 1;

        flip_h(input, tmp, size);
        for (int j = 0; j < sizeof(tmp); j++) tmp[j] = input[j];
        if (memcmp(tmp, pattern->input, sizeof(char) * size * size) == 0) return 1;

        flip_h(input, tmp, size);
        for (int j = 0; j < sizeof(tmp); j++) tmp[j] = input[j];
        flip_v(input, tmp, size);
        for (int j = 0; j < sizeof(tmp); j++) tmp[j] = input[j];
        if (memcmp(tmp, pattern->input, sizeof(char) * size * size) == 0) return 1;

        flip_v(input, tmp, size);
        for (int j = 0; j < sizeof(tmp); j++) tmp[j] = input[j];
        if (memcmp(tmp, pattern->input, sizeof(char) * size * size) == 0) return 1;

        rotate(input, tmp, size);
    }
    return 0;
}

char *step(char last_grid[], int last_size, Pattern patterns[], int patterns_len, int *out_new_size) {
    int last_block_size = (last_size % 2 == 0) ? 2 : 3;

    int new_size = (last_size % 2 == 0) ? (last_size + last_size / 2) : (last_size + last_size / 3);
    int block_size = (last_size % 2 == 0) ? 3 : 4;
    char *grid = calloc((size_t) (new_size * new_size), sizeof(char));

    for (int x = 0; x < new_size / block_size; x++) {
        for (int y = 0; y < new_size / block_size; y++) {
            for (int p = 0; p < patterns_len; p++) {
                Pattern *pat = &patterns[p];
                if (pat->input_size != last_block_size) continue;

                if (matches(last_grid, last_size, x, y, pat)) {
                    paste_block(grid, new_size, x, y, block_size, pat->output);
                }
            }
        }
    }

    *out_new_size = new_size;
    return grid;
}

int pixels_on(const char *grid, int size) {
    int pixels_on = 0;
    for (int x = 0; x < size; x++) {
        for (int y = 0; y < size; y++) {
            if (grid[y * size + x]) pixels_on++;
        }
    }
    return pixels_on;
}

int main() {
    int size = 3;
    char *grid = calloc((size_t) (size * size), sizeof(char));
    grid[1] = 1;
    grid[5] = 1;
    grid[6] = 1;
    grid[7] = 1;
    grid[8] = 1;

    Pattern patterns[500];
    int pattern_count = 0;

    char buf[100] = {};
    while (strlen(fgets(buf, 100, stdin)) > 1) {
        buf[strlen(buf) - 1] = '\0';

        Pattern p;
        if (strstr(buf, "=>") == &buf[6]) {
            p.input_size = 2;
            p.output_size = 3;
            p.input = calloc(4, sizeof(char));
            p.output = calloc(9, sizeof(char));

            // size 2
            for (int x = 0; x < 2; x++) {
                for (int y = 0; y < 2; y++) {
                    p.input[y * 2 + x] = buf[y * 3 + x] == '#';
                }
            }

            for (int x = 0; x < 3; x++) {
                for (int y = 0; y < 3; y++) {
                    p.output[y * 3 + x] = buf[y * 4 + x + 9] == '#';
                }
            }
        } else {
            p.input_size = 3;
            p.output_size = 4;
            p.input = calloc(9, sizeof(char));
            p.output = calloc(16, sizeof(char));

            // size 3
            for (int x = 0; x < 3; x++) {
                for (int y = 0; y < 3; y++) {
                    p.input[y * 3 + x] = buf[y * 4 + x] == '#';
                }
            }

            for (int x = 0; x < 4; x++) {
                for (int y = 0; y < 4; y++) {
                    p.output[y * 4 + x] = buf[y * 5 + x + 15] == '#';
                }
            }
        }
        patterns[pattern_count++] = p;
    }

    for (int i = 0; i < 5; i++) {
        char *new_grid = step(grid, size, patterns, pattern_count, &size);
        free(grid);
        grid = new_grid;
    }

    printf("%d\n", pixels_on(grid, size));

    for (int i = 0; i < 13; i++) {
        char *new_grid = step(grid, size, patterns, pattern_count, &size);
        free(grid);
        grid = new_grid;
    }

    printf("%d\n", pixels_on(grid, size));
}