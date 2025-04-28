#include "raylib.h"
#include <stdlib.h>
#include <time.h>

typedef enum { NONE = -1, ROCK, PAPER, SCISSORS } Choice;
typedef enum { WAITING, WIN, LOSE, DRAW } Result;

int GetComputerChoice() {
    return rand() % 3;
}

Result GetGameResult(int player, int computer) {
    if (player == computer) return DRAW;
    if ((player == ROCK && computer == SCISSORS) ||
        (player == PAPER && computer == ROCK) ||
        (player == SCISSORS && computer == PAPER)) return WIN;
    return LOSE;
}

const char* GetChoiceText(int choice) {
    switch (choice) {
        case ROCK: return "Rock";
        case PAPER: return "Paper";
        case SCISSORS: return "Scissors";
        default: return "";
    }
}

int main() {
    InitWindow(800, 600, "Камень Ножницы Бумага Выбирай :)");
    SetTargetFPS(60);
    srand(time(NULL));

    Rectangle rockBtn = { 150, 500, 150, 60 };
    Rectangle paperBtn = { 325, 500, 150, 60 };
    Rectangle scissorsBtn = { 500, 500, 150, 60 };

    int playerChoice = NONE;
    int computerChoice = NONE;
    Result result = WAITING;

    while (!WindowShouldClose()) {
        if (result == WAITING) {
            if (IsKeyPressed(KEY_R)) playerChoice = ROCK;
            else if (IsKeyPressed(KEY_P)) playerChoice = PAPER;
            else if (IsKeyPressed(KEY_S)) playerChoice = SCISSORS;

            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                Vector2 mouse = GetMousePosition();
                if (CheckCollisionPointRec(mouse, rockBtn)) playerChoice = ROCK;
                if (CheckCollisionPointRec(mouse, paperBtn)) playerChoice = PAPER;
                if (CheckCollisionPointRec(mouse, scissorsBtn)) playerChoice = SCISSORS;
            }

            if (playerChoice != NONE) {
                computerChoice = GetComputerChoice();
                result = GetGameResult(playerChoice, computerChoice);
            }
        }

        if (result != WAITING && IsKeyPressed(KEY_SPACE)) {
            playerChoice = NONE;
            computerChoice = NONE;
            result = WAITING;
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawText("Rock Paper Scissors!", 240, 50, 30, DARKBLUE);

        DrawRectangleRec(rockBtn, LIGHTGRAY);
        DrawText("Rock (R)", rockBtn.x + 20, rockBtn.y + 15, 20, ORANGE);

        DrawRectangleRec(paperBtn, LIGHTGRAY);
        DrawText("Paper (P)", paperBtn.x + 20, paperBtn.y + 15, 20, RED);

        DrawRectangleRec(scissorsBtn, LIGHTGRAY);
        DrawText("Scissors (S)", scissorsBtn.x + 10, scissorsBtn.y + 15, 20, GREEN);

        DrawText("Choose your move (R, P, S or Click):", 210, 200, 20, GRAY);

        if (playerChoice != NONE) {
            DrawText(TextFormat("You chose: %s", GetChoiceText(playerChoice)), 50, 250, 20, DARKGREEN);
            DrawText(TextFormat("Computer chose: %s", GetChoiceText(computerChoice)), 50, 280, 20, MAROON);
        }

        if (result == WIN) DrawText("You Win!", 350, 350, 30, GREEN);
        else if (result == LOSE) DrawText("You Lose!", 340, 350, 30, RED);
        else if (result == DRAW) DrawText("Draw!", 370, 350, 30, ORANGE);
        else DrawText("Make your choice!", 310, 400, 20, GRAY);

        if (result != WAITING)
            DrawText("Press SPACE to play again", 270, 450, 20, DARKGRAY);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
