#include <stdio.h>

typedef struct StateInstruction {
    int write;
    int move;
    int next;
} StateInstruction;

typedef struct State {
    StateInstruction zero;
    StateInstruction one;
} State;

int main() {
    char initial;
    int checksum_pos;
    scanf("Begin in state %c.\n", &initial);
    scanf("Perform a diagnostic checksum after %d steps.\n\n", &checksum_pos);

    State states[10];
    int state_count = 0;

    char cur_state;
    while (scanf("In state %c:\n", &cur_state) > 0) {
        char buf[100];

        while (getchar() != '\n') {}

        State state;

        gets(buf);
        state.zero.write = buf[22] - '0';

        gets(buf);
        state.zero.move = buf[27] == 'r' ? 1 : -1;

        gets(buf);
        state.zero.next = buf[26] - 'A';

        while (getchar() != '\n') {}

        gets(buf);
        state.one.write = buf[22] - '0';

        gets(buf);
        state.one.move = buf[27] == 'r' ? 1 : -1;

        gets(buf);
        state.one.next = buf[26] - 'A';

        states[state_count++] = state;
        getchar();
    }

#define LENGTH 32768
    char tape[LENGTH] = {0};
    int state = initial - 'A';
    int pos = LENGTH / 2;
    int cycles = 0;

    while (1) {
        State *s = &states[state];
        StateInstruction *instr = (tape[pos] == 1) ? &s->one : &s->zero;

        tape[pos] = (char) instr->write;
        pos += instr->move;
        state = instr->next;

        if (++cycles == checksum_pos) {
            break;
        }
    }

    int ones = 0;
    for (int i = 0; i < LENGTH; i++) {
        ones += tape[i];
    }
    printf("%d\n", ones);
}