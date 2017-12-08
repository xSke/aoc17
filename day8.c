#include <stdio.h>
#include <mem.h>

int main() {
    char buf[50];

    char *regNames[100] = {};
    int regValues[100] = {};

    int largestEver = -0xFFFFFFFF;
    while (strlen(fgets(buf, 1000, stdin)) > 1) {
        buf[strlen(buf) - 1] = '\0';

        char reg[5];
        char op[4];
        int val;
        char dep[5];
        char cmpOp[3];
        int cmpCmp;
        sscanf(buf, "%s %s %d if %s %s %d", reg, op, &val, dep, cmpOp, &cmpCmp);

        int i = 0;
        while (regNames[i] != NULL && strcmp(regNames[i], reg) != 0) i++;
        if (regNames[i] == NULL) regNames[i] = strdup(reg);

        int cmpVal = 0;
        for (int j = 0; regNames[j] != NULL; j++) {
            if (strcmp(regNames[j], dep) == 0) {
                cmpVal = regValues[j];
                break;
            }
        }

        if ((strcmp(cmpOp, "==") == 0 && cmpVal == cmpCmp) ||
            (strcmp(cmpOp, "!=") == 0 && cmpVal != cmpCmp) ||
            (strcmp(cmpOp, "<") == 0 && cmpVal < cmpCmp) ||
            (strcmp(cmpOp, ">") == 0 && cmpVal > cmpCmp) ||
            (strcmp(cmpOp, "<=") == 0 && cmpVal <= cmpCmp) ||
            (strcmp(cmpOp, ">=") == 0 && cmpVal >= cmpCmp)) {
            if (strcmp(op, "inc") == 0) regValues[i] += val;
            else regValues[i] -= val;
        }

        if (regValues[i] > largestEver) largestEver = regValues[i];
    }

    int largestEnd = -0xFFFFFFFF;
    for (int j = 0; regNames[j] != NULL; j++) {
        if (regValues[j] > largestEnd) largestEnd = regValues[j];
    }
    printf("%d\n", largestEnd);
    printf("%d\n", largestEver);
}