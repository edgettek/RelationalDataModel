#
# File: Makefile
# Creator: George Ferguson
# Created: Thu Jun 30 11:00:49 2016
# Time-stamp: <Wed Sep  7 18:01:09 EDT 2016 ferguson>
#

CC=gcc
CFLAGS=-g3 -I.
DEPS = attributes.h
OBJ = csg.c snap.c cdh.c cp.c cr.c main.c part2.c part3.c algebra.c

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

output: $(OBJ)
	gcc -o $@ $^ $(CFLAGS)