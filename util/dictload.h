#include "dictutils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DFLT_DICT "../dict/word.txt"
//Function to load default dictionary
trienode* loadaddfltdict(trienode *root);
// Function to load a dictionary into a trie
trienode* loaddict(char *filename, trienode *root);
