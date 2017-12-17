#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
    if (argc < 2) return 1;
    int skip = atoi(argv[1]);

    int v[2018] = {0};
    int v_count = 1;
    int v_pos = 0;

    for (int i = 1; i < 2018; i++) {
        v_pos = (v_pos + skip) % v_count++ + 1;
        for (int j = v_count-1; j > v_pos; j--) v[j] = v[j-1];
        v[v_pos] = i;
    }

    printf("%d\n", v[v_pos+1]);

    v_count = 1;
    v_pos = 0;
    int first_v = 0;
    for (int i = 1; i < 50000000; i++) {
        v_pos = (v_pos + skip) % v_count++ + 1;
        if (v_pos == 1) first_v = i;
    }

    printf("%d\n", first_v);
}