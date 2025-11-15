#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#define MAX_WORDS 1000

bool processGuess (char* answer, char* guess);
int main()
{
    
    char** wordsList = calloc(MAX_WORDS, sizeof(char *)); //array of strings
    int wordCount = 0;
    char* fiveLetterWord = malloc(6 * sizeof(char));
    FILE* words = fopen("words.txt", "r"); // accessing word file

    //loading words into the game
    while (fscanf(words, "%s", fiveLetterWord) != EOF && wordCount < MAX_WORDS)
    {
        wordsList[wordCount] = fiveLetterWord;
        wordCount++;
        fiveLetterWord = malloc(6 * sizeof(char));
    }
    fclose(words);

    //starting the game
    srand(time(NULL)); //randomly picking a word
    char* answer = wordsList[rand()%wordCount];

    int guesses = 0; //total number of guesses
    bool correctGuess = 0;
    char* guess = malloc(6*sizeof(char)); //storing that word

    while (guesses < 6 && correctGuess != 1) {
        printf("Enter a 5-letter word and press enter: ");
        scanf("%s", guess);
        guesses++;

        correctGuess = processGuess (answer, guess);
    }

    if (correctGuess==1) {
        printf("Congratulations! You guesses the correct word in %d times\n", guesses);
    }
    else {
        printf("You have used up your guesses.... the correct word is %s\n", answer);
    }

    //freeing the memory used
    for(int i=0; i<wordCount; i++) {
        free(wordsList[i]);//freeing individual words memory
    }
    free(wordsList);//freeing the entire list
    free(fiveLetterWord);
    free(guess);

    return 0;
}


bool processGuess (char* answer, char* guess) {
    //initializing the array to -
    char defaultArray[] = {'-','-','-','-','-','\0'};
    //initializing all the flags to 0
    bool answerFlags[5] = {0,0,0,0,0};

    //for correct letter in correct place
    for (int i=0; i<5; i++) {
        if (guess[i] == answer[i]) {
           defaultArray[i] = 'G'; 
           answerFlags[i] = 1;
        }
    }
    //for letters in the wrong place
    for (int i=0; i<5; i++) {
        if (defaultArray[i] == '-') {
            for(int j=0; j<5; j++) {
                if(guess[i]==answer[j] && answerFlags[j] == 0) {
                    defaultArray[i] = 'Y';
                    answerFlags[j] = 1;
                    break;
                }
            }
        }
    }

    printf("%s\n", defaultArray);
    //returns 1 if the player guessed all the letter correctly
    int correct_guess = strcmp(defaultArray, "GGGGG")==0;
    return correct_guess;
}