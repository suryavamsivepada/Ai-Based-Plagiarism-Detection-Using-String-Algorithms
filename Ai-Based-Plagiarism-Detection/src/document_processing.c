#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAX_SIZE 10000

// Remove unnecessary spaces and symbols
void preprocessText(char text[])
{
    char cleaned[MAX_SIZE];
    int i, j = 0;
    int spaceFound = 0;

    for (i = 0; text[i] != '\0'; i++)
    {
        // Keep alphabets and numbers
        if (isalnum((unsigned char)text[i]))
        {
            cleaned[j++] = tolower((unsigned char)text[i]);
            spaceFound = 0;
        }
        // Replace spaces with a single space
        else if (isspace((unsigned char)text[i]))
        {
            if (j > 0 && spaceFound == 0)
            {
                cleaned[j++] = ' ';
                spaceFound = 1;
            }
        }
    }

    // Remove space at the end
    if (j > 0 && cleaned[j - 1] == ' ')
    {
        j--;
    }

    cleaned[j] = '\0';

    strcpy(text, cleaned);
}

// Read document from file
int readDocument(const char *filename, char text[])
{
    FILE *file;
    int ch;
    int i = 0;

    file = fopen(filename, "r");

    if (file == NULL)
    {
        printf("Error: Could not open file %s\n", filename);
        return 0;
    }

    while ((ch = fgetc(file)) != EOF && i < MAX_SIZE - 1)
    {
        text[i++] = (char)ch;
    }

    text[i] = '\0';

    fclose(file);

    return 1;
}

// Save processed document
void saveProcessedText(const char *filename, const char text[])
{
    FILE *file = fopen(filename, "w");

    if (file == NULL)
    {
        printf("Error: Could not create output file.\n");
        return;
    }

    fprintf(file, "%s", text);

    fclose(file);
}

// Main function
int main()
{
    char document1[MAX_SIZE];
    char document2[MAX_SIZE];

    printf("=====================================\n");
    printf("   AI-BASED PLAGIARISM DETECTION\n");
    printf("       DOCUMENT PROCESSING\n");
    printf("=====================================\n\n");

    // Read first document
    if (!readDocument("input/document1.txt", document1))
    {
        return 1;
    }

    // Read second document
    if (!readDocument("input/document2.txt", document2))
    {
        return 1;
    }

    // Display original text
    printf("Original Document 1:\n");
    printf("%s\n\n", document1);

    printf("Original Document 2:\n");
    printf("%s\n\n", document2);

    // Preprocess documents
    preprocessText(document1);
    preprocessText(document2);

    // Display processed text
    printf("Processed Document 1:\n");
    printf("%s\n\n", document1);

    printf("Processed Document 2:\n");
    printf("%s\n\n", document2);

    // Save processed documents
    saveProcessedText("output/processed_document1.txt", document1);
    saveProcessedText("output/processed_document2.txt", document2);

    printf("Document processing completed successfully.\n");
    printf("Processed files saved in the output folder.\n");

    return 0;
} 
