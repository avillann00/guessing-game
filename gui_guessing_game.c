// TODO: ADD MUSIC? ADD PICTURES?

// header files
#include <stdio.h>
#include <time.h>
#include <limits.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
// gui library
#include <raylib.h>

// defenition for the size of the users input
#define INPUT_SIZE 10

// the different screens that will be shown
typedef enum screens{LOGO = 0, START = 1, GAME = 2, END = 3} screens;

// function that resets the users input
void reset(char * word, int * letter_count){
  word[0] = '\0';  
  *letter_count = 0;
  return;
}

int to_int(char key){
  switch(key){
    case KEY_ZERO:
      return 0;
    case KEY_ONE:
      return 1;
    case KEY_TWO:
      return 2;
    case KEY_THREE:
      return 3;
    case KEY_FOUR:
      return 4;
    case KEY_FIVE:
      return 5;
    case KEY_SIX:
      return 6;
    case KEY_SEVEN:
      return 7;
    case KEY_EIGHT:
      return 8;
    case KEY_NINE:
      return 9;
  };
  return 0;
}

// main function
int main(){
  // random function
  srand(time(NULL));

  // setting the fps 
  SetTargetFPS(100);

  // window height and width
  const int screen_width = 800;
  const int screen_height = 800;

  // the max that the random number can be
  int max;
  // the number of guesses the user gets if not unlimited
  int num_guesses;
  // the key taken from the user 
  int key;
  // the position of the input
  int letter_count = 0;
  // the full input of the user guess
  char input[INPUT_SIZE];
  reset(input, &letter_count);
  // the int version of the user input
  int i_input = 0;
  // variable to store the moving text
  int pos_x = 0;

  // set the current screen
  screens current = LOGO;

  // bool to check if the user won
  bool won = false;

  // initializes a window
  InitWindow(screen_width, screen_height, "basic window");
  
  // rectangle structs for all the buttons
  Rectangle easy = { screen_width / 2 - 100, screen_height / 2 - 150, 200, 100 };
  Rectangle medium = { screen_width / 2 - 100, screen_height / 2 - 50, 200, 100 };
  Rectangle hard = { screen_width / 2 - 100, screen_height / 2 + 50, 200, 100 };
  Rectangle hint = { screen_width / 2 - 100, screen_height / 2 + 150, 200, 100 };
  Rectangle type = { screen_width / 2 - 100, screen_height / 2 + 250, 200, 100 };
  
  // bools to check if a button is pressed
  bool easy_pressed = false;
  bool medium_pressed = false;
  bool hard_pressed = false;
  bool type_pressed = false;
  bool hint_pressed = false;
  
  // bools to check if too high or too low
  bool high = false;
  bool low = false;

  // variable for the correct anser
  int answer;

  // while loop to keep the window open until closed by user
  while(!WindowShouldClose()){
    // handles updating the pages (buttons)
    switch(current){
      case LOGO: // logo functionality
        if(IsKeyPressed(KEY_ENTER)){
          current = START;
        }
        break;
      case START: // start functionality
          // all of the settings for the game
        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
          Vector2 mousePoint = GetMousePosition();
          int g_num;
          if(CheckCollisionPointRec(mousePoint, easy)){
            g_num = 3;
            easy_pressed = true;
            medium_pressed = false;
            hard_pressed = false;
            max = 10;
            num_guesses = g_num;
          }
          else if(CheckCollisionPointRec(mousePoint, medium)){
            g_num = 5;
            medium_pressed = true;
            easy_pressed = false;
            hard_pressed = false;
            max = 50;
            num_guesses = g_num;
          }
          else if(CheckCollisionPointRec(mousePoint, hard)){
            g_num = 10;
            hard_pressed = true;
            easy_pressed = false;
            medium_pressed = false;
            max = 100;
            num_guesses = g_num;
          }
          if(CheckCollisionPointRec(mousePoint, hint)){
            hint_pressed = !hint_pressed;
          }
          if(CheckCollisionPointRec(mousePoint, type)){
            type_pressed = !type_pressed;
            num_guesses = INT_MAX;
            if(type_pressed){
              num_guesses = INT_MAX;
            }
            else{
              num_guesses = g_num;
            }
          }
        }
        
        // make the number to be guessed based on the settings above
        if(IsKeyPressed(KEY_ENTER) && (easy_pressed || medium_pressed || hard_pressed)){
          answer = rand() % max + 1;
          printf("ANSWER HERE: %d\n", answer);
          current = GAME;
        }
        break;
      case GAME: // game functionality
        if(num_guesses == 0 || won){
          current = END;
        }

        key = GetCharPressed();
        // user inputs a number
        while(key > 0){
            if((key >= 48) && (key <= 57) && (letter_count < INPUT_SIZE - 1)){
              input[letter_count] = (char)key;
              input[letter_count + 1] = '\0';
              letter_count++;
              
              i_input = i_input * 10 + to_int(key);
            }

            key = GetCharPressed();
        }
        // user presses backspace
        if(IsKeyPressed(KEY_BACKSPACE)){
            if(letter_count > 0){
              letter_count--;
              input[letter_count] = '\0';
              i_input /= 10;  
            }
        }
        // user presses enter
        if(IsKeyPressed(KEY_ENTER)){
          if(answer == i_input){
            won = true;
          }
          else{
            if(i_input < answer){
              low = true;
              high = false;
              pos_x = 0;
            }
            else{
              high = true;
              low = false;
              pos_x = 0;
            }
            num_guesses--;
          }
          reset(input, &letter_count);
          i_input = 0;
        }
  
        // hint functionality
        if(low && hint_pressed){
          pos_x++;
          if(pos_x >= screen_width){
            pos_x = 0;
            low = false;
          }
        }
        if(high && hint_pressed){
          pos_x++;
          if(pos_x >= screen_width){
            pos_x = 0;
            high = false;
          }
        }
        break;
      case END: // end functionality
        // if enter is pressed, restart game
        if(IsKeyPressed(KEY_ENTER)){
          current = START;
          reset(input, &letter_count);
          won = false;
          easy_pressed = false;
          medium_pressed = false;
          hard_pressed = false;
          type_pressed = false;
          hint_pressed = false;
          low = false;
          high = false;
          max = 0;
          num_guesses = 0;
          i_input = 0;
        }
        break;
      default:
        break;
    }

    // start putting out image
    BeginDrawing();

    ClearBackground(RAYWHITE);
    
    switch(current){
      case LOGO: // the starting screen
        DrawText("Welcome to the guessing game!", 120, 220, 20, GRAY);
        DrawText("Made by Austin Villanueva, avillann00 on github", 120, 260, 20, GRAY);
        DrawText("Press enter to continue to game", 120, 300, 20, GRAY);
        break;
      case START: // the screen where the difficulty is chosen
        // buttons for each respective button
        DrawText("Put settings, then press enter to start", 120, 220, 20 , GRAY);
        DrawRectangleRec(easy, easy_pressed ? GRAY : LIGHTGRAY);
        DrawRectangleLines(easy.x, easy.y, easy.width, easy.height, BLACK);
        DrawText("Easy", easy.x + easy.width / 2 - MeasureText("Easy", 20) / 2, easy.y + easy.height / 2 - 10, 20, BLACK);
        
        DrawRectangleRec(medium, medium_pressed ? GRAY : LIGHTGRAY);
        DrawRectangleLines(medium.x, medium.y, medium.width, medium.height, BLACK);
        DrawText("Medium", medium.x + medium.width / 2 - MeasureText("Medium", 20) / 2, medium.y + medium.height / 2 - 10, 20, BLACK);
        
        DrawRectangleRec(hard, hard_pressed ? GRAY : LIGHTGRAY);
        DrawRectangleLines(hard.x, hard.y, hard.width, hard.height, BLACK);
        DrawText("Hard", hard.x + hard.width / 2 - MeasureText("Hard", 20) / 2, hard.y + hard.height / 2 - 10, 20, BLACK);
       
        DrawRectangleRec(hint, hint_pressed ? GRAY : LIGHTGRAY);
        DrawRectangleLines(hint.x, hint.y, hint.width, hint.height, BLACK);
        DrawText("Hints on?", hint.x + hint.width / 2 - MeasureText("Hints on?", 20) / 2, hint.y + hint.height / 2 - 10, 20, BLACK);
        
        DrawRectangleRec(type, type_pressed ? GRAY : LIGHTGRAY);
        DrawRectangleLines(type.x, type.y, type.width, type.height, BLACK);
        DrawText("Unlimited Guesses?", type.x + type.width / 2 - MeasureText("Unlimited Guesses?", 20) / 2, type.y + type.height / 2 - 10, 20, BLACK);
        break;
      case GAME: // where the game is actuall played
        DrawText("Guess a number then press enter", 120, 220, 20, GRAY);
        DrawRectangleLines(120, 320, 200, 40, GRAY);
        DrawText(input, 130, 330, 20, BLACK);
        if(low && hint_pressed){
          DrawText("Too low", pos_x, 400, 20, GRAY);
        }
        if(high && hint_pressed){
          DrawText("Too high", pos_x, 400, 20, GRAY);
        }
        break;

      case END: // the ending screen
        DrawText("THE END!", 120, 220, 20, GRAY);
        if(won){
          DrawText("YOU WON", 120, 320, 20, GRAY);
        }
        else{
          DrawText("NICE TRY", 120, 320, 20, GRAY);
        }
        DrawText("PLAY AGAIN?(ENTER)", 120, 420, 20, GRAY);
      default:
        break;
    }

    // end the drawing
    EndDrawing();
  }

  // closes the window
  CloseWindow();

  // return 
  return 0;
}
