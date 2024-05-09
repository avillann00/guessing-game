// TODO: MAKE GUESSING FUNCTIONALITY, ADD MUSIC? ADD PICTURES?

// header files
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>
// gui library
#include <raylib.h>

// the different screens that will be shown
typedef enum screens{LOGO = 0, START = 1, GAME = 2, END = 3} screens;

// main function
int main(){
  // window height and width
  const int screen_width = 800;
  const int screen_height = 450;

  // set the current screen
  screens current = LOGO;

  // bool to check if the user won
  bool won = false;

  // initializes a window
  InitWindow(screen_width, screen_height, "basic window");
  
  // rectangle structs for all the buttons
  default:
  Rectangle easy = {
    screenWidth / 2 - 100, screenHeight / 2 - 50, 200, 100);
  };
  Rectangle medium = {
    screenWidth / 2 - 100, screenHeight / 2 - 50, 200, 100);
  };
  Rectangle hard = {
    screenWidth / 2 - 100, screenHeight / 2 - 50, 200, 100);
  };
  Rectangle hint = {
    screenWidth / 2 - 100, screenHeight / 2 - 150, 200, 100);
  };
  Rectangle type = {
    screenWidth / 2 - 100, screenHeight / 2 - 250, 200, 100);
  };
  
  // bools to check if a button is pressed
  bool easy_pressed = false;
  bool medium_pressed = false;
  bool hard_pressed = false;
  bool type_pressed = false;
  bool hint_pressed = false;

  // while loop to keep the window open until closed by user
  while(WindowShouldClose()){
    // handles updating the pages (buttons)
    switch(current){
      case LOGO:
        if(IsKeyPressed(KEY_ENTER)){
          current = START;
        }
      case START: 
        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
          Vector2 mousePoint = GetMousePosition();
          if(CheckCollisionPointRec(mousePoint, easy)){
            easy_pressed = true;
            medium_pressed = false;
            hard_pressed = false;
          }
          if(CheckCollisionPointRec(mousePoint, medium)){
            medium_pressed = true;
            easy_pressed = false;
            hard_pressed = false;
          }
          if(CheckCollisionPointRec(mousePoint, hard)){
            hard_pressed = true;
            easy_pressed = false;
            medium_pressed = false;
          }
          if(CheckCollisionPointRec(mousePoint, hint)){
            hint_pressed = true;
          }
          if(CheckCollisionPointRec(mousePoint, type)){
            type_pressed = true;
          }
        }
        if(IsKeyPressed(KEY_ENTER)){
          current = GAME;
        }
        break;
      case GAME:

      case END:
        if(IsKeyPressed(KEY_ENTER)){
          current = START;
        }
      default:
       break;
    }

    // start putting out image
    BeginDrawing();

    ClearBackground(RAYWHITE);
    
    switch(current){
      case LOGO: // the starting screen

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
      case GAME: // where the game is actuall played

      case END: // the ending screen
        DrawText("THE END!", 120, 220, 20, GRAY);
        if(won){
          DrawText("YOU WON", 120, 320, 20, GRAY);
        }
        else{
          DrawText("NICE TRY", 120, 420, 20, GRAY);
        }
        DrawText("PLAY AGAIN?", 120, 450, 20, GRAY);
      default:
        break;
    }

    // end the drawing
    EndDrawing;
  }

  // closes the window
  CloseWindow();

  // return 
  return 0;
}
