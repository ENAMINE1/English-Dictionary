#include "dictload.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../trie/trie.c"

/********************************************************************/
trienode *loadaddfltdict(trienode *root)
{
    FILE *ptr;
    char *word;
    // Open the file
    ptr = fopen(DFLT_DICT, "r");

    // check if file is empty
    if (ptr == NULL)
    {
        printf("File is empty!!\n");
        return NULL;
    }
    // Read the file
    while (fscanf(ptr, "%s", word) != EOF)
    {
        // printf("%s\n", word);
        trieinsert(root, word);
        // listall(root);
    }
    fclose(ptr);
    return root;
}

// Function to load any dictonary
trienode *loaddict(char *filename, trienode *root)
{
    FILE *ptr;
    char *word;
    // Open the file
    ptr = fopen(filename, "r");

    // check if file is empty
    if (ptr == NULL)
    {
        printf("File is empty!!\n");
        return NULL;
    }
    // Read the file
    while (fscanf(ptr, "%s", word) != EOF)
    {
        trieinsert(root, word);
    }
    fclose(ptr);
    return root;
}

// Driver code
// Driver code
// Driver code
// int main()
// {
//     // Create a trie
//     dict d, d2;
//     // d.root = NULL;
//     // d2.root = NULL;
//     d.root = newNode('\0');
//     d2.root = newNode('\0');
//     d.root = loadaddfltdict(d.root);
//     // address of learning gir.txt
//     // loaddict("C:\\Users\\kshas\\OneDrive\\Desktop\\learning git.txt", d2.root);
//     listall(d.root);
//     // listall(d2.root);
//     // printf("%d", triesearch(d.root, "pirate"));
//     return 0;
// }