#include <string.h>
#include <stdio.h>
#include <stdlib.h>

long long int value(long long int regs[8], char *v) {
    if (v[0] >= 'a') return regs[v[0] - 'a'];
    return atoi(v);
}

int is_prime(int num) {
    if (num <= 1) return 0;
    if (num % 2 == 0 && num > 2) return 0;
    for (int i = 3; i < num / 2; i += 2) {
        if (num % i == 0)
            return 0;
    }
    return 1;
}

long long int program(int _b, int _c) {
    int h = 0;
    for (int b = _b; b <= _c; b += 17) {
        if (!is_prime(b)) h++;
    }
    return h;
}

int main() {
    char buf[100];

    char *lines[50] = {0};
    int line_count = 0;
    while (strlen(fgets(buf, 100, stdin)) > 1) {
        buf[strlen(buf) - 1] = '\0';
        lines[line_count] = strdup(buf);
        lines[line_count][3] = '\0';
        lines[line_count][5] = '\0';
        line_count++;
    }

    long long int regs[8] = {0};
    int pc = 0;
    int mults = 0;
    while (pc >= 0 && pc < line_count) {
        if (strcmp(lines[pc], "set") == 0) {
            long long int val = value(regs, &lines[pc][6]);
            regs[lines[pc][4] - 'a'] = val;
        } else if (strcmp(lines[pc], "sub") == 0) {
            long long int val = value(regs, &lines[pc][6]);
            regs[lines[pc][4] - 'a'] -= val;
        } else if (strcmp(lines[pc], "mul") == 0) {
            long long int val = value(regs, &lines[pc][6]);
            regs[lines[pc][4] - 'a'] *= val;
            mults++;
        } else if (strcmp(lines[pc], "jnz") == 0) {
            long long int valx = value(regs, &lines[pc][4]);
            long long int valy = value(regs, &lines[pc][6]);
            if (valx != 0) {
                pc += valy - 1;
            }
        }
        pc++;
    }

    printf("%d\n", mults);

    int n = atoi(&lines[0][6]);
    printf("%d\n", program(100000 + n * 100, 100000 + n * 100 + 17000));
}