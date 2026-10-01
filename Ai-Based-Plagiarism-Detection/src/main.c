#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "document_processing.h"
#include "hashing.h"
#include "kmp.h"
#include "rabin_krap.h"
#include "similarity.h"

#define SIZE 10000

int main()
{
    char d1[SIZE];
    char d2[SIZE];
    char word[100];
    int h1, h2;
    int kmpCount = 0;
    int rabinCount = 0;
    int i, j;
    int start;

    printf("========================================\n");
    printf(" AI BASED PLAGIARISM DETECTION SYSTEM\n");
    printf("   USING STRING ALGORITHMS\n");
    printf("========================================\n");

    if (readfile("../input/document1.txt", d1) == 0)
        return 1;

    if (readfile("../input/document.txt", d2) == 0)
        return 1;

    printf("\nDocuments read successfully.\n");

    clean(d1);
    clean(d2);

    printf("\nText preprocessing completed.\n");

    writefile("../output/processed_document1.txt", d1);
    writefile("../output/processed_document2.txt", d2);

    printf("\nProcessed documents saved.\n");

    printf("\n========================================\n");
    printf("HASHING RESULT\n");
    printf("========================================\n");

    h1 = calculate_hash(d1);
    h2 = calculate_hash(d2);

    printf("Document 1 Hash : %d\n", h1);
    printf("Document 2 Hash : %d\n", h2);

    if (h1 == h2)
        printf("Hash values are same.\n");
    else
        printf("Hash values are different.\n");

    printf("\n========================================\n");
    printf("KMP STRING MATCHING\n");
    printf("========================================\n");

    start = 0;

    while (d2[start] != '\0')
    {
        while (d2[start] == ' ')
            start++;

        if (d2[start] == '\0')
            break;

        i = 0;

        while (d2[start] != ' ' && d2[start] != '\0')
        {
            word[i] = d2[start];
            i++;
            start++;
        }

        word[i] = '\0';

        if (KMP(d1, word))
        {
            printf("Common word found using KMP: %s\n", word);
            kmpCount++;
        }
    }

    printf("Total common words using KMP: %d\n", kmpCount);

    printf("\n========================================\n");
    printf("RABIN-KARP STRING MATCHING\n");
    printf("========================================\n");

    start = 0;

    while (d2[start] != '\0')
    {
        while (d2[start] == ' ')
            start++;

        if (d2[start] == '\0')
            break;

        i = 0;

        while (d2[start] != ' ' && d2[start] != '\0')
        {
            word[i] = d2[start];
            i++;
            start++;
        }

        word[i] = '\0';

        if (rabinKarpSearch(d1, word) > 0)
        {
            printf("Common word found using Rabin-Karp: %s\n", word);
            rabinCount++;
        }
    }

    printf("Total common words using Rabin-Karp: %d\n", rabinCount);

    printf("\n========================================\n");
    printf("SIMILARITY RESULT\n");
    printf("========================================\n");

    report(d1, d2);

    printf("\n========================================\n");
    printf("PROJECT EXECUTION COMPLETED\n");
    printf("========================================\n");

    return 0;
}