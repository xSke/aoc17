#include <stdlib.h>
#include <mem.h>
#include <stdio.h>

void knothash_data_init(unsigned char data[256]) {
    for (int i = 0; i < 256; i++) data[i] = (unsigned char) i;
}

int knothash_round(unsigned char *data, const int input_length, const unsigned char *input, unsigned char *position,
                   int *skip) {
    for (int i = 0; i < input_length; i++) {
        int length = input[i];

        unsigned char tmp[length];
        for (int j = 0; j < length; j++) tmp[j] = data[*position + (length - j - 1) & 0xff];
        for (int j = 0; j < length; j++) data[(*position + j) & 0xff] = tmp[j];
        *position = (unsigned char) (*position + length + (*skip)++);
    }
}

void knothash_reduce(unsigned char dense[16], const unsigned char sparse[256]) {
    memset(dense, 0, 16);
    for (int i = 0; i < 16; i++) {
        for (int j = 0; j < 16; j++) {
            dense[i] ^= sparse[i * 16 + j];
        }
    }
}

void knothash(const int input_length, const unsigned char *input, unsigned char *out) {
    unsigned char data[256];
    knothash_data_init(data);

    unsigned char kinput[input_length + 5];
    memcpy(kinput, input, (size_t) input_length);

    // add suffix
    kinput[input_length] = 17;
    kinput[input_length + 1] = 31;
    kinput[input_length + 2] = 73;
    kinput[input_length + 3] = 47;
    kinput[input_length + 4] = 23;

    unsigned char pos = 0;
    int skip = 0;

    for (int i = 0; i < 64; i++) {
        knothash_round(data, input_length + 5, kinput, &pos, &skip);
    }
    knothash_reduce(out, data);
}

int get_pos(const unsigned char grid[16 * 128], int x, int y) {
    return (grid[y * 16 + (x / 8)] >> 7 - (x % 8)) & 1;
}

int fill(const unsigned char grid[16 * 128], unsigned char visited[16 * 128], int x, int y) {
    visited[y * 16 + (x / 8)] |= 1 << 7 - (x % 8);
    if (x < 127 && get_pos(grid, x + 1, y) && !get_pos(visited, x + 1, y)) fill(grid, visited, x + 1, y);
    if (x > 0 && get_pos(grid, x - 1, y) && !get_pos(visited, x - 1, y)) fill(grid, visited, x - 1, y);
    if (y < 127 && get_pos(grid, x, y + 1) && !get_pos(visited, x, y + 1)) fill(grid, visited, x, y + 1);
    if (y > 0 && get_pos(grid, x, y - 1) && !get_pos(visited, x, y - 1)) fill(grid, visited, x, y - 1);
}

int main(int argc, char **argv) {
    if (argc <= 1) return 1;

    char *key = argv[1];

    unsigned char grid[128 * 16] = {};

    int total = 0;
    for (int i = 0; i < 128; i++) {
        char buf[30];
        sprintf(buf, "%s-%d", key, i);

        knothash(strlen(buf), (const unsigned char *) buf, &grid[i * 16]);

        for (int j = 0; j < 16; j++) {
            unsigned char b = grid[i * 16 + j];
            for (int k = 7; k >= 0; k--) {
                char used = (char) ((b >> k) & 1);
                total += used;
                //printf(used ? "#" : ".");
            }
        }
        //printf("\n");
    }

    int total2 = 0;
    unsigned char visited[128 * 16] = {};
    for (int x = 0; x < 128; x++) {
        for (int y = 0; y < 128; y++) {
            if (get_pos(grid, x, y) && !get_pos(visited, x, y)) {
                fill(grid, visited, x, y);
                total2++;
            }
        }
    }

    printf("%d\n", total);
    printf("%d\n", total2);
}