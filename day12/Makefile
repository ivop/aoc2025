CFLAGS=-O0 -g3 -march=native -Wall -Wextra
#CFLAGS=-O3 -march=native -Wall -Wextra -flto

all: p1 #p2

%: %.c
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f p1 p2 *~
