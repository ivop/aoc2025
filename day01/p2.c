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

int main(void) {
    while (getline(&line, &n, stdin) > 0) {
        if (nlines == space) {
            space += 16;
            lines = realloc(lines, space * sizeof(char*));
        }
        lines[nlines] = strdup(line);
        nlines++;
    }

    int pos = 50, pwd = 0;

    for (int i=0; i<nlines; i++) {
        int r = atoi(&lines[i][1]);
        if (lines[i][0] == 'L') {
            if (!pos) pwd--;
            pos -= r;
            while (pos < 0) {
                pos += 100;
                pwd++;
            }
            if (!pos) pwd++;
        } else {
            pos += r;
            pwd += pos/100;
            pos %= 100;
        }
    }

    printf("%d\n", pwd);
}
