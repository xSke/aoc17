#include <mem.h>
#include <stdio.h>

typedef struct Program {
    char name[10];
    int weight;
    char *childrenNames[10];
    struct Program *parent;
} Program;

Program programs[10000];
int heapPtr;

Program *find(char *name) {
    for (int i = 0; i < heapPtr; i++) {
        if (strcmp(programs[i].name, name) == 0) return &programs[i];
    }
}

int weight(Program *prg) {
    int total = prg->weight;
    for (int i = 0; i < 10; i++) {
        if (prg->childrenNames[i] == NULL) break;
        total += weight(find(prg->childrenNames[i]));
    }
    return total;
}

int main() {
    char buf[1000];

    while (strlen(fgets(buf, 100, stdin)) > 1) {
        buf[strlen(buf) - 1] = '\0';

        Program p;
        p.parent = NULL;
        for (int j = 0; j < 10; j++) p.childrenNames[j] = NULL;
        sscanf(buf, "%s (%d) ", p.name, &p.weight);

        char *start = strstr(buf, "->");
        if (start != NULL) {
            start += 3;

            char *tok = strtok(start, ",");
            for (int j = 0; tok != NULL; j++) {
                p.childrenNames[j] = strdup(tok + ((j == 0) ? 0 : 1));
                tok = strtok(NULL, ",");
            }
        }
        programs[heapPtr++] = p;
    }

    for (int i = 0; i < heapPtr; i++) {
        for (int j = 0; j < 10; j++) {
            if (programs[i].childrenNames[j] == NULL) break;
            for (int k = 0; k < heapPtr; k++) {
                if (strcmp(programs[i].childrenNames[j], programs[k].name) == 0) {
                    programs[k].parent = &programs[i];
                }
            }
        }
    }

    Program *root;
    for (int i = 0; i < heapPtr; i++) {
        if (programs[i].parent == NULL) {
            root = &programs[i];
            printf("%s\n", programs[i].name);
            break;
        }
    }

    Program *unbalanced = root;
    int target;
    while (1) {
        int total = weight(unbalanced);

        int weights[2] = {};
        int weightCounts[2] = {};
        for (int i = 0; i < 10; i++) {
            if (unbalanced->childrenNames[i] == NULL) break;
            int w = weight(find(unbalanced->childrenNames[i]));
            if (weights[0] == 0) weights[0] = w;
            if (w != weights[0]) weights[1] = w;

            if (w == weights[0]) weightCounts[0]++;
            if (w == weights[1]) weightCounts[1]++;
        }

        if (weights[1] == 0) {
            printf("%d\n", unbalanced->weight - (total - target));
            break;
        } else {
            int odd = (weightCounts[0] == 1) ? weights[0] : weights[1];
            target = (weightCounts[0] == 1) ? weights[1] : weights[0];
            for (int i = 0; i < 10; i++) {
                if (unbalanced->childrenNames[i] == NULL) break;
                int w = weight(find(unbalanced->childrenNames[i]));
                if (w == odd) unbalanced = find(unbalanced->childrenNames[i]);
            }
        }
    }
}