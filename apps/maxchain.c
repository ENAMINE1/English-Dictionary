// #include"../util/dictutils.h"
#include "../util/dictutils.c"
// #include "../trie/trie.c"

// finds the longest chain of valid words, that can be obtained by adding single letters to the beginning or end of words
void maxchain(dict D, char *S)
{
    static int flag = 1;
    // listall(D.root);
    int aa = 0;
    int bb = 0; 
    char *before = addbefore(D, S);
    char *after = addafter(D, S);
    // printf("S: %s\n", S);
    // printf("before: %s\n", before);
    // printf("after: %s\n", after);
    if (strlen(after) == 0 && strlen(before) == 0)
    {
        //printf("\n%d\n\n", flag);
        printf("\n");
        return;
    }

    // If no characters can be added before S to obtain valid English words
    if (strlen(before) != 0)
    {

        while (bb < strlen(before))
        {
            int len = strlen(S) + 2;
            char wordb[len];
            int size = sizeof(wordb);
            wordb[0] = before[bb];
            for (int i = 0; i < strlen(S); i++)
            {
                wordb[i + 1] = S[i];
            }

            wordb[len - 1] = '\0';
            char *temp = wordb;
            printf("==> %s\n", temp);
            flag++;
            maxchain(D, temp);
            flag--;
            bb++;
        }
    }
    // If no characters can be add after S to obtain valid English words
    if (strlen(after) != 0)
    {

        while (aa < strlen(after))
        {

            int len = strlen(S) + 2;
            char worda[len];
            for (int i = 0; i < strlen(S); i++)
            {
                worda[i] = S[i];
            }
            char c = after[aa];
            worda[strlen(S)] = c;
            worda[len - 1] = '\0';

            char *temp = worda;
            printf("==> %s\n", temp);
            flag++;
            maxchain(D, temp);
            flag--;
            aa++;
        }
    }
}

int main()
{
    dict D;
    D.root = newNode('\0');
    D.root = loadaddfltdict(D.root);
    char *S = "ello";
    maxchain(D, S);
    return 0;
}