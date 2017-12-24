#include <mem.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Component {
    int a;
    int b;
    int attached;
} Component;

void find(Component comps[100], int component_count, Component *stack[100], int i, int* strongest, int* longest_len, int* longest_str) {
    int score = 0;
    for (int j = 0; j < i; j++) {
        score += stack[j]->a + stack[j]->b;
    }
    if (score > *strongest) *strongest = score;

    if (i > *longest_len) {
        *longest_len = i;
        *longest_str = i;
    } else if (i == *longest_len) {
        if (score > *longest_str) {
            *longest_str = score;
        }
    }

    for (int j = 0; j < component_count; j++) {
        Component *cmp = &comps[j];

        char already_is_in_stack = 0;
        for (int k = 0; k < i; k++) {
            if (cmp == stack[k]) already_is_in_stack = 1;
        }
        if (already_is_in_stack) continue;

        if (i == 0) {
            if (cmp->a == 0 || cmp->b == 0) {
                cmp->attached = cmp->a == 0 ? 0 : 1;

                stack[i] = cmp;
                find(comps, component_count, stack, i + 1, strongest, longest_len, longest_str);
            }
        } else {
            Component *last = stack[i - 1];

            int not_attached = last->attached ? last->a : last->b;
            if (not_attached == cmp->a || not_attached == cmp->b) {
                cmp->attached = not_attached == cmp->a ? 0 : 1;

                stack[i] = cmp;

                find(comps, component_count, stack, i + 1, strongest, longest_len, longest_str);
            }
        }
    }
}

int main() {
    char buf[100];

    Component components[100] = {};
    int comps = 0;
    while (strlen(fgets(buf, 100, stdin)) > 1) {
        buf[strlen(buf) - 1] = '\0';

        Component c;

        char *tok = strtok(buf, "/");
        c.a = atoi(tok);
        tok = strtok(NULL, "/");
        c.b = atoi(tok);

        components[comps++] = c;
    }

    Component *stack[100];
    int strongest = 0;
    int longest_len = 0;
    int longest_strength = 0;
    find(components, comps, stack, 0, &strongest, &longest_len, &longest_strength);

    printf("%d\n", strongest);
    printf("%d\n", longest_strength);
}