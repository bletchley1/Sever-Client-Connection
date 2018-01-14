server: server.o createFIFO.o
	gcc -o server server.o createFIFO.o

server.o: server.c headers.h request.h result.h decl.h
	gcc -c server.c

createFIFO.o: createFIFO.c headers.h decl.h
	gcc -c createFIFO.c	

clean:
	rm *.o 
	rm server
