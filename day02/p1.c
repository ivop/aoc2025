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
    if (n&1) return false;
    return memcmp(id, id+n/2, n/2) == 0;
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
