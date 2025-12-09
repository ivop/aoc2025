#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <limits.h>
#include <unistd.h>

typedef long long ll;

ll min(ll a, ll b) {
   return (a<b) ? a : b;
}
ll max(ll a, ll b) {
    return (a>b) ? a : b;
}

struct coor {
    ll x,y;
};

int ntiles;
struct coor *red;

ll calc_area(int i, int j) {
    ll dx = llabs(red[i].x - red[j].x) + 1;
    ll dy = llabs(red[i].y - red[j].y) + 1;
    return dx*dy;
}

bool is_inside_polygon(ll xmin, ll ymin, ll xmax, ll ymax) {
    for (int i=0; i<ntiles; i++) {
        ll x1 = red[i].x;
        ll y1 = red[i].y;
        ll x2 = red[i+1].x;
        ll y2 = red[i+1].y;

        if (y1 == y2) {
            if (ymin < y1 && y1 < ymax &&
                    ((min(x1,x2) <= xmin && xmin < max(x1,x2)) ||
                     (min(x1,x2) < xmax && xmax <= max(x1,x2)))) {
                return false;
            }
        } else if (x1 == x2) {
            if (xmin < x1 && x1 < xmax &&
                    ((min(y1,y2) <= ymin && ymin < max(y1,y2)) ||
                     (min(y1,y2) < ymax && ymax <= max(y1,y2)))) {
                return false;
            }
        } else {
            puts("shouldn't happen");
            exit(1);
        }
    }
    return true;
}

int main(void) {
    ll x, y;

    while (fscanf(stdin, "%lld,%lld\n", &x, &y) == 2) {
        ntiles++;
        red = realloc(red, ntiles * sizeof(struct coor));
        red[ntiles-1].x = x;
        red[ntiles-1].y = y;
    }

    ll largest = 0;;
    for (int i=0; i<ntiles; i++) {
        for (int j=i+1; j<ntiles; j++) {
            ll area = calc_area(i, j);
            if (area > largest) {
                largest = area;
            }
        }
    }

    printf("part 1: %lld\n", largest);

    red = realloc(red, (ntiles+1) * sizeof(struct coor));
    red[ntiles].x = red[0].x; // duplicate start point at end
    red[ntiles].y = red[0].y; // for convenience

    largest = 0;;
    for (int i=0; i<ntiles; i++) {
        for (int j=i+1; j<ntiles; j++) {
            ll x1 = red[i].x;
            ll y1 = red[i].y;
            ll x2 = red[j].x;
            ll y2 = red[j].y;

            if (is_inside_polygon(min(x1,x2), min(y1,y2),
                                  max(x1,x2), max(y1,y2))) {

                ll area = calc_area(i, j);
                if (area > largest) largest = area;
            }
        }
    }

    printf("part 2: %lld\n", largest);
}
