
CROSS_COMPILE=
CC = gcc

writer: writer.o
	$(CROSS_COMPILE)$(CC) writer.o -o writer
	
writer.o: writer.c
	$(CROSS_COMPILE)$(CC) -c writer.c
clean:
	rm *.o writer
