#include "dictutils.h"
/*************************************************************************/
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
    if (temp != NULL && temp->is_word == 1)
    {
        return 1;
    }

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
    if (temp->is_word == 1)
    {
        printf("%s\n", a);
    }
    listall(temp->child);
    a[strlen(a) - 1] = '\0';
    listall(temp->sibling);
}

/************************************************************************/

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
        trieinsert(root, word);
    }
    fclose(ptr);
    return root;
}

/************************************************************************/
// Swap two strings
void swap(char *x, char *y)
{
    char temp;
    temp = *x;
    *x = *y;
    *y = temp;
}
// Compare two strings
int compare(const void *a, const void *b)
{
    return strcmp(*(const char **)a, *(const char **)b);
}
// The function should return a single string consisting of all single letters that can be added before S to obtain valid English words.
char *addbefore(dict D, char *S)
{
    // listall(D.root);
    char *characters = (char *)malloc(sizeof(char) * 26);
    characters[0] = '\0';
    int j = 0;
    for (int i = 'a'; i < 'z'; i++)
    {
        char temp[strlen(S) + 1];
        char c = i;
        temp[0] = c;
        strcat(temp, S);
        // printf("%s\n", temp);
        char *word = temp;
        // Search for the word in the trie
        int flag = triesearch(D.root, word);
        // printf("%d\n", flag);
        // If the word is found in the trie
        if (flag == 1)
        {
            characters[j] = c;
            characters[j + 1] = '\0';
            j++;
        }
    }
    // printf("%d", strlen(characters));
    // If no characters can be added before S to obtain valid English words
    if (strlen(characters) == 0)
    {
        printf("No characters can be added before \"%s\" to obtain valid English words.\n", S);
        return characters;
    }
    return characters;
}

// The function should return a single string consisting of all single letters that can be added after S to obtain valid English words.
char *addafter(dict D, char *S)
{
    // listall(D.root);
    char *characters = (char *)malloc(sizeof(char) * 26);
    characters[0] = '\0';
    int j = 0;
    for (int i = 'a'; i < 'z'; i++)
    {
        char temp[strlen(S) + 1];
        char c = i;
        strcpy(temp, S);
        strncat(temp, &c, 1);
        // printf("%s\n", temp);
        char *word = temp;
        // Search for the word in the trie
        int flag = triesearch(D.root, word);
        // printf("%d\n", flag);
        // If the word is found in the trie
        if (flag == 1)
        {
            characters[j] = c;
            characters[j + 1] = '\0';
            j++;
        }
    }
    // printf("%d", strlen(characters));
    // If no characters can be added before S to obtain valid English words
    if (strlen(characters) == 0)
    {
        printf("No characters can be added before \"%s\" to obtain valid English words.\n", S);
        return characters;
    }
    return characters;
}
// The function returns a dynamically allocated array of all permutations of S, that are valid Englishwords according to the dictionary D

// Driver code
int main()
{
    dict D;
    D.root = NULL;
    D.root = newNode('\0');
    D.root = loadaddfltdict(D.root);
    // listall(D.root);
    char *S = "ball";
    char *characters = addafter(D, S);
    printf("%s", characters);
    return 0;
}