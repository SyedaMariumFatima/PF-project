#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define MAX_WORDS 1000

int game(char* answer, char* guess);
int processGuess(char *answer, char *guess);
int total_guesses = 0;

int main() {
    char **wordsList = calloc(MAX_WORDS, sizeof(char *));
    int wordCount = 0;
    char buffer[6];
    FILE *words = fopen("words.txt", "r");

    if (words == NULL) {
        printf("Failed to open words.txt\n");
        return 1;
    }

    while (fscanf(words, "%5s", buffer) != EOF && wordCount < MAX_WORDS) {
        wordsList[wordCount] = strdup(buffer);
        wordCount++;
    }
    fclose(words);
    srand(time(NULL));
    char *guess = malloc(6 * sizeof(char));
    int number_of_tries = 0;
    char response[4];

    printf("Welcome to Wordle\n");
    printf("You'll have 6 tries to guess a word\n");
    printf("Correct letters in correct spots: \033[92mgreen\033[0m\n");
    printf("Correct letters in wrong spots: \033[93myellow\033[0m\n");
    printf("Incorrect letters: \033[91mred\033[0m\n");
    printf("Let's start the game!\n");

    do {
        char *answer = wordsList[rand() % wordCount];
        int guesses_used = game(answer, guess);
        total_guesses += guesses_used;

        if (guesses_used <= 6) {
            printf("\033[92m\nYou Won!\033[0m\n");
            printf("Do you wish to play again? Enter Yes or No: ");
            scanf("%3s", response);
        } else {
            printf("\033[93mYou lost!\033[0m\n");
            break;
        }
        number_of_tries++;
    } while ((strcasecmp(response, "YES") == 0) && number_of_tries < 10);

    if (number_of_tries > 0) {
        float avg_steps = (float)total_guesses / number_of_tries;
        printf("You played Wordle %d times and guessed the word(s) in an average of %.2f steps\n", number_of_tries, avg_steps);
    }

    for (int i = 0; i < wordCount; i++) {
        free(wordsList[i]);
    }
    free(wordsList);
    free(guess);

    return 0;
}
int processGuess(char *answer, char *guess) {
    int correct = 0;
    for (int i = 0; i < 5; i++) {
        if (guess[i] == answer[i]) {
            printf("\033[92m%c\033[0m", guess[i]);
            correct++;
        } else {
            int found = 0;
            for (int j = 0; j < 5; j++) {
                if (guess[i] == answer[j] && i != j) {
                    found = 1;
                    break;
                }
            }
            if (found)
                printf("\033[93m%c\033[0m", guess[i]);
            else
                printf("\033[91m%c\033[0m", guess[i]);
        }
    }
    printf("\n");
    return correct;
}

int game(char* answer, char* guess) {
    int guesses = 0;
    while (guesses < 6) {
        printf("\033[94mEnter a 5-letter word: \033[0m");
        scanf("%5s", guess);
        guesses++;
        if (processGuess(answer, guess) == 5) {
            return guesses;
        }
    }
    return 7; // Indicates loss
}

