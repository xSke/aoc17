#include <stdio.h>
#include <mem.h>

int severity(int delay, const int layers[], int layerNum) {
    int severity = 0;
    int caught = 0;
    for (int i = 0; i < layerNum; i++) {
        if (layers[i]) {
            int sPos = (delay + i) % (layers[i] * 2 - 2);
            if (sPos >= layers[i]) sPos = (layers[i] * 2 - 2) - sPos;

            if (sPos == 0) {
                caught = 1;
                severity += i * layers[i];
            }
        }
    }
    return caught ? severity : -1;
}

int main() {
    char buf[100];
    int layers[100] = {0};
    int layerNum = 0;
    while (strlen(fgets(buf, 100, stdin)) > 1) {
        buf[strlen(buf) - 1] = '\0';

        int depth;
        int range;
        sscanf(buf, "%d: %d", &depth, &range);

        layers[depth] = range;
        layerNum = depth + 1;
    }

    printf("%d\n", severity(0, layers, layerNum));

    int i = 0;
    while (severity(i++, layers, layerNum) != -1) {}
    printf("%d\n", i-1);
}