#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <limits.h>
#include <unistd.h>
#include <float.h>

int nboxes;
struct coor {
    int x, y, z;
    int circuit;
    bool con;
} boxes[1000];
double dists[1000*1000];
int circuits[1000];

static double distance(int i, int j) {
    if (!dists[i*1000+j]) {
        struct coor *a = &boxes[i], *b = &boxes[j];
        double dx = abs(a->x-b->x);
        double dy = abs(a->y-b->y);
        double dz = abs(a->z-b->z);
        double dist = dx*dx + dy*dy + dz*dz;    // omit sqrt for speed
        dists[i*1000+j]= dist;
    }
    return dists[i*1000+j];
}

int main(void) {
    int x, y, z;

    while (fscanf(stdin, "%d,%d,%d\n", &x, &y, &z) == 3) {
        boxes[nboxes].x = x;
        boxes[nboxes].y = y;
        boxes[nboxes].z = z;
        boxes[nboxes].circuit = nboxes;     // id them
        nboxes++;
    }

    double prev_smallest = 0;
    int s1, s2;
    while (1) {
        double smallest = DBL_MAX;
        s1=0, s2=1;
        for (int i=0; i<nboxes; i++) {
            for (int j=i+1; j<nboxes; j++) {
                double sd;
                if ((sd = distance(i, j)) < smallest) {
                    if (sd <= prev_smallest) continue;
                    s1 = i;
                    s2 = j;
                    smallest = sd;
                }
            }
        }
        if (boxes[s1].circuit == boxes[s2].circuit) {
            // same circuit already, do nothing
        } else if (boxes[s1].con) {
            int save = boxes[s2].circuit;
            boxes[s2].circuit = boxes[s1].circuit;
            if (boxes[s2].con) {
                for (int i=0; i<nboxes; i++) {
                    if (boxes[i].circuit == save) {
                        boxes[i].circuit = boxes[s2].circuit;
                    }
                }
            } else {
                boxes[s2].con = true;
            }
        } else {
            boxes[s1].circuit = boxes[s2].circuit;
            boxes[s1].con = boxes[s2].con = true;
        }
        prev_smallest = smallest;

        int f;
        for (f=1; f<nboxes; f++)
            if (boxes[0].circuit != boxes[f].circuit) break;
        if (f == nboxes) break;
    }

    printf("%lld\n", (long long) boxes[s1].x * (long long) boxes[s2].x);
}
