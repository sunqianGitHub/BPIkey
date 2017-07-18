CC = gcc
CFLAGS = -Wall -g -O0
LIB = -lmactoll_lltomac -L.
extractbpi:extractbpi.c
	    $(CC) $(CFLAGS) $^ -o $@ $(LIB)

clean:
	    $(RM)  extractbpi .*.sw?
