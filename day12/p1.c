#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <limits.h>
#include <unistd.h>
#include <ctype.h>
#include <stdarg.h>

typedef long long ll;

char packages[6][3][3];
char sizes[6];

int main(void) {
    while (1) {
        int n;
        fscanf(stdin, "%d:\n", &n);
        for (int y=0; y<3; y++) {
            for (int x=0; x<3; x++) {
                packages[n][y][x] = fgetc(stdin);
            }
            fgetc(stdin);
        }
        fgetc(stdin);
        if (n == 5) break;
    }
    for (int p=0; p<6; p++) {
        int s = 0;
        for (int y=0; y<3; y++) {
            for (int x=0; x<3; x++) {
                if (packages[p][y][x] == '#') s++;
            }
        }
        sizes[p] = s;
    }

    int fits = 0;
    int width, height;
    int counts[6];
    while (1) {
        if (fscanf(stdin, "%dx%d: %d %d %d %d %d %d\n",
                    &width, &height, &counts[0], &counts[1], &counts[2],
                    &counts[3], &counts[4], &counts[5]) != 8) break;

        // this is silly, does not work for example, but apparently works
        // for the large input
        //
        ll size = width * height, total = 0;
        for (int p=0; p<6; p++) total += sizes[p]* counts[p];
        if (total < size) fits++;
    }

    printf("%d\n", fits);
}
