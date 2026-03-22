CFLAG =-Wall -std=c99 -o

src = $(wildcard *.c)
bin = $(src:%.c=%)

all : clean $(bin)

clean:
	rm -rf a_star bfs connexe

%: %.c moteur.o
	gcc $(CFLAG) $@ $^