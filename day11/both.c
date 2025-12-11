#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <limits.h>
#include <unistd.h>

#define MAX (26*26*26)
#define C2I(x) ((x)-'a')
#define YOU (C2I('y')*26*26 + C2I('o')*26 + C2I('u'))
#define OUT (C2I('o')*26*26 + C2I('u')*26 + C2I('t'))
#define SVR (C2I('s')*26*26 + C2I('v')*26 + C2I('r'))
#define DAC (C2I('d')*26*26 + C2I('a')*26 + C2I('c'))
#define FFT (C2I('f')*26*26 + C2I('f')*26 + C2I('t'))

int conn[MAX][32];
long long cache[MAX][2][2];

static int trav1(int pos) {
    if (pos == OUT) return 1;
    int cnt = 0;
    for (int i=0; conn[pos][i] != -1; i++)
        cnt += trav1(conn[pos][i]);
    return cnt;
}

static long long trav2(int pos, bool dac, bool fft) {
    if (cache[pos][dac][fft] >= 0) return cache[pos][dac][fft];
    if (pos == FFT) fft = true;
    if (pos == DAC) dac = true;
    if (pos == OUT) return dac & fft;
    long long cnt = 0;
    for (int i=0; conn[pos][i] != -1; i++)
        cnt += trav2(conn[pos][i], dac, fft);
    cache[pos][dac][fft] = cnt;
    return cnt;
}

int main(void) {
    memset(conn, -1, MAX*32*sizeof(int));
    memset(cache, -1, MAX*2*2*sizeof(long long));

    while (1) {
        int v = C2I(fgetc(stdin));
        if (v < 0) break;
        v *= 26;
        v += C2I(fgetc(stdin));
        v *= 26;
        v += C2I(fgetc(stdin));

        int c = fgetc(stdin);
        c = fgetc(stdin);
        if (c != ' ') {
            puts("error");
            return 1;
        }
        int i = 0;
        while (c != '\n') {
            int x = C2I(fgetc(stdin));
            x *= 26;
            x += C2I(fgetc(stdin));
            x *= 26;
            x += C2I(fgetc(stdin));
            conn[v][i] = x;
            i++;
            c = fgetc(stdin);
        }
    }

    printf("%d\n", trav1(YOU));
    printf("%lld\n", trav2(SVR, false, false));
}
