//Makefile
libutil.so: dictutils.o dictload.o
	gcc -shared -o libutil.so dictutils.o dictload.o -L../trie -ltrie
dictutils.o: dictutils.c dictutils.h
	gcc -c -fPIC dictutils.c
dictload.o: dictload.c dictload.h
	gcc -c -fPIC dictload.c
