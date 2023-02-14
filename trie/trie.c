// #include"trie.h"

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

//Function to create a new trie
trie *trieinit()
{
    trie *temp = (trie *)malloc(sizeof(trie));
    temp->root == NULL;
    temp->root = newNode('\0');
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

//Function to triesearch a word in trie
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
        if (temp == NULL)
        {
            return 0;
        }
    }
    // If current character is end of word mark it as leaf node
    if (temp->is_word == 1)
        return 1;
    return 0;
}

// print the trie
void listall(trienode*root)
{
    if (root == NULL)
        return;
    trienode *temp = root;
    // while (temp != NULL)
    static char a[100];
    a[strlen(a)] = temp->alphabet;
    //printf("%d", strlen(a));
    //printf("%c\t", temp->alphabet);
    if (temp->is_word == 1)
    {
        printf("%s\n", a);
    }
    listall(temp->child);
    a[strlen(a) - 1] = '\0';
    listall(temp->sibling);
}

//Driver program to test above functions


// int main()
// {
//     trie *t = trieinit();
//     trieinsert(t->root, "hello");
//     trieinsert(t->root, "world");
//     trieinsert(t->root, "hell");
//     trieinsert(t->root, "word");
//     trieinsert(t->root, "hi");
//     trieinsert(t->root, "bye");
//     trieinsert(t->root, "he");
//     trieinsert(t->root, "wor");
//     trieinsert(t->root, "hel");
//     trieinsert(t->root, "worl");
//     trieinsert(t->root, "h");

//     listall(t->root);
//     printf("%d ", triesearch(t->root, "hello"));
//     printf("%d ", triesearch(t->root, "world"));
//     printf("%d ", triesearch(t->root, "aell"));
//     printf("%d ", triesearch(t->root, "word"));
//     printf("%d ", triesearch(t->root, "hi"));
//     printf("%d ", triesearch(t->root, "bye"));
//     printf("%d ", triesearch(t->root, "he"));
//     printf("%d ", triesearch(t->root, "wor"));
//     printf("%d ", triesearch(t->root, "hel"));
//     printf("%d ", triesearch(t->root, "worl"));
//     printf("%d ", triesearch(t->root, "h"));
//     printf("%d ", triesearch(t->root, "b"));
//     return 0;
// }
