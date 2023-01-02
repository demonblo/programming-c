all: test.exe


string_func.o: string_func.c string_func.h
	gcc -std=c99 -Wall -Werror -pedantic -c string_func.c

my_snprintf.o: my_snprintf.c my_snprintf.h
	gcc -std=c99 -Wall -Werror -pedantic -c my_snprintf.c

test.o: test.c my_snprintf.h
	gcc -std=c99 -Wall -Werror -pedantic -c test.c

test.exe: test.o my_snprintf.o string_func.o my_snprintf.h
	gcc -o test.exe test.o my_snprintf.o string_func.o

clean:
	rm *.o *.exe