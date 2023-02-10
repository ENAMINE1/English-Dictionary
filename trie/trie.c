#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure of trie node
struct node
{
    char alphabet;
    struct node *child;
    struct node *sibling;
    int is_word;
};

// Function to create a new node
struct node *newNode(char alphabet)
{
    struct node *temp = (struct node *)malloc(sizeof(struct node));
    temp->alphabet = alphabet;
    temp->child = NULL;
    temp->sibling = NULL;
    temp->is_word = 0;
    return temp;
}

// Function to insert a word in trie
void insert(struct node *root, char *word)
{
    // If trie is empty
    struct node *temp = root;
    // If root is NULL, create a node and make it root
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
            // Traverse the child nodes
            temp = temp->child;
            // If current character is not present as sibling
            while (temp->sibling != NULL)
            {
                // If current character is present as sibling
                if (temp->alphabet == word[i])
                    break;
                // Else traverse the sibling nodes
                temp = temp->sibling;
            }
            // If current character is not present as sibling
            if (temp->alphabet != word[i])
            {
                // Create a new node and make it sibling of last child
                temp->sibling = newNode(word[i]);
                temp = temp->sibling;
            }
        }
        i++;
    }
    temp->is_word = 1;
}

// Function to search a word in trie
int search(struct node *root, char *word)
{
    // If trie is empty
    if (root == NULL)
        return 0;
    struct node *temp = root->child;
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
void print(struct node *root)
{
    if (root == NULL)
        return;
    struct node *temp = root;
    // while (temp != NULL)
    static char a[100];
    // {
    //     printf("%c", temp->alphabet);
    //     print(temp->child);
    //     print(temp->sibling);
    // }
    a[strlen(a)] = temp->alphabet;
    // printf("%d \n", strlen(a));
    if (temp->is_word == 1)
    {
        printf("%s\n", a);
    }
    print(temp->child);
    a[strlen(a) - 1] = '\0';
    // printf("%s\n", a);

    print(temp->sibling);
}

// Driver program to test above functions
int main()
{
    struct node *root = NULL;
    root = newNode('\0');
    insert(root, "hello");
    insert(root, "world");
    insert(root, "hell");
    insert(root, "word");
    insert(root, "hi");
    insert(root, "bye");
    print(root);
    printf("%d ", search(root, "hello"));
    printf("%d ", search(root, "world"));
    printf("%d ", search(root, "hell"));
    printf("%d ", search(root, "word"));
    printf("%d ", search(root, "hi"));
    printf("%d ", search(root, "bye"));
    printf("%d ", search(root, "he"));
    printf("%d ", search(root, "wor"));
    printf("%d ", search(root, "hel"));
    printf("%d ", search(root, "worl"));
    printf("%d ", search(root, "h"));
    printf("%d ", search(root, "b"));
    return 0;
}
