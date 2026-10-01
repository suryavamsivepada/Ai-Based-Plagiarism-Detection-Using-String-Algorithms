#include "hashing.h"

int calculate_hash(char text[])
{
    int i;
    int hash = 0;

    for(i = 0; text[i] != '\0'; i++)
    {
        hash = (hash * 31 + text[i]) % 100000;
    }

    return hash;
}

int compare_hash(char text1[], char text2[])
{
    int h1;
    int h2;

    h1 = calculate_hash(text1);
    h2 = calculate_hash(text2);

    if(h1 == h2)
        return 1;

    return 0;
}