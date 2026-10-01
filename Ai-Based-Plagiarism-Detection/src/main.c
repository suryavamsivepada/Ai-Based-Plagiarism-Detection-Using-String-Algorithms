#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX 10000
#define PRIME 101

void read_document(char filename[], char text[])
{
    FILE *fp;
    int ch, i = 0;

    fp = fopen(filename, "r");

    if(fp == NULL)
    {
        text[0] = '\0';
        return;
    }

    while((ch = fgetc(fp)) != EOF && i < MAX - 1)
    {
        text[i] = ch;
        i++;
    }

    text[i] = '\0';
    fclose(fp);
}

void preprocess(char text[])
{
    int i;

    for(i = 0; text[i] != '\0'; i++)
    {
        text[i] = tolower(text[i]);

        if(text[i] == '\n' || text[i] == '\t')
            text[i] = ' ';
    }
}

void compute_lps(char pattern[], int lps[])
{
    int m = strlen(pattern);
    int len = 0;
    int i = 1;

    lps[0] = 0;

    while(i < m)
    {
        if(pattern[i] == pattern[len])
        {
            len++;
            lps[i] = len;
            i++;
        }
        else
        {
            if(len != 0)
                len = lps[len - 1];
            else
            {
                lps[i] = 0;
                i++;
            }
        }
    }
}

int kmp_search(char text[], char pattern[])
{
    int n = strlen(text);
    int m = strlen(pattern);
    int lps[MAX];
    int i = 0, j = 0;

    if(m == 0 || m > n)
        return 0;

    compute_lps(pattern, lps);

    while(i < n)
    {
        if(text[i] == pattern[j])
        {
            i++;
            j++;
        }

        if(j == m)
        {
            printf("KMP: Pattern found at position %d\n", i - j);
            return 1;
        }

        if(i < n && text[i] != pattern[j])
        {
            if(j != 0)
                j = lps[j - 1];
            else
                i++;
        }
    }

    printf("KMP: Pattern not found\n");

    return 0;
}

int calculate_hash(char text[])
{
    int i;
    int hash = 0;

    for(i = 0; text[i] != '\0'; i++)
        hash = (hash * 31 + text[i]) % 100000;

    return hash;
}

int rabin_karp(char text[], char pattern[])
{
    int n = strlen(text);
    int m = strlen(pattern);
    int i, j;
    int ph = 0;
    int th = 0;
    int h = 1;

    if(m == 0 || m > n)
        return 0;

    for(i = 0; i < m - 1; i++)
        h = (h * 256) % PRIME;

    for(i = 0; i < m; i++)
    {
        ph = (256 * ph + pattern[i]) % PRIME;
        th = (256 * th + text[i]) % PRIME;
    }

    for(i = 0; i <= n - m; i++)
    {
        if(ph == th)
        {
            for(j = 0; j < m; j++)
            {
                if(text[i + j] != pattern[j])
                    break;
            }

            if(j == m)
            {
                printf("Rabin-Karp: Pattern found at position %d\n", i);
                return 1;
            }
        }

        if(i < n - m)
        {
            th = (256 * (th - text[i] * h) + text[i + m]) % PRIME;

            if(th < 0)
                th = th + PRIME;
        }
    }

    printf("Rabin-Karp: Pattern not found\n");

    return 0;
}

float calculate_similarity(char text1[], char text2[])
{
    int i, j;
    int common = 0;
    int length1 = strlen(text1);
    int length2 = strlen(text2);
    int used[MAX] = {0};

    for(i = 0; i < length1; i++)
    {
        for(j = 0; j < length2; j++)
        {
            if(text1[i] == text2[j] && used[j] == 0)
            {
                common++;
                used[j] = 1;
                break;
            }
        }
    }

    if(length1 + length2 == 0)
        return 0;

    return (2.0 * common / (length1 + length2)) * 100;
}

void display_common_text(char text1[], char text2[])
{
    int i, j;
    int found;

    for(i = 0; text1[i] != '\0'; i++)
    {
        found = 0;

        for(j = 0; text2[j] != '\0'; j++)
        {
            if(text1[i] == text2[j])
            {
                found = 1;
                break;
            }
        }

        if(found)
            printf("%c", text1[i]);
    }

    printf("\n");
}

int main()
{
    char text1[MAX];
    char text2[MAX];
    char file1[100];
    char file2[100];
    int h1, h2;
    float similarity;

    printf("============================================\n");
    printf(" AI-BASED PLAGIARISM DETECTION SYSTEM\n");
    printf("     USING STRING ALGORITHMS\n");
    printf("============================================\n\n");

    printf("Enter first document name: ");
    scanf("%s", file1);

    printf("Enter second document name: ");
    scanf("%s", file2);

    read_document(file1, text1);
    read_document(file2, text2);

    if(text1[0] == '\0' || text2[0] == '\0')
    {
        printf("\nError: Unable to read document.\n");
        return 1;
    }

    printf("\nDocuments read successfully.\n");

    preprocess(text1);
    preprocess(text2);

    printf("Text preprocessing completed.\n");

    h1 = calculate_hash(text1);
    h2 = calculate_hash(text2);

    printf("\n============================================\n");
    printf("HASHING RESULT\n");
    printf("============================================\n");

    printf("Hash of Document 1: %d\n", h1);
    printf("Hash of Document 2: %d\n", h2);

    if(h1 == h2)
        printf("Hash values are same.\n");
    else
        printf("Hash values are different.\n");

    printf("\n============================================\n");
    printf("KMP STRING MATCHING\n");
    printf("============================================\n");

    kmp_search(text1, text2);

    printf("\n============================================\n");
    printf("RABIN-KARP STRING MATCHING\n");
    printf("============================================\n");

    rabin_karp(text1, text2);

    printf("\n============================================\n");
    printf("SIMILARITY CALCULATION\n");
    printf("============================================\n");

    similarity = calculate_similarity(text1, text2);

    printf("Similarity Percentage: %.2f%%\n", similarity);

    printf("\n============================================\n");
    printf("COMMON TEXT\n");
    printf("============================================\n");

    display_common_text(text1, text2);

    printf("\n============================================\n");
    printf("FINAL RESULT\n");
    printf("============================================\n");

    if(similarity >= 30)
        printf("Similar content detected.\n");
    else
        printf("Low similarity detected.\n");

    printf("\nAnalysis completed successfully.\n");

    return 0;
}