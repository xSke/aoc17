#include <stdlib.h>
#include <stdio.h>

int main() {
    char *stream = NULL;
    size_t bufSize = 0;
    int charsRead = 0;

    charsRead = getline(&stream, &bufSize, stdin);

    int totalScore = 0, garbage = 0, groupLevel = 0;
    while (*stream != '\0') {
        switch (*(stream++)) {
            case '{':
                totalScore += ++groupLevel;
                break;
            case '}':
                groupLevel--;
                break;
            case '<':
                while (*(stream++) != '>') {
                    if (*(stream - 1) == '!') stream++;
                    else garbage++;
                }
                break;
            default:break;
        }
    }

    printf("%d\n", totalScore);
    printf("%d\n", garbage);
}