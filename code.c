#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define MAX_WORDS 1000

int game(char* answer, char* guess);
int processGuess(char *answer, char *guess);
int total_guesses = 0;   // Global variable to track total guesses across multiple games



int main() {
    // Allocate memory for storing up to MAX_WORDS words
    char **wordsList = calloc(MAX_WORDS, sizeof(char *));
    int wordCount = 0; // Counter for number of words loaded
    char buffer[6];   // Temporary buffer to hold each word (5 letters + null terminator)
    FILE *words = fopen("words.txt", "r"); // Open words file for reading

    // Check if file opened successfully
    if (words == NULL) {
        printf("Failed to open words.txt\n");
        return 1; // Exit program if file not found
    }

    // Read words from file into wordsList
    while (fscanf(words, "%5s", buffer) != EOF && wordCount < MAX_WORDS) {
        wordsList[wordCount] = strdup(buffer);  // Duplicate string into heap memory
        wordCount++;
    }
    fclose(words);// Close file after reading
    srand(time(NULL)); // Seed random number generator with current time
    char *guess = malloc(6 * sizeof(char)); // Allocate memory for user guesses
    int number_of_tries = 0; // Track number of games played
    char response[4]; // Store user response (Yes/No)

    // Print game instructions
    printf("Welcome to Wordle\n");
    printf("You'll have 6 tries to guess a word\n");
    printf("Correct letters in correct spots: \033[92mgreen\033[0m\n");
    printf("Correct letters in wrong spots: \033[93myellow\033[0m\n");
    printf("Incorrect letters: \033[91mred\033[0m\n");
    printf("Let's start the game!\n");

    // Main game loop (allows replay up to 10 times)
    do {
         // Pick a random word from the list as the answer
        char *answer = wordsList[rand() % wordCount];

         // Play one game and return number of guesses used
        int guesses_used = game(answer, guess);
        total_guesses += guesses_used;  // Add to total guesses across games
        

        // Check win/loss condition
        if (guesses_used <= 6) {
            printf("\033[92m\nYou Won!\033[0m\n");
            printf("Do you wish to play again? Enter Yes or No: ");
            scanf("%3s", response);
        } else {
            printf("\033[93mYou lost!\033[0m\n");
            break; // Exit loop if player lost
        }
        number_of_tries++;
    } while ((strcasecmp(response, "YES") == 0) && number_of_tries < 10);

    // After finishing, show average guesses per game
    if (number_of_tries > 0) {
        float avg_steps = (float)total_guesses / number_of_tries;
        printf("You played Wordle %d times and guessed the word(s) in an average of %.2f steps\n", number_of_tries, avg_steps);
    }

    // Free allocated memory
    for (int i = 0; i < wordCount; i++) {
        free(wordsList[i]);
    }
    free(wordsList);
    free(guess);

    return 0;
}

// Function to process a single guess and print colored feedback
int processGuess(char *answer, char *guess) {
    int correct = 0; // Count of correctly placed letters
    for (int i = 0; i < 5; i++) {
        if (guess[i] == answer[i]) {
             // Correct letter in correct position --> green
            printf("\033[92m%c\033[0m", guess[i]);
            correct++;
        } else {
            int found = 0;
             // Check if letter exists elsewhere in the word
            for (int j = 0; j < 5; j++) {
                if (guess[i] == answer[j] && i != j) {
                    found = 1;
                    break;
                }
            }
            if (found)
                  // Correct letter but wrong position --> yellow
                printf("\033[93m%c\033[0m", guess[i]);
            else
                 // Letter not in word --> red
                printf("\033[91m%c\033[0m", guess[i]);
        }
    }
    printf("\n");
    return correct; // Return number of correct letters
}

// Function to run one game session
int game(char* answer, char* guess) {
    int guesses = 0;
    while (guesses < 6) { // Player has max 6 guesses
        printf("\033[94mEnter a 5-letter word: \033[0m");
        scanf("%5s", guess);
        guesses++;
        
          // If all 5 letters correct, player wins
        if (processGuess(answer, guess) == 5) {
            return guesses;
        }
    }
    return 7; // Indicates loss
}


