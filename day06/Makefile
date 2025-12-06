CFLAGS=-O0 -g3 -march=native -Wall -Wextra

all: p1 p2

%: %.c
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f p1 p2 *~
