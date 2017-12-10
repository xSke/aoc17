#include <stdio.h>
#include <mem.h>
#include <stdlib.h>

void knothash_data_init(unsigned char data[256]) {
    for (int i = 0; i < 256; i++) data[i] = (unsigned char) i;
}

int knothash_round(unsigned char *data, const int input_length, const unsigned char *input, unsigned char *position,
                   int *skip) {
    for (int i = 0; i < input_length; i++) {
        int length = input[i];

        unsigned char tmp[length];
        for (int j = 0; j < length; j++) tmp[j] = data[*position + (length - j - 1) & 0xff];
        for (int j = 0; j < length; j++) data[(*position + j) & 0xff] = tmp[j];
        *position = (unsigned char) (*position + length + (*skip)++);
    }
}

void knothash_reduce(unsigned char dense[16], const unsigned char sparse[256]) {
    memset(dense, 0, 16);
    for (int i = 0; i < 16; i++) {
        for (int j = 0; j < 16; j++) {
            dense[i] ^= sparse[i * 16 + j];
        }
    }
}

int round1(const char *input_buf) {
    unsigned char round1_input[20];
    int round1_input_len = 0;

    // strtok messes input list up, so duplicate it
    char *input_dup = strdup(input_buf);

    // loop through and add to input buffer (as comma separated int values)
    char *tok = strtok(input_dup, ",");
    while (tok != NULL) {
        round1_input[round1_input_len++] = (unsigned char) atoi(tok);
        tok = strtok(NULL, ",");
    }

    // free duplicated string, don't need it
    free(input_dup);

    unsigned char data[256];
    unsigned char pos = 0;
    int skip = 0;
    knothash_data_init(data);
    knothash_round(data, round1_input_len, round1_input, &pos, &skip);

    return data[0] * data[1];
}

int round2(char output[33], const char *input_buf) {
    // discard newline (-1) and add suffix (+5)
    int input_len = strlen(input_buf) - 1 + 5;
    unsigned char input[input_len];
    memcpy(input, input_buf, (size_t) (input_len - 5));

    // add suffix
    input[input_len - 5] = 17;
    input[input_len - 4] = 31;
    input[input_len - 3] = 73;
    input[input_len - 2] = 47;
    input[input_len - 1] = 23;

    unsigned char data[256];
    unsigned char pos = 0;
    int skip = 0;
    knothash_data_init(data);

    // run 64 rounds
    for (int i = 0; i < 64; i++) {
        knothash_round(data, input_len, input, &pos, &skip);
    }

    // reduce sparse to dense
    unsigned char dense[16] = {0};
    knothash_reduce(dense, data);

    // print to hex
    const char *hex = "0123456789abcdef";
    for (int i = 0; i < 16; i++) {
        output[i * 2] = hex[dense[i] >> 4];
        output[i * 2 + 1] = hex[dense[i] & 0xf];
    }
    output[32] = '\0';
}

int main() {
    char *input_buf = NULL;
    size_t input_buf_len = 0;
    int input_len = getline(&input_buf, &input_buf_len, stdin);

    int round1_res = round1(input_buf);
    printf("%d\n", round1_res);

    char output[33];
    round2(output, input_buf);
    printf("%s\n", output);
}