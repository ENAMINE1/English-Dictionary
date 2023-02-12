// #include"../util/dictutils.h"
#include"../util/dictutils.c"
//#include "../trie/trie.c"

// finds the longest chain of valid words, that can be obtained by adding single letters to the beginning or end of words
void maxchain(dict D,char* S)
{

    //listall(D.root);
    int aa = 0;
    int bb = 0;
    char * before = addbefore(D, S);
    char * after = addafter(D, S);
    if (strlen(after) == 0 && strlen(before) == 0)
    {
        return;
    }

    // If no characters can be added before S to obtain valid English words
    if (strlen(before) != 0)
    {

        while (bb < strlen(before))
        {
            char wordb[strlen(S) + 1];
            wordb[0] = before[bb];
            strcat(wordb, S);
            char* temp = wordb;
            printf("==> %s\n", temp);
            maxchain(D, temp);
            bb++;
        }
    }
    //If no characters can be add after S to obtain valid English words
    if(strlen(after) != 0)
    {

        while (aa < strlen(after))
        {
            char worda[strlen(S) + 1];
            strcpy(worda, S);
            char c = after[aa];
            strncat(worda, &c, 1);
            char* temp = worda;
            printf("==> %s\n", temp);
            maxchain(D, temp);
            aa++;
        }
    }

}


int main()
{
    dict D;
    D.root = newNode('\0');
    D.root = loadaddfltdict(D.root);
    char *S = "all";
    maxchain(D, S);
    return 0;
}