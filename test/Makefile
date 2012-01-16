lib:
	g++ -shared lib.cpp -o liblib.so

exe: lib
	g++ -ansi -pedantic-errors -Werror -Wall -Wextra -I/home/dpotapov/dev/reinvented-wheels/ubermock ../symbolloader.cpp mock.cpp -ggdb -lbacktracexx -fmax-errors=4 -llib -L.

all: exe lib
	LD_LIBRARY_PATH=. ./a.out
