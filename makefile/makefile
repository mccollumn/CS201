
hello: hello.o printName.o 
	gcc -m32 -std=gnu99 hello.o printName.o -o hello

hello.o: hello.c printName.h 
	gcc -c -m32 -std=gnu99 hello.c

printName.o: printName.c printName.h
	gcc -c -m32 -std=gnu99 printName.c

clean:
	rm *.o 
