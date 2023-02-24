//Makefile for apps
apps: Maxchain Subwords
	
Maxchain:maxchain.c libtrie.so libutil.so
	gcc -o Maxchain maxchain.c -L../trie -L../util -ltrie -lutil
	./Maxchain
Subwords:subwords.c libtrie.so libutil.so
	gcc -o Subwords subwords.c -L../trie -L../util -ltrie -lutil
	./Subwords
libtrie.so:
	cd ../trie; make
libutil.so:
	cd ../util; make
