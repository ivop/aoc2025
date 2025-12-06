#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <limits.h>
#include <unistd.h>

char **lines;
int nlines;
int space;

char *line;
size_t n;

typedef long long ll;

int main(void) {
    while (getline(&line, &n, stdin) > 0) {
        if (nlines == space) {
            space += 16;
            lines = realloc(lines, space * sizeof(char*));
        }
        lines[nlines] = strdup(line);
        nlines++;
    }

    int nargs = nlines - 1;

    char *p = lines[nargs];
    ll sum = 0;
    while (1) {
        while (*p == ' ') p++;
        char operator = *p++;
        if (!*p || operator == '\n') break;
        ll res = 0;
        if (operator == '*') res = 1;
        for (int i=0; i<nargs; i++) {
            char *q = lines[i];
            while (*q == ' ') q++;
            ll v = strtoll(q, &lines[i], 10);
            if (operator == '*') res *= v;
            else                 res += v;
        }
        sum += res;
    }
    printf("%lld\n", sum);
}
