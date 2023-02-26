#include "../util/wordutils.h"

int main()
{
    printf("Enter the string: ");
    char *_str;
    // char s[] = "abac";
    _str = (char *)malloc(100 * sizeof(char));
    scanf("%s", _str);
    if (strlen(_str) <=1)
    {
        printf("Unit length string or Null string!! No substrings POSSIBLE !!\n");
        return 0;
    }
    else
    {
        char *str = strdup(_str);
        dict D;
        D.root = NULL;
        D.root = newNode('\0');
        D.root = loadaddfltdict(D.root);
        int i, len = strlen(_str);
        for (i = 0; i < len; ++i)
        {

            char *temp_str;
            temp_str = (char *)malloc((len) * sizeof(char));
            int j, k = 0;
            for (j = 0; j < len; ++j)
            {
                if (j == i)
                {
                }
                else
                {
                    temp_str[k] = _str[j];
                    k++;
                }
            }
            temp_str[k] = '\0';
            char *temp = strdup(temp_str);
            char **list = sortedPermutations(D, temp);
            int l = 0;
            while (list[l] != NULL)
            {
                printf("%s\n", list[l]);
                l++;
            }
            free(list);
            free(temp_str);
        }
    }
}
