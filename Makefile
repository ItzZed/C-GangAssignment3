# Authors: Zachary Bell, Gian Cua, Scott Weaver, Thomas Schuster
# Lab Instructor’s Name: Ardalan Rahmatidehkordi
# Lecture Instructor’s Name: Abdullah Mohiuddin, Ardalan Rahmatidehkordi

CC= gcc
CFLAGS= -Wall -g -ansi -std=c99
LDLIBS= -lm

all: DB_impl.o DB.o test_import

DB_impl.o: DB_impl.c DB_impl.h
	$(CC) $(CFLAGS) -c $< -o $@ $(LDLIBS)

DB.o: DB.c DB.h
	$(CC) $(CFLAGS) -c $< -o $@ $(LDLIBS)

test_import: test_import.c DB_impl.o DB.o 
	$(CC) $(CFLAGS) $< DB.o DB_impl.o -o $@ $(LDLIBS)

clean:
	rm test_import *.o