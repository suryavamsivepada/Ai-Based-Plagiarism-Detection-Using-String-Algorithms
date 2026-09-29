#include <stdio.h>
#include <string.h>
#define SIZE 10000
int words(char text[])
{
    int i;
    int count;
    int inside;
    count = 0;
    inside = 0;
    for (i = 0; text[i] != '\0'; i++)
    {
        if (text[i] != ' ' && inside == 0)
        {
            count++;
            inside = 1;
        }
        if (text[i] == ' ')
            inside = 0;
    }
    return count;
}
int common(char text1[], char text2[])
{
    char temp[SIZE];
    char *p;
    int count;
    strcpy(temp, text1);
    count = 0;
    p = strtok(temp, " ");
    while (p != NULL)
    {
        if (strstr(text2, p) != NULL)
            count++;
        p = strtok(NULL, " ");
    }
    return count;
}
void report(char text1[], char text2[])
{
    int w1;
    int w2;
    int c;
    float percentage;
    w1 = words(text1);
    w2 = words(text2);
    c = common(text1, text2);
    if (w1 > w2)
        percentage = (c * 100.0) / w1;
    else if (w2 > 0)
        percentage = (c * 100.0) / w2;
    else
        percentage = 0;
    printf("\n");
    printf("----------------------------------\n");
    printf("       PLAGIARISM REPORT\n");
    printf("----------------------------------\n");
    printf("Document 1 words : %d\n", w1);
    printf("Document 2 words : %d\n", w2);
    printf("Common words     : %d\n", c);
    printf("Similarity       : %.2f%%\n", percentage);
    if (percentage >= 30)
        printf("Result           : Similar content found\n");
    else
        printf("Result           : Low similarity\n");
    printf("----------------------------------\n");
}
int main()
{
    char d1[SIZE];
    char d2[SIZE];
    FILE *f1;
    FILE *f2;
    printf("AI BASED PLAGIARISM DETECTION\n");
    printf("SIMILARITY AND REPORT MODULE\n");
    f1 = fopen("output/processed_document1.txt", "r");
    if (f1 == NULL)
    {
        printf("Document 1 cannot be opened.\n");
        return 1;
    }
    f2 = fopen("output/processed_document2.txt", "r");
    if (f2 == NULL)
    {
        printf("Document 2 cannot be opened.\n");
        fclose(f1);
        return 1;
    }
    fread(d1, sizeof(char), SIZE - 1, f1);
    fread(d2, sizeof(char), SIZE - 1, f2);
    d1[SIZE - 1] = '\0';
    d2[SIZE - 1] = '\0';
    fclose(f1);
    fclose(f2);
    report(d1, d2);
    return 0;
}
