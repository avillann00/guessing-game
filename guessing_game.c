// headers
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>

// changes any uppercase to lowercase for better handling
char * str_lwr(char * string){
    int size = strlen(string);
    for(int i = 0; i < size; i++){
        string[i] = tolower(string[i]);
    }

    return string;
}

// function that actually plays the game
void game(int target, int limit, bool print_hint){
    // variable to store the guess attempt
    int guess;

    printf("Okay start guessing.\n");

    // -1 means unlimited guesses but the final number of attempts will be printed at the end
    if(limit == -1){
        int num_guesses = 0;
        while(1){
            scanf("%d", &guess);
            if(guess == target){
                break;
            }
            else{
                num_guesses++;
                printf("Incorrect.\n");
                if(print_hint){
                    if(guess > target){
                        printf("Too high.\n");
                    }
                    else{
                        printf("Too low\n");
                    }
                }
            }
        }

        printf("You won! it took %d guesses.", num_guesses);
    }
    else{
        // variable to see if the person won or lost
        bool win = false;
        for(int i = 0; i < limit; i++){
            scanf("%d", &guess);
            if(guess == target){
                win = true;
                break;
            }
            else{
                printf("Incorrect.\n");
                if(print_hint){
                    if(guess > target){
                        printf("Too high.\n");
                    }
                    else{
                        printf("Too low");
                    }
                }
            }
        }

        if(win){
            printf("You won!");
        }
        else{
            printf("You lost.");
        }
    }
}

// main function
int main(){
    // random function
    srand(time(NULL));

    // variables to store input
    char * difficulty = (char*)malloc(sizeof(char) * 10);
    char * hint = (char*)malloc(sizeof(char) * 5);
    char * type = (char*)malloc(sizeof(char) * 15);
    // variable that decides the difficulty
    int max;
    // variable that decides if hints should be printed
    bool print_hint;

    // game intro and takes input
    printf("Hello, welcome to the guessing game. A random number will be chosen and you have to guess it.\n");

    do{
      printf("What difficulty? Easy, Medium, Hard, or Quit\n");
      scanf("%s", difficulty);
      str_lwr(difficulty);
      if(strcmp(difficulty, "easy") == 0){
        max = 10;
        break;
      }
      else if(strcmp(difficulty, "medium") == 0){
        max = 50;
        break;
      }
      else if(strcmp(difficulty, "hard") == 0){
        max = 100;
        break;
      }
      else if(strcmp(difficulty, "quit") == 0){
        return 0;
      } 
      else{
        printf("invalid answer.\n");
      }
    }while(1);

    // number to be guessed
    int target = (rand() % max) + 1;

    do{
      printf("Would you like hints on? Yes, No, or Quit\n");
      scanf("%s", hint);
      str_lwr(hint);
      if(strcmp(hint, "yes") == 0){
        print_hint = true;
        break;
      }
      else if(strcmp(hint, "no") == 0){
        print_hint = false;
        break;
      }
      else if(strcmp(difficulty, "quit") == 0){
        return 0;
      }
      else{
        printf("invalid answer.\n");
      }
    }while(1);

    printf("Unlimited guesses or preset amount? Unlimited or preset\n");
    scanf("%s", type);
    str_lwr(type);
    if(strcmp(type, "unlimited") == 0){
      game(target, -1, print_hint);
    }
    else if(strcmp(type, "preset") == 0){
      if(max == 10){
        game(target, 3, print_hint);
      }
      else if(max == 50){
        game(target, 7, print_hint);
      }
      else{
        game(target, 10, print_hint);
      }
    }
    else{
      printf("invalid answer.\n");
      return 0;
    }

    free(difficulty);
    free(hint);
    free(type);

    return 0;
}
