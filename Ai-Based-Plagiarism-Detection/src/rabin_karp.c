#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_SIZE 10000
#define PRIME 101
#define BASE 256

// Read processed document from file
int readDocument(const char *filename, char text[])
{
    FILE *file = fopen(filename, "r");

    if (file == NULL)
    {
        printf("Error: Cannot open file %s\n", filename);
        return 0;
    }

    size_t length = fread(text, sizeof(char), MAX_SIZE - 1, file);
    text[length] = '\0';

    fclose(file);
    return 1;
}

// Calculate hash value
int calculateHash(const char *text, int length)
{
    int hash = 0;

    for (int i = 0; i < length; i++)
    {
        hash = (hash * BASE + (unsigned char)text[i]) % PRIME;
    }

    return hash;
}

// Rabin-Karp string matching
int rabinKarpSearch(const char *text, const char *pattern)
{
    int textLength = strlen(text);
    int patternLength = strlen(pattern);

    if (patternLength == 0 || patternLength > textLength)
        return 0;

    int patternHash = calculateHash(pattern, patternLength);
    int textHash = calculateHash(text, patternLength);

    int highestPower = 1;

    for (int i = 0; i < patternLength - 1; i++)
        highestPower = (highestPower * BASE) % PRIME;

    int count = 0;

    for (int i = 0; i <= textLength - patternLength; i++)
    {
        if (patternHash == textHash)
        {
            int match = 1;

            // Verify characters to avoid hash collision
            for (int j = 0; j < patternLength; j++)
            {
                if (text[i + j] != pattern[j])
                {
                    match = 0;
                    break;
                }
            }

            if (match)
            {
                count++;
                printf("Pattern found at position: %d\n", i);
            }
        }

        // Rolling hash
        if (i < textLength - patternLength)
        {
            textHash =
                (BASE * (textHash -
                (unsigned char)text[i] * highestPower)
                + (unsigned char)text[i + patternLength]) % PRIME;

            if (textHash < 0)
                textHash += PRIME;
        }
    }

    return count;
}

int main()
{
    char document1[MAX_SIZE];
    char document2[MAX_SIZE];
    char pattern[1000];

    printf("=====================================\n");
    printf("       RABIN-KARP STRING MATCHING\n");
    printf("=====================================\n\n");

    // Read processed files created by Member 1
    if (!readDocument("output/processed_document1.txt", document1))
        return 1;

    if (!readDocument("output/processed_document2.txt", document2))
        return 1;

    printf("Enter pattern to search: ");
    fgets(pattern, sizeof(pattern), stdin);
    pattern[strcspn(pattern, "\n")] = '\0';

    // Convert pattern to lowercase
    for (int i = 0; pattern[i] != '\0'; i++)
        pattern[i] = tolower((unsigned char)pattern[i]);

    printf("\n========== DOCUMENT 1 ==========\n");
    int count1 = rabinKarpSearch(document1, pattern);
    printf("Total occurrences in Document 1: %d\n", count1);

    printf("\n========== DOCUMENT 2 ==========\n");
    int count2 = rabinKarpSearch(document2, pattern);
    printf("Total occurrences in Document 2: %d\n", count2);

    printf("\n=====================================\n");
    printf("Rabin-Karp searching completed.\n");
    printf("=====================================\n");

    return 0;
}
