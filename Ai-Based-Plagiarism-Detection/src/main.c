#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define SIZE 10000
#define PATTERN_SIZE 1000
#define BASE 256
#define PRIME 101

void preprocess(char text[])
{
    char temp[SIZE];
    int i, j, space;

    i = 0;
    j = 0;
    space = 0;

    while (text[i] != '\0')
    {
        if (isalnum((unsigned char)text[i]))
        {
            temp[j] = tolower((unsigned char)text[i]);
            j++;
            space = 0;
        }
        else if (isspace((unsigned char)text[i]))
        {
            if (j > 0 && space == 0)
            {
                temp[j] = ' ';
                j++;
                space = 1;
            }
        }

        i++;
    }

    if (j > 0 && temp[j - 1] == ' ')
        j--;

    temp[j] = '\0';

    strcpy(text, temp);
}

void lps_array(char pattern[], int lps[])
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
        else if (len != 0)
        {
            len = lps[len - 1];
        }
        else
        {
            lps[i] = 0;
            i++;
        }
    }
}

int kmp(char text[], char pattern[])
{
    int lps[PATTERN_SIZE];
    int i, j;

    if (pattern[0] == '\0')
        return -1;

    lps_array(pattern, lps);

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
            return i - j;

        if (text[i] != pattern[j])
        {
            if (j != 0)
                j = lps[j - 1];
            else
                i++;
        }
    }

    return -1;
}

int rabin(char text[], char pattern[])
{
    int n, m;
    int i, j;
    int h;
    int th, ph;

    n = strlen(text);
    m = strlen(pattern);

    if (m == 0 || m > n)
        return -1;

    h = 1;

    for (i = 0; i < m - 1; i++)
        h = (h * BASE) % PRIME;

    th = 0;
    ph = 0;

    for (i = 0; i < m; i++)
    {
        ph = (BASE * ph + pattern[i]) % PRIME;
        th = (BASE * th + text[i]) % PRIME;
    }

    for (i = 0; i <= n - m; i++)
    {
        if (th == ph)
        {
            j = 0;

            while (j < m && text[i + j] == pattern[j])
                j++;

            if (j == m)
                return i;
        }

        if (i < n - m)
        {
            th = (BASE * (th - text[i] * h)
                  + text[i + m]) % PRIME;

            if (th < 0)
                th = th + PRIME;
        }
    }

    return -1;
}

int count_words(char text[])
{
    int i, count, inside;

    i = 0;
    count = 0;
    inside = 0;

    while (text[i] != '\0')
    {
        if (text[i] != ' ' && inside == 0)
        {
            count++;
            inside = 1;
        }
        else if (text[i] == ' ')
        {
            inside = 0;
        }

        i++;
    }

    return count;
}

int common_words(char text1[], char text2[])
{
    char copy[SIZE];
    char *word;
    int count;

    strcpy(copy, text1);

    count = 0;
    word = strtok(copy, " ");

    while (word != NULL)
    {
        if (strstr(text2, word) != NULL)
            count++;

        word = strtok(NULL, " ");
    }

    return count;
}

int main()
{
    char document1[SIZE];
    char document2[SIZE];
    char pattern[PATTERN_SIZE];

    int p1, p2;
    int w1, w2, common;
    float similarity;

    printf("=====================================\n");
    printf(" AI-BASED PLAGIARISM DETECTION\n");
    printf("=====================================\n");

    printf("\nEnter Document 1:\n");
    fgets(document1, SIZE, stdin);

    printf("\nEnter Document 2:\n");
    fgets(document2, SIZE, stdin);

    preprocess(document1);
    preprocess(document2);

    printf("\nProcessed Document 1:\n");
    printf("%s\n", document1);

    printf("\nProcessed Document 2:\n");
    printf("%s\n", document2);

    printf("\nEnter text to search:\n");
    fgets(pattern, PATTERN_SIZE, stdin);

    pattern[strcspn(pattern, "\n")] = '\0';

    p1 = kmp(document1, pattern);
    p2 = rabin(document2, pattern);

    printf("\nKMP Result: ");

    if (p1 >= 0)
        printf("Match found at position %d\n", p1);
    else
        printf("Match not found\n");

    printf("Rabin-Karp Result: ");

    if (p2 >= 0)
        printf("Match found at position %d\n", p2);
    else
        printf("Match not found\n");

    w1 = count_words(document1);
    w2 = count_words(document2);

    common = common_words(document1, document2);

    if (w1 > w2 && w1 > 0)
        similarity = common * 100.0 / w1;
    else if (w2 > 0)
        similarity = common * 100.0 / w2;
    else
        similarity = 0;

    printf("\n=====================================\n");
    printf("          FINAL REPORT\n");
    printf("=====================================\n");

    printf("Document 1 words : %d\n", w1);
    printf("Document 2 words : %d\n", w2);
    printf("Common words     : %d\n", common);
    printf("Similarity       : %.2f%%\n", similarity);

    if (similarity >= 30)
        printf("Result            : Similar content detected\n");
    else
        printf("Result            : Low similarity\n");

    printf("=====================================\n");

    return 0;
}