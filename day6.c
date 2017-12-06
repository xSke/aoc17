#include <stdio.h>
#include <mem.h>
#include <stdlib.h>

#define BANKS 16

void read(int arr[]) {
    char buf[64];
    fgets(buf, 64, stdin);

    int i = 0;
    char* tok = strtok(buf, "\t ");
    while (tok != NULL) {
        arr[i++] = atoi(tok);
        tok = strtok(NULL, "\t ");
    }
}

int main() {
    int states[1024 * 16][BANKS] = {0};

    read(states[0]);
    int cycle = 0;
    int cyclelen = 0;
    while (1) {
        int highest = BANKS - 1;
        for (int i = BANKS; i >= 0; i--) {
            if (states[cycle][i] >= states[cycle][highest]) {
                highest = i;
            }
        }

        int count = states[cycle][highest];
        memcpy(states[cycle + 1], states[cycle], sizeof(states[cycle]));
        states[++cycle][highest] = 0;
        for (int i = 0; i < count; i++) {
            states[cycle][(highest + i + 1) % BANKS]++;
        }

        for (int i = cycle-1; i >= 0; i--) {
            if (memcmp(states[i], states[cycle], sizeof(states[i])) == 0) {
                cyclelen = cycle - i;
                goto end;
            }
        }
    }

    end:
    printf("%d\n", cycle);
    printf("%d\n", cyclelen);
}
