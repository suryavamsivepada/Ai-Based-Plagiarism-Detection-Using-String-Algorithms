#include <stdio.h>
#include <ctype.h>
#include <string.h>
#define SIZE 10000
void clean(char s[])
{
    char t[SIZE];
    int i, j;
    int space;
    j = 0;
    space = 0;
    for (i = 0; s[i] != '\0'; i++)
    {
        if (isalnum(s[i]))
        {
            t[j] = tolower(s[i]);
            j++;
            space = 0;
        }
        else if (isspace(s[i]))
        {
            if (j > 0 && space == 0)
            {
                t[j] = ' ';
                j++;
                space = 1;
            }
        }
    }

    if (j > 0 && t[j - 1] == ' ')
        j--;
    t[j] = '\0';
    strcpy(s, t);
}
int readfile(char name[], char text[])
{
    FILE *fp;
    int ch;
    int i;
    fp = fopen(name, "r");
    if (fp == NULL)
    {
        printf("File cannot be opened: %s\n", name);
        return 0;
    }
    i = 0;
    while ((ch = fgetc(fp)) != EOF && i < SIZE - 1)
    {
        text[i] = ch;
        i++;
    }
    text[i] = '\0';
    fclose(fp);
    return 1;
}
void writefile(char name[], char text[])
{
    FILE *fp;
    fp = fopen(name, "w");
    if (fp == NULL)
    {
        printf("Cannot create output file.\n");
        return;
    }
    fprintf(fp, "%s", text);
    fclose(fp);
}
int main()
{
    char d1[SIZE];
    char d2[SIZE];
    printf("\n");
    printf("AI BASED PLAGIARISM DETECTION\n");
    printf("DOCUMENT PROCESSING\n");
    printf("------------------------------\n");
    if (readfile("input/document1.txt", d1) == 0)
        return 1;
    if (readfile("input/document2.txt", d2) == 0)
        return 1;
    printf("\nDocument 1:\n");
    printf("%s\n", d1);
    printf("\nDocument 2:\n");
    printf("%s\n", d2);
    clean(d1);
    clean(d2);
    printf("\nAfter Processing:\n");
    printf("\nDocument 1:\n");
    printf("%s\n", d1);
    printf("\nDocument 2:\n");
    printf("%s\n", d2);
    writefile("output/processed_document1.txt", d1);
    writefile("output/processed_document2.txt", d2);
    printf("\nProcessing completed.\n");
    return 0;
}
