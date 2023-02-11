#include"dicttype.h"
#define DFLT_DICT "../dict/word.txt"
//Function to load default dictionary
trienode* loadaddfltdict(trienode *root);
// Function to load a dictionary into a trie
trienode* loaddict(char *filename, trienode *root);