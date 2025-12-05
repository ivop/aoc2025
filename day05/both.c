#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <limits.h>
#include <unistd.h>

char *line;
size_t n;

struct range {
    long long a, b;
};

unsigned nranges;
struct range ranges[500];

bool x_in_range_yz(long long x, long long y, long long z) {
    if (x >= y && x <= z) return true;
    return false;
}

int main(void) {
    while (getline(&line, &n, stdin) > 0) {
        if (line[0] == '\n') break;
        ranges[nranges].a = strtoll(line, NULL, 10);
        ranges[nranges].b = strtoll(strchr(line, '-')+1, NULL, 10);
        nranges++;
    }
    long long cnt = 0;
    while (getline(&line, &n, stdin) > 0) {
        long long v = strtoll(line, NULL, 10);
        for (unsigned i=0; i<nranges; i++) {
            if (v >= ranges[i].a && v <= ranges[i].b) {
                cnt++;
                break;
            }
        }
    }
    printf("part 1: %lld\n", cnt);
    bool merged;
    do {
        merged = false;
        for (unsigned i=0; i<nranges; i++) {
            for (unsigned j=0; j<nranges; j++) {
                if (i==j) continue;
                long long a = ranges[i].a;
                long long b = ranges[i].b;
                long long c = ranges[j].a;
                long long d = ranges[j].b;

                if (a == -1 || c == -1) continue;

                if (x_in_range_yz(c,a,b) && x_in_range_yz(d,a,b) &&
                    x_in_range_yz(d,a,b) && x_in_range_yz(d,a,b)) {
                    ranges[j].a = ranges[j].b = -1;
                    merged = true;
                    continue;
                }
                if (a < c && x_in_range_yz(b,c,d)) {
                    ranges[j].a = ranges[j].b = -1;
                    ranges[i].b = d;
                    merged = true;
                    continue;
                }
                if (x_in_range_yz(a,c,d) && b > d) {
                    ranges[j].a = ranges[j].b = -1;
                    ranges[i].a = c;
                    merged = true;
                    continue;
                }
            }
        }
    } while (merged);
    cnt = 0;
    for (unsigned i=0; i<nranges; i++) {
        if (ranges[i].a == -1) continue;
        cnt += ranges[i].b - ranges[i].a + 1;
    }
    printf("part 2: %lld\n", cnt);
}
