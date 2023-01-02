app.exe: main.o task.o
	gcc -o app.exe main.o task.o

test.exe: test.o task.o
	gcc -o test.exe test.o task.o

main.o: main.c header.h
	gcc -std=c99 -Wall -Werror -c main.c

task.o: task.c header.h
	gcc -std=c99 -Wall -Werror -c task.c

test.o: test.c header.h
	gcc -std=c99 -Wall -Werror -c test.c

clean:
	rm *.o *.exe