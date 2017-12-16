#include <stdio.h>
#include <stdlib.h>
#include <mem.h>

#define PRGS 16
#define LOOPS 1000000000

void do_spin(char programs[PRGS], int spin) {
    char buf[PRGS];
    for (int i = 0; i < PRGS; i++) {
        buf[(i + spin) % PRGS] = programs[i];
    }
    memcpy(programs, buf, sizeof(buf));
}

void do_exchange(char programs[PRGS], int a, int b) {
    char tmp = programs[a];
    programs[a] = programs[b];
    programs[b] = tmp;
}

void do_partner(char programs[PRGS], char a, char b) {
    a -= 'a';
    b -= 'a';

    int ap;
    int bp;
    for (int i = 0; i < PRGS; i++) {
        if (programs[i] == a) ap = i;
        if (programs[i] == b) bp = i;
    }
    do_exchange(programs, ap, bp);
}

void do_dance(char programs[PRGS], char *instrs) {
    instrs = strdup(instrs);
    char *tok = strtok(instrs, ",");
    while (tok != NULL) {
        if (tok[0] == 's') {
            int spin;
            sscanf(tok, "s%d", &spin);

            do_spin(programs, spin);
        } else if (tok[0] == 'x') {
            int a;
            int b;
            sscanf(tok, "x%d/%d", &a, &b);

            do_exchange(programs, a, b);
        } else if (tok[0] == 'p') {
            char a;
            char b;
            sscanf(tok, "p%c/%c", &a, &b);

            do_partner(programs, a, b);
        }
        tok = strtok(NULL, ",");
    }
    free(instrs);
}

int main() {
    char buf[100000] = {};
    fgets(buf, 100000, stdin);

    char programs[PRGS];
    for (int i = 0; i < PRGS; i++) programs[i] = (char) i;
    do_dance(programs, buf);

    for (int i = 0; i < PRGS; i++) {
        putchar('a' + programs[i]);
    }
    printf("\n");

    char seen[PRGS * 10000] = {};
    for (int i = 0; i < PRGS; i++) seen[i] = programs[i];

    int cycle_start;
    int cycle_end;

    for (int i = 1;; i++) {
        do_dance(programs, buf);
        for (int j = 0; j < i; j++) {
            if (memcmp(&seen[j * PRGS], programs, sizeof(programs[0]) * PRGS) == 0) {
                cycle_start = j;
                cycle_end = i;
                goto done;
            }
        }
        for (int j = 0; j < PRGS; j++) seen[PRGS * i + j] = programs[j];
    }

    int cycles;
    done:
    cycles = (LOOPS - cycle_start) / (cycle_end - cycle_start);
    int pre_pos = (cycles * (cycle_end - cycle_start)) + cycle_start;
    int seen_pos = (LOOPS - pre_pos) + cycle_start - 1;

    for (int i = 0; i < PRGS; i++) {
        putchar('a' + seen[seen_pos * PRGS + i]);
    }
}