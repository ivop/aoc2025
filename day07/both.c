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

    typedef long long ll;

    ll **count = malloc(width*sizeof(ll*));
    for (int y=0; y<height; y++)
        count[y] = calloc(1,width*sizeof(ll));

    for (int x=0; x<width; x++) {
        if (lines[0][x] == 'S') {
            lines[0][x] = '|';
            count[0][x] = 1;
        }
    }

    int split = 0;
    for (int y=0; y<height-1; y++) {
        for (int x=0; x<width; x++) {
            if (lines[y][x] == '|') {
                if (lines[y+1][x] == '^') {
                    split++;
                    lines[y+1][x-1] = '|';
                    lines[y+1][x+1] = '|';
                    count[y+1][x-1] += count[y][x];
                    count[y+1][x+1] += count[y][x];
                } else {
                    lines[y+1][x] = '|';
                    count[y+1][x] += count[y][x];
                }
            }
        }
    }
    printf("part 1: %d\n", split);
    ll sum = 0;
    for (int x=0; x<width; x++)
        sum += count[height-1][x];
    printf("part 2: %lld\n", sum);
}
