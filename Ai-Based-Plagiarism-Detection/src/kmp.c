#include <stdio.h>
#include <string.h>

void createLPS(char pattern[], int lps[])
{
    int i, len;

    i = 1;
    len = 0;
    lps[0] = 0;

    while (pattern[i] != '\0')
    {
        if (pattern[i] == pattern[len])
        {
            len++;
            lps[i] = len;
            i++;
        }
        else
        {
            if (len != 0)
                len = lps[len - 1];
            else
            {
                lps[i] = 0;
                i++;
            }
        }
    }
}

void KMP(char text[], char pattern[])
{
    int lps[1000];
    int i, j;
    int found = 0;

    createLPS(pattern, lps);

    i = 0;
    j = 0;

    while (text[i] != '\0')
    {
        if (text[i] == pattern[j])
        {
            i++;
            j++;
        }

        if (pattern[j] == '\0')
        {
            printf("Matching text found at position %d\n", i - j);
            found = 1;
            j = lps[j - 1];
        }
        else if (text[i] != pattern[j])
        {
            if (j != 0)
                j = lps[j - 1];
            else
                i++;
        }
    }

    if (found == 0)
        printf("Matching text not found.\n");
}

int main()
{
    char text[10000];
    char pattern[1000];

    printf("KMP STRING MATCHING\n");
    printf("-------------------\n");

    printf("Enter document text:\n");
    fgets(text, sizeof(text), stdin);

    printf("Enter text to search:\n");
    fgets(pattern, sizeof(pattern), stdin);

    text[strcspn(text, "\n")] = '\0';
    pattern[strcspn(pattern, "\n")] = '\0';

    KMP(text, pattern);

    return 0;
}
