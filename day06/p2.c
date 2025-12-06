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
        if (*p == '\n') break;
        char *sp = p;
        char operator = *p;
        ll res = 0;
        if (operator == '*') res = 1;
        p++;
        while (*p == ' ') p++;
        int jump = p-sp;
        if (*p == '\n') jump += 1;
        for (int i=0; i<jump-1; i++) {
            ll v = 0;
            ll fac = 1;
            for (int j=nargs-1; j>=0; j--) {
                if (lines[j][i]==' ') continue;
                if (lines[j][i]=='\n') continue;
                v += fac * (lines[j][i] - '0');
                fac *= 10;
            }
            if (operator == '*') res *= v;
            else                 res += v;
        }
        for (int j=0; j<nargs; j++) lines[j] += jump;
        sum += res;
    }
    printf("%lld\n", sum);
}
