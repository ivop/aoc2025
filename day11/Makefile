CFLAGS=-O0 -g3 -march=native -Wall -Wextra

all: both

%: %.c
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f both *~
