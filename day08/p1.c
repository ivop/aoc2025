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
} boxes[10000];

int circuits[10000];

static double distance(struct coor *a, struct coor *b) {
    double dx = abs(a->x-b->x);
    double dy = abs(a->y-b->y);
    double dz = abs(a->z-b->z);
    return sqrt(dx*dx + dy*dy + dz*dz);
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
    for (int k=0; k<1000; k++) {
        double smallest = DBL_MAX;
        int s1=0, s2=1;
        for (int i=0; i<nboxes; i++) {
            for (int j=i+1; j<nboxes; j++) {
                double sd;
                if ((sd = distance(&boxes[i], &boxes[j])) < smallest) {
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
    }

    for (int i=0; i<nboxes; i++)
        circuits[boxes[i].circuit]++;

    int largest, largest2, largest3;
    largest = largest2 = largest3 = 0;
    for (int i=0; i<nboxes; i++)
        if (circuits[i] > largest) largest = circuits[i];
    for (int i=0; i<nboxes; i++)
        if (circuits[i] > largest2 && circuits[i] < largest)
            largest2 = circuits[i];
    for (int i=0; i<nboxes; i++)
        if (circuits[i] > largest3 && circuits[i] < largest2)
            largest3 = circuits[i];

    int mul = largest * largest2 * largest3;
    printf("%d x %d x %d = %d\n", largest, largest2, largest3, mul);
}
