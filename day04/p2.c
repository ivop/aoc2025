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
    int answer = 0;
    bool removed;
  do {
    removed = false;
    for (int y=0; y<height; y++) {
        for (int x=0; x<width; x++) {
            if (lines[y][x] == '.') continue;
            int cnt = 0;
            if (y>0) {
                if (x>0       && lines[y-1][x-1] == '@') cnt++;
                if (             lines[y-1][x+0] == '@') cnt++;
                if (x<width-1 && lines[y-1][x+1] == '@') cnt++;
            }
            if (x>0       && lines[y][x-1] == '@') cnt++;
            if (x<width-1 && lines[y][x+1] == '@') cnt++;
            if (y<width-1) {
                if (x>0       && lines[y+1][x-1] == '@') cnt++;
                if (             lines[y+1][x+0] == '@') cnt++;
                if (x<width-1 && lines[y+1][x+1] == '@') cnt++;
            }
            if (cnt < 4) {
                answer++;
                lines[y][x] = '.';
                removed = true;
            }
        }
    }
  } while (removed);
    printf("%d\n", answer);
}
