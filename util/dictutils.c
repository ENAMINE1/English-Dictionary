#include "dictutils.h"
#include "../trie/trie.c"
/*************************************************************************/

trienode *loadaddfltdict(trienode *root)
{
    FILE *ptr;
    char *word;
    word = (char *)malloc(sizeof(char) * 100);
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
        // printf("No characters can be added before \"%s\" to obtain valid English words.\n", S);
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
        // printf("No characters can be added after \"%s\" to obtain valid English words.\n", S);
        return characters;
    }
    return characters;
}
// The function returns a dynamically allocated array of all permutations of S, that are valid Englishwords according to the dictionary D

int compare(const void *a, const void *b)
{
    return (*(char *)a - *(char *)b);
}

// A utility function two swap two characters a and b
void swap(char *a, char *b)
{
    char t = *a;
    *a = *b;
    *b = t;
}

// This function finds the index of the smallest character
// which is greater than 'first' and is present in str[l..h]
int findCeil(char str[], char first, int l, int h)
{
    // initialize index of ceiling element
    int ceilIndex = l;

    // Now iterate through rest of the elements and find
    // the smallest character greater than 'first'
    for (int i = l + 1; i <= h; i++)
        if (str[i] > first && str[i] < str[ceilIndex])
            ceilIndex = i;

    return ceilIndex;
}

// Print all permutations of str in sorted order
char **sortedPermutations(dict D, char s[])
{
    // Dunamically allocating memory for stroring the valid strings
    char **ans = (char **)malloc(sizeof(char *));
    ans[0] = NULL;
    int ans_len = 1;

    // Get size of string and allocate memory for the string
    char str[strlen(s) + 1];
    for (int i = 0; i < strlen(s); i++)
    {
        str[i] = s[i];
    }
    str[strlen(s)] = '\0';
    // Get size of string
    int size = strlen(str);

    // Sort the string in increasing order
    qsort(str, size, sizeof(str[0]), compare);
    // printf("%s\n", str);

    // Print permutations one by one
    int isFinished = 0;

    while (!isFinished)
    {
        // print this permutation
        if (triesearch(D.root, str) == 1)
        {
            ans_len++;
            ans = realloc(ans, ans_len * sizeof(char *));
            char *temp = (char *)malloc((size + 1) * sizeof(str));
            strcpy(temp, str);
            ans[ans_len - 1] = temp;
            // printf("%s\t", ans[ans_len - 1]);
            // printf("%s\n", str);
        }

        // Find the rightmost character which is smaller than its next
        // character. Let us call it 'first char'
        int i;
        for (i = size - 2; i >= 0; --i)
            if (str[i] < str[i + 1])
                break;
        // If there is no such character, all are sorted in decreasing order,
        // means we just printed the last permutation and we are done.
        if (i == -1)
            isFinished = 1;
        else
        {
            // Find the ceil of 'first char' in right of first character.
            // Ceil of a character is the smallest character greater than it
            int ceilIndex = findCeil(str, str[i], i + 1, size - 1);
            // Swap first and second characters
            swap(&str[i], &str[ceilIndex]);

            // Sort the string on right of 'first char'
            qsort(str + i + 1, size - i - 1, sizeof(str[0]), compare);
            // printf("%s\n", str);
        }
    }
    ans[0] = ans[ans_len - 1];
    ans[ans_len - 1] = NULL;
    return ans;
}


// Driver code
// int main()
// {
//     dict D;
//     D.root = NULL;
//     D.root = newNode('\0');
//     D.root = loadaddfltdict(D.root);
//     // listall(D.root);

//     char S[] = "stop";
//     // printf("%d\t", triesearch(D.root, S));
//     char *characters = addbefore(D, S);
//     printf("%s\n", characters);

//     characters = addafter(D, S);
//     printf("%s", characters);

//     // sortedPermutations(D, S);
//     char **ans = sortedPermutations(D, S);
//     for (int i = 0; ans[i] != NULL; i++)
//     {
//         printf("%s\n", ans[i]);
//     }

//     return 0;
// }