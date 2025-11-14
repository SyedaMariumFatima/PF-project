#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define MAX_WORDS 1000

int main()
{
    char **wordsList = calloc(MAX_WORDS, sizeof(char *));
    int wordCount = 0;
    char *fiveLetterWord = malloc(6 * sizeof(char));
    FILE *words = fopen("words.txt", "r"); // accessing word file
    while (fscanf(words, "%s", fiveLetterWord) != EOF && wordCount < MAX_WORDS)
    {
        wordsList[wordCount] = fiveLetterWord;
        wordCount++;
        fiveLetterWord = malloc(6 * sizeof(char));
    }

    return 0;
}
