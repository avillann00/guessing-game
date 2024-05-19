// TODO: ADD MUSIC? ADD PICTURES?

// header files
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
void reset(char * word){
  for(int i = 0; i < INPUT_SIZE; i++){
    word[i] = '0';
  }

  return;
}

// main function
int main(){
  // window height and width
  const int screen_width = 800;
  const int screen_height = 450;

  // the max that the random number can be
  int max;
  // the number of guesses the user gets if not unlimited
  int num_guesses;
  // the key taken #include 
  int key;
  // the number of digits in key
  int key_size = INPUT_SIZE - 1;
  // the full input of the user guess
  char input[INPUT_SIZE];
  reset(input);

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
          answer = GetRandomValue(1, max);
          current = GAME;
        }
        break;
      case GAME: // game functionality
        if(num_guesses == 0 || won){
          current = END;
        }
        // if the user enters a number put it in input
        if(strlen(input) < INPUT_SIZE - 1){
            key = GetKeyPressed();
            if(key == KEY_ENTER){
              if(answer == atoi(input)){
                won = true;
              }
              else{
                num_guesses--;
              }
              reset(input);
            }
            // user presses backspace
            else if(key == KEY_BACKSPACE && key_size < INPUT_SIZE){
              key_size++;
              input[key_size] = '0';
            }
            // user inputs a number
            else if((key >= KEY_ZERO) && (key <= KEY_NINE)){
                input[key_size] = (char)(key);
                key_size--;
            }
        }
        break;
      case END: // end functionality
        // if enter is pressed, restart game
        if(IsKeyPressed(KEY_ENTER)){
          current = START;
          reset(input);
          won = false;
            easy_pressed = false;
            medium_pressed = false;
            hard_pressed = false;
            type_pressed = false;
            hint_pressed = false;
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
        DrawText("Type a guess, then press enter", 120, 220, 20, GRAY);
        DrawRectangleLines(120, 320, 200, 40, GRAY);
        DrawText(input, 120, 330, 20, BLACK);

      case END: // the ending screen
        DrawText("THE END!", 120, 220, 20, GRAY);
        if(won){
          DrawText("YOU WON", 120, 320, 20, GRAY);
        }
        else{
          DrawText("NICE TRY", 120, 320, 20, GRAY);
        }
        DrawText("PLAY AGAIN?", 120, 420, 20, GRAY);
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
