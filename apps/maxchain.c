#include "../util/wordutils.h"
// #include"../trie/trie.c"
// #include"../util/dictutils.c"
trienode *loadaddfltdict(trienode *root)
{
    FILE *ptr;
    char *word;
    word = (char *)malloc(100 * sizeof(char));
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
/***************************************************************************************************/

typedef struct nod
{
    int l;
    char *choice;
} new;
new recur(dict d, char *str)
{
    int len = strlen(str);

    char *a;
    a = (char *)malloc(100 * sizeof(char));
    a = addafter(d, str);
    char *b;
    b = (char *)malloc(100 * sizeof(char));
    b= addbefore(d, str);
    new n;
    new c;
    // Gives the length of the longest chain of valid words that can be obtained by adding single letters to the beginning or end of words
    n.choice = (char *)malloc(3 * sizeof(char));
    n.choice[2] = '\0';
    // base case when no characters can be added before or after the string to obtain valid English words
    if (strcmp(a, "") == 0 && strcmp(b, "") == 0)
    {
        n.l = 0;
        n.choice[0] = 'x';
        n.choice[1] = 'y';
        return n;
    }
    // if no characters can be added before the string to obtain valid English words
    int max = 0;
    int curr = 0;
    char *temp = NULL;
    if (strcmp(a, "") != 0)
    {
        temp = (char *)malloc((len + 2) * sizeof(char));
        strcpy(temp, str);
        temp[len + 1] = '\0';
        for (int i = 0; i < strlen(a); i++)
        {
            temp[len] = a[i];
            c = recur(d, temp);
            curr = 1 + c.l;
            if (curr > max)
            {
                n.l = curr;
                n.choice[1] = '1';
                n.choice[0] = a[i];
                max = curr;
            }
            free(c.choice);
        }
    }
    free(temp);
    temp = NULL;
    if (strcmp(b, "") != 0)
    {
        temp = (char *)malloc((len + 2) * sizeof(char));
        strcpy(temp + 1, str);
        for (int i = 0; i < strlen(b); i++)
        {
            temp[0] = b[i];
            c = recur(d, temp);
            curr = 1 + c.l;
            if (curr > max)
            {
                n.l = curr;
                n.choice[1] = '2';
                n.choice[0] = b[i];
                max = curr;
            }
            free(c.choice);
        }
    }
    free(temp);
    return n;
}
void print(dict d, char *str)
{
    printf("%s\n", str);
    int len = strlen(str);
    new temp = recur(d, str);
    if (temp.l == 0)
    {
        return;
    }
    char *buff = (char *)malloc((len + 2) * sizeof(char));
    if (temp.choice[1] == '1')
    {
        strcpy(buff, str);
        buff[len + 1] = '\0';
        buff[len] = temp.choice[0];
        print(d, buff);
    }
    else
    {
        strcpy(buff + 1, str);
        buff[0] = temp.choice[0];
        print(d, buff);
    }
    free(buff);
    free(temp.choice);
}

int main()
{
    dict D;
    D.root = newNode('\0');
    D.root = loadaddfltdict(D.root);
    // char S[] = "ello";
    // // maxchain(D, S);
    // char str[] = "s";
    printf("Enter the string: ");
    char *str = (char *)malloc(100 * sizeof(char));
    scanf("%s", str);
    print(D, str);
    return 0;
}
