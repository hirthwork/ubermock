lib:
	g++ -shared lib.cpp -o liblib.so -O3

mock:
	g++ -ansi -pedantic-errors -Werror -Wall -Wextra -I/home/dpotapov/dev/reinvented-wheels/ubermock -shared ../symbolloader.cpp -O3 -o libmock.so

exe: mock lib
	g++ -ansi -pedantic-errors -Werror -Wall -Wextra -I/home/dpotapov/dev/reinvented-wheels/ubermock mock.cpp -lmock -lbacktracexx -O3 -llib -L.

all: exe lib
	LD_LIBRARY_PATH=. ./a.out
