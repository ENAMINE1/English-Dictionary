#include "dictload.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// #include"../trie/trie.c"
/********************************************************************/
// Function to create a new node
trienode *newNode(char alphabet)
{
    trienode *temp = (trienode *)malloc(sizeof(trienode));
    temp->alphabet = alphabet;
    temp->child = NULL;
    temp->sibling = NULL;
    temp->is_word = 0;
    return temp;
}

// Function to trieinsert a word in trie
void trieinsert(trienode *root, char *word)
{
    // If trie is empty
    struct node *temp = root;
    int i = 0;
    // Traverse the trie with the given word
    while (word[i] != '\0')
    {
        // If current character of word is not present
        if (temp->child == NULL)
        {
            // Create a node and make it child of root
            temp->child = newNode(word[i]);
            // temp->child->sibling = NULL;
            temp = temp->child;
            // temp->is word = 0;
        }
        // If current character is present as child
        else
        {
            if (word[i] < temp->child->alphabet)
            {
                struct node *temp1 = newNode(word[i]);
                temp1->sibling = temp->child;
                temp->child = temp1;
                temp = temp->child;
            }
            else if (word[i] == temp->child->alphabet)
            {
                temp = temp->child;
            }
            else
            {
                // If current character is present as sibling
                trienode *temp1 = temp->child;
                // Traverse the sibling nodes
                while (temp1->sibling != NULL && temp1->sibling->alphabet < word[i])
                {
                    temp1 = temp1->sibling;
                }
                // If current character is not present as sibling
                if (temp1->sibling == NULL)
                {
                    temp1->sibling = newNode(word[i]);
                    temp = temp1->sibling;
                }
                // If current character is present as sibling
                else if (temp1->sibling->alphabet == word[i])
                {
                    temp = temp1->sibling;
                }
                // If current character is present as sibling
                else
                {
                    trienode *temp2 = newNode(word[i]);
                    temp2->sibling = temp1->sibling;
                    temp1->sibling = temp2;
                    temp = temp1->sibling;
                }
            }
        }
        i++;
    }
    temp->is_word = 1;
}

// Function to triesearch a word in trie
int triesearch(trienode *root, const char *word)
{
    // If trie is empty
    if (root == NULL)
        return 0;
    trienode *temp = root->child;
    int i = 0;
    // Traverse the trie with the given word
    while (word[i] != '\0' && temp != NULL)
    {

        // If current character of word is present as child
        if (temp->alphabet == word[i])
        {
            // Traverse the child nodes
            // printf("%c", temp->alphabet);
            i++;
            if (i == strlen(word))
            {
                break;
            }
            temp = temp->child;
        }
        // If current character is present as sibling
        else
        {
            // Traverse the sibling nodes
            temp = temp->sibling;
        }
    }
    // If current character is end of word mark it as leaf node
    if (temp->is_word == 1)
        return 1;
    return 0;
}

// print the trie
void listall(trienode *root)
{
    if (root == NULL)
        return;
    trienode *temp = root;
    // while (temp != NULL)
    static char a[100];
    a[strlen(a)] = temp->alphabet;
    // printf("%d", strlen(a));
    // printf("%c\t", temp->alphabet);
    if (temp->is_word == 1)
    {
        printf("%s\n", a);
    }
    listall(temp->child);
    a[strlen(a) - 1] = '\0';
    listall(temp->sibling);
}

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
// int main()
// {
//     // Create a trie
//     dict d, d2;
//     d.root = NULL;
//     d2.root = NULL;
//     d.root = newNode('\0');
//     d2.root = newNode('\0');
//     d.root = loadaddfltdict(d.root);
//     //address of learning gir.txt
//     //loaddict("C:\\Users\\kshas\\OneDrive\\Desktop\\learning git.txt", d2.root);
//     //listall(d.root);
//     //listall(d2.root);
//     printf("%d", triesearch(d.root, "well"));
//     return 0;
// }