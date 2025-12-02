#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <limits.h>
#include <unistd.h>

char *p, *q;
size_t n;
long long sum;

bool invalid(long long x) {
    char id[64];
    sprintf(id, "%lld", x);
    int n = strlen(id);
    if (!(n%2)) {
        if (memcmp(id, id+n/2, n/2) == 0) return true;
    }
    if (!(n%3)) {
        int m = n/3;
        if (memcmp(id, id+1*m, m) == 0 &&
            memcmp(id, id+2*m, m) == 0) return true;
    }
    if (!(n%5)) {
        int m = n/5;
        if (memcmp(id, id+1*m, m) == 0 &&
            memcmp(id, id+2*m, m) == 0 &&
            memcmp(id, id+3*m, m) == 0 &&
            memcmp(id, id+4*m, m) == 0) return true;
    }
    if (!(n%7)) {
        int m = n/7;
        if (memcmp(id, id+1*m, m) == 0 &&
            memcmp(id, id+2*m, m) == 0 &&
            memcmp(id, id+3*m, m) == 0 &&
            memcmp(id, id+4*m, m) == 0 &&
            memcmp(id, id+5*m, m) == 0 &&
            memcmp(id, id+6*m, m) == 0) return true;
    }
    return false;
}

int main(void) {
    getline(&p, &n, stdin);

    while (*p && *p != '\n') {
        long long v = strtoll(p, &q, 10);
        p = ++q;
        long long w = strtoll(p, &q, 10);
        p = ++q;
        for (long long x = v; x<=w; x++)
            if (invalid(x)) sum += x;
    }

    printf("%lld\n", sum);
}
