#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <limits.h>
#include <unistd.h>

#define LINES

char **lines;
int nlines;
int space;

char *line;
size_t n;

int height;
int width;

int main(void) {
    while (getline(&line, &n, stdin) > 0) {
        if (nlines == space) {
            space += 16;
            lines = realloc(lines, space * sizeof(char*));
        }
        lines[nlines] = strdup(line);
        nlines++;
    }
    height = nlines;
    width = strlen(lines[0])-1;

    long long sum = 0;

    for (int j=0; j<height; j++) {
        int larval = 0, larpos = 0;        // but not in last position
        for (int i=0; i<width-1; i++) {
            if (lines[j][i] > larval) {
                larval = lines[j][i];
                larpos = i;
            }
        }
        int larval2 = 0, larpos2 = 0;
        for (int i=larpos+1; i<width; i++) {
            if (lines[j][i] > larval2) {
                larval2 = lines[j][i];
                larpos2 = i;
            }
        }
        larval -= '0';
        larval2 -= '0';
        sum += larval*10 + larval2;
    }

    printf("%lld\n", sum);
}
