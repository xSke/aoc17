#include <string.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Program {
    int pipes[10];
    int pipeCount;
} Program;

void visit(int id, Program *programs, char *visited, int pCount) {
    visited[id] = 1;
    for (int i = 0; i < programs[id].pipeCount; i++) {
        int cid = programs[id].pipes[i];

        if (!visited[cid]) {
            visit(cid, programs, visited, pCount);
        }
    }
}

int main() {
    char buf[1000];

    Program programs[3000];
    int ps = 0;

    while (strlen(fgets(buf, 1000, stdin)) > 1) {
        buf[strlen(buf) - 1] = '\0';

        int pid;
        sscanf(buf, "%d <-> ", &pid);

        Program p;

        char *tok = strtok(strstr(buf, "<-> ") + 4, ",");
        int param = 0;
        while (tok != NULL) {
            if (tok[0] == ' ') p.pipes[param++] = atoi(tok + 1);
            else p.pipes[param++] = atoi(tok);

            tok = strtok(NULL, ",");
        }
        p.pipeCount = param;

        programs[ps++] = p;
    }

    char visited[ps];
    for (int i = 0; i < ps; i++) visited[i] = 0;
    visit(0, programs, visited, ps);

    int count = 0;
    for (int i = 0; i < ps; i++) if (visited[i]) count++;
    printf("%d\n", count);

    int groups = 1; // includes 0 group above
    char done = 0;
    while (1) {
        int firstNotIn = 0;
        while (visited[++firstNotIn]) {
            if (firstNotIn == ps-1) {
                done = 1;
                break;
            }
        }
        if (done) break;
        visit(firstNotIn, programs, visited, ps);
        groups++;
    }
    printf("%d\n", groups);
}