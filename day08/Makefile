CFLAGS=-O3 -march=native -Wall -Wextra -flto

all: p1 p2

%: %.c
	$(CC) $(CFLAGS) -o $@ $^ -lm

clean:
	rm -f p1 p2 *~
