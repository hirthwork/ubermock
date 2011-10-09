GCC=gcc -ansi -pedantic-errors -fPIC -L. -Wl,-rpath=. -rdynamic
all: lib mock main test

lib:
	$(GCC) -shared -o liblib.so lib.c

mock: lib
	$(GCC) -ldl -llib -shared -o libmock.so mock.c

main: lib
	$(GCC) -llib -o main main.c

test: mock
	$(GCC) -lmock -o test test.c

