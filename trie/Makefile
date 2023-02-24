//Makefile for trie
libtrie.so: trie.o
	gcc -shared -o libtrie.so trie.o
trie.o: trie.c trie.h
	gcc -c -fPIC trie.c
