#include <stdio.h>
#include <string.h>

#define PRIME 101
#define BASE 256

int calculateHash(const char *text, int length)
{
    int hash = 0;
    int i;

    for (i = 0; i < length; i++)
        hash = (hash * BASE + (unsigned char)text[i]) % PRIME;

    return hash;
}

int rabinKarpSearch(const char *text, const char *pattern)
{
    int textLength = strlen(text);
    int patternLength = strlen(pattern);
    int patternHash;
    int textHash;
    int highestPower = 1;
    int i, j;
    int count = 0;

    if (patternLength == 0 || patternLength > textLength)
        return 0;

    patternHash = calculateHash(pattern, patternLength);
    textHash = calculateHash(text, patternLength);

    for (i = 0; i < patternLength - 1; i++)
        highestPower = (highestPower * BASE) % PRIME;

    for (i = 0; i <= textLength - patternLength; i++)
    {
        if (patternHash == textHash)
        {
            int match = 1;

            for (j = 0; j < patternLength; j++)
            {
                if (text[i + j] != pattern[j])
                {
                    match = 0;
                    break;
                }
            }

            if (match)
                count++;
        }

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