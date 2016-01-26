libcio.so : cio.c cio.h
	gcc -c -fPIC cio.c -o cio.o
	gcc -shared -Wall -o libcio.so cio.o
	
.PHONYOBJ : cleanobj
cleanobj:
	rm *.o

.PHONY : clean
clean:
	rm libcio.so *.o
