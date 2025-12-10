#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <limits.h>
#include <unistd.h>
#include <stdarg.h>
#include <ctype.h>

static void fatal(char *s, ...) {
    va_list ap;
    va_start(ap,s);
    fprintf(stderr, "error: ");
    vfprintf(stderr, s, ap);
    va_end(ap);
    exit(1);
}

struct machine {
    int target;
    int nbuttons;
    int *buttons;
};

int nmachines;
struct machine *machines;

static int getnum(void) {
    int v = 0;
    while (1) {
        int c = fgetc(stdin);
        if (!isdigit(c)) {
            ungetc(c, stdin);
            return v;
        }
        v *= 10;
        v += c - '0';
    }
}

struct entry;

struct entry {
    int cur;
    int presses;
    struct entry *next;
};

struct entry *first;
struct entry *last;

static int solve_machine(int i) {
    struct machine *m = &machines[i];
    int nbuttons = m->nbuttons;
    int target = m->target;

    // BFS
    // start with queue with one empty entry
    first = calloc(1, sizeof(struct entry));
    last = first;

    struct entry *n = NULL;

    while (1) {
        // for each entry at the front of the queue, press each of the buttons
        // create new entry and add entry at the back of the queue
        for (int i=0; i<nbuttons; i++) {
            n = malloc(sizeof(struct entry));
            memcpy(n, first, sizeof(struct entry));
            n->cur ^= m->buttons[i];
            n->presses++;

            if (n->cur == target) goto done;

            last->next = n;
            last = n;
        }
        struct entry *save = first;
        first = first->next;
        free(save); // popped
    }

done:
    int p = n->presses;
    free(n);
    while (first != last) {
        n = first->next;
        free(first);
        first = n;
    }
    free(last);
    return p;
}

int main(void) {
    int c;

    while ((c = fgetc(stdin)) >= 0) {
        nmachines++;
        machines = realloc(machines, nmachines * sizeof(struct machine));

        if (c != '[') fatal("[ expected\n");

        int pat = 0;  // # of lights are less than 32, so bit pattern fits
        int bit = 0;

        while ((c = fgetc(stdin)) != ']') {
            if (c<0) fatal("parse error\n");
            if (c == '#') pat |= 1<<bit;
            bit++;
        }

        struct machine *m = &machines[nmachines-1];
        memset(m, 0, sizeof(struct machine));
        m->target = pat;

        while (1) {
            c = fgetc(stdin);
            c = fgetc(stdin);
            if (c != '(') break;
            m->nbuttons++;
            m->buttons = realloc(m->buttons, m->nbuttons * sizeof(int));
            int *b = &m->buttons[m->nbuttons-1];
            *b = 0;
            while (1) {
                int but = getnum();
                *b |= 1<<but;
                c = fgetc(stdin);
                if (c == ')') break;
                if (c != ',') fatal("expected , or )\n");
            }
        }

        if (c != '{') fatal("expected '{'\n");

        while ((c = fgetc(stdin)) != '\n') ;
    }

    long long sum = 0;
    for (int i=0; i<nmachines; i++) {
        sum += solve_machine(i);
    }

    printf("%lld\n", sum);
}
