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
