LDLIBS = -lyaml

all: main

main: main.o types.o parser.o

types.o: types.c parser.h

parser.o: parser.c

main.o: main.c parser.h main.h

parser.c parser.h: parser.y
	lemon $^

.PHONY: clean
clean:
	rm -f main parser.c parser.h parser.out parser.o types.o main.o
