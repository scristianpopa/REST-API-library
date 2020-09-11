CC=gcc
CFLAGS=-I.

client: client.c requests.c helpers.c buffer.c parson.c
	$(CC) -o client client.c requests.c helpers.c buffer.c parson.c -Wall

run: client
	./client

clean:
	rm -f *.o client

pack:
	zip -rFS Popa_StefanCristian_321CA_Tema3PC.zip *.c *.h README Makefile
