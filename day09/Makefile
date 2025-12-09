#CFLAGS=-O0 -g3 -march=native -Wall -Wextra
CFLAGS=-O3 -march=native -Wall -Wextra -flto

all: both

%: %.c
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f both *~
