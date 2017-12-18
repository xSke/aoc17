#include <mem.h>
#include <stdio.h>
#include <stdlib.h>

long long int value(long long int regs[26], char *v) {
    if (v[0] >= 'a') return regs[v[0] - 'a'];
    return atoi(v);
}

typedef struct ProgramState {
    int pc;
    long long int regs[26];
    long long int input_queue[1000];
    int input_queue_length;
    int terminated;
    int send_count;
} ProgramState;

void run(char **program, ProgramState *this, ProgramState *other) {
    while (!this->terminated) {
        if (strcmp(program[this->pc], "snd") == 0) {
            long long int data = value(this->regs, &program[this->pc][4]);
            other->input_queue[other->input_queue_length++] = data;
            this->send_count++;
        } else if (strcmp(program[this->pc], "set") == 0) {
            long long int val = value(this->regs, &program[this->pc][6]);
            this->regs[program[this->pc][4] - 'a'] = val;
        } else if (strcmp(program[this->pc], "add") == 0) {
            long long int val = value(this->regs, &program[this->pc][6]);
            this->regs[program[this->pc][4] - 'a'] += val;
        } else if (strcmp(program[this->pc], "mul") == 0) {
            long long int val = value(this->regs, &program[this->pc][6]);
            this->regs[program[this->pc][4] - 'a'] *= val;
        } else if (strcmp(program[this->pc], "mod") == 0) {
            long long int val = value(this->regs, &program[this->pc][6]);
            this->regs[program[this->pc][4] - 'a'] %= val;
        } else if (strcmp(program[this->pc], "jgz") == 0) {
            long long int valx = value(this->regs, &program[this->pc][4]);
            long long int valy = value(this->regs, &program[this->pc][6]);
            if (valx > 0) {
                this->pc += valy - 1;
            }
        } else if (strcmp(program[this->pc], "rcv") == 0) {
            if (this->input_queue_length == 0) return;
            long long int val = this->input_queue[0];
            for (int i = 1; i < this->input_queue_length; i++) {
                this->input_queue[i - 1] = this->input_queue[i];
            }
            this->input_queue_length--;
            this->regs[program[this->pc][4] - 'a'] = val;
        }
        this->pc++;
    }
}

int main() {
    char buf[100];

    char *lines[50] = {};
    int line_count = 0;
    while (strlen(fgets(buf, 100, stdin)) > 1) {
        buf[strlen(buf) - 1] = '\0';
        lines[line_count] = strdup(buf);
        lines[line_count][3] = '\0';
        lines[line_count][5] = '\0';
        line_count++;
    }

    long long int regs[26] = {};

    int pc = 0;
    long long int last_sound = 0;
    while (pc >= 0 && pc < line_count) {
        if (strcmp(lines[pc], "snd") == 0) {
            long long int freq = value(regs, &lines[pc][4]);
            last_sound = freq;
        } else if (strcmp(lines[pc], "set") == 0) {
            long long int val = value(regs, &lines[pc][6]);
            regs[lines[pc][4] - 'a'] = val;
        } else if (strcmp(lines[pc], "add") == 0) {
            long long int val = value(regs, &lines[pc][6]);
            regs[lines[pc][4] - 'a'] += val;
        } else if (strcmp(lines[pc], "mul") == 0) {
            long long int val = value(regs, &lines[pc][6]);
            regs[lines[pc][4] - 'a'] *= val;
        } else if (strcmp(lines[pc], "mod") == 0) {
            long long int val = value(regs, &lines[pc][6]);
            regs[lines[pc][4] - 'a'] %= val;
        } else if (strcmp(lines[pc], "jgz") == 0) {
            long long int valx = value(regs, &lines[pc][4]);
            long long int valy = value(regs, &lines[pc][6]);
            if (valx > 0) {
                pc += valy - 1;
            }
        } else if (strcmp(lines[pc], "rcv") == 0) {
            long long int val = value(regs, &lines[pc][4]);
            if (val != 0) {
                printf("%d\n", last_sound);
                break;
            }
        }
        pc++;
    }

    ProgramState one;
    for (int i = 0; i < 26; i++) one.regs[i] = 0;
    one.input_queue_length = 0;
    one.terminated = 0;
    one.pc = 0;
    one.regs['p' - 'a'] = 0;
    one.send_count = 0;

    ProgramState two;
    for (int i = 0; i < 26; i++) two.regs[i] = 0;
    two.input_queue_length = 0;
    two.terminated = 0;
    two.pc = 0;
    two.regs['p' - 'a'] = 1;
    two.send_count = 0;

    do {
        run(lines, &one, &two);
        run(lines, &two, &one);
    } while (one.input_queue_length != 0 || two.input_queue_length != 0);

    printf("%d\n", two.send_count);
}