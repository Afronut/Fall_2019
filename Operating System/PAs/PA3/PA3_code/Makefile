CC = gcc
CFLAGS = -c -g -Wall -Wextra
LFLAGS = -pthread -Wall -Wextra

.PHONY: all clean

all: multi_lookup

multi_lookup: multi_lookup.o list.o util.o service.o sync.o
	$(CC) $(LFLAGS) $^ -o $@

list.o: list.c list.h
	$(CC) $(CFLAGS) $<
sync.o: sync.c sync.h
	$(CC) $(CFLAGS) $<
service.o: service.c service.h
	$(CC) $(CFLAGS) $<

util.o: util.c util.h
	$(CC) $(CFLAGS) $<

multi-lookup.o: multi_lookup.c
	$(CC) $(CFLAGS) $<

clean:
	echo "Cleaning up"
	rm -f *.o
	rm -f *~

purge:
	rm -f multi_lookup
	rm -f *.txt
