#include<stdlib.h>

// Structure of trie_node
typedef struct node
{
    char alphabet;
    struct node *child;
    struct node *sibling;
    int is_word;
} trienode;

// Structure of trie
typedef struct Trie
{
    trienode *root;
} trie;

// Function to create a new node
struct node *newNode(char);
// Function to trieinsert a word in trie
void trieinsert(struct node *root, char *word);
// Function to triesearch a word in trie
int triesearch(struct node *root, char *word);
// print the trie
void listall(struct node *root);