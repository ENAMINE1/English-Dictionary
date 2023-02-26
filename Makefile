#Makefile for Assignment 2
assignment: app clean
app:
	cd apps; make apps
clean:
	cd trie;rm -f *.o *.so
	cd apps; make clean
	cd util;rm -f *.o *.so
