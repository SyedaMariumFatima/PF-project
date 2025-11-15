#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <conio.h>

#define MAX_WORDS 1000

int processGuess(char *answer, char *guess);
int main()
{

    char **wordsList = calloc(MAX_WORDS, sizeof(char *)); // array of strings
    int wordCount = 0;
    char *fiveLetterWord = malloc(6 * sizeof(char));
    FILE *words = fopen("words.txt", "r"); // accessing word file

    // loading words into the game
    while (fscanf(words, "%s", fiveLetterWord) != EOF && wordCount < MAX_WORDS)
    {
        wordsList[wordCount] = fiveLetterWord;
        wordCount++;
        fiveLetterWord = malloc(6 * sizeof(char));
    }
    fclose(words);

    // starting the game
    srand(time(NULL)); // randomly picking a word
    char *answer = wordsList[rand() % wordCount];

    int guesses = 0; // total number of guesses
    bool correctGuess = 0;
    char *guess = malloc(6 * sizeof(char)); // storing that word

    while (guesses < 6)
    {
        printf("\033[94m\nEnter a 5-letter word and press enter: ");
        scanf("%s", guess);
        guesses++;

        if (processGuess(answer, guess) == 5)
        {
            printf("\033[92myou win!");
            break;
        }
    }

    // freeing the memory used
    for (int i = 0; i < wordCount; i++)
    {
        free(wordsList[i]); // freeing individual words memory
    }
    free(wordsList); // freeing the entire list
    free(fiveLetterWord);
    free(guess);

    return 0;
}

int processGuess(char *answer, char *guess)
{
    int corr = 0;
    // for correct letter in correct place
    for (int i = 0; i < 5; i++)
    {

        if (guess[i] == answer[i])
        {
            printf("\033[92m%c", guess[i]);
            corr++;
        }
        else
        {
            int count = 0;
            for (int j = 0; j < 5; j++)
            {
                if (guess[i] == answer[j] && i != j)
                {
                    count++;
                }
            }
            if (count == 0)
            {
                printf("\033[91m%c", guess[i]);
            }
            else

                printf("\033[93m%c", guess[i]);
        }
    }
    return corr;
}
