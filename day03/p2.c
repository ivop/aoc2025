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

    int larvals[12], larposs[12];

    for (int j=0; j<height; j++) {
        long long v = 0;
        for (int x=0; x<12; x++) {
            int larval = 0;
            int larpos = x ? larposs[x-1]+1 : 0;
            for (int i=larpos; i<width-(12-1-x); i++) {
                if (lines[j][i] > larval) {
                    larval = lines[j][i];
                    larpos = i;
                }
            }
            larposs[x] = larpos;
            larvals[x] = larval;
            v *= 10;
            v += larval - '0';
        }
        sum += v;
    }

    printf("%lld\n", sum);
}
