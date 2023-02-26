#Makefile for apps
apps: Maxchain Subwords

Maxchain:maxchain.c l1 l2
	gcc -o Maxchain maxchain.c -I../trie -I../util -L../trie -L../util -ltrie -lutil
	export LD_LIBRARY_PATH"=../trie:../util";./Maxchain
Subwords:subwords.c l1 l2
	gcc -o Subwords subwords.c -I../trie -I../util -L../trie -L../util -ltrie -lutil
	export LD_LIBRARY_PATH"=../trie:../util";./Subwords
l1:
	cd ../trie; make
l2:
	cd ../util; make
clean:
	rm -f Maxchain Subwords
