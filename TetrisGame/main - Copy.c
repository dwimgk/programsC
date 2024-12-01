#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>
#include <stdbool.h>
#include <unistd.h>
#include <time.h>
#include <conio.h>
#include "tetramino.h"

// shapes:
//  █ ▄ ▀ - I recommend you use the first one only, size will be consistent

// Foreground Colors:

//     30 - Black
//     31 - Red
//     32 - Green
//     33 - Yellow
//     34 - Blue
//     35 - Magenta
//     36 - Cyan
//     37 - White

// Background Colors:

//     40 - Black
//     41 - Red
//     42 - Green
//     43 - Yellow
//     44 - Blue
//     45 - Magenta
//     46 - Cyan
//     47 - White

// #define TETROMINO_ROWS 4
// #define TETROMINO_COLS 6
#define MAX_TETROMINOS 100

#define GRID_ROWS 21
#define GRID_COLS 22

typedef struct
{
    int shape[TETROMINO_ROWS][TETROMINO_COLS];
    int y_row;
    int x_col;
    const char *color;
    bool placed;
} Tetromino;

// dynamic arr TODO:
Tetromino tetrominos[MAX_TETROMINOS];
int current_tetromino = 0;
bool key_pressed = false;

void print_grid(int grid[GRID_ROWS][GRID_COLS], const char *color);
void shape_generator();
void print_shape(int shape[TETROMINO_ROWS][TETROMINO_COLS], const char *color, int row, int col);
void clear_input();
void proccess_input();

// playfield
int playfield[GRID_ROWS][GRID_COLS] = {
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},

    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},

    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},

    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},

    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    //
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},

    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},

    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},

    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},

    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    //
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},

    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},

    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},

    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},

    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    //
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},

    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},

    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},

    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},

    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    //
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}

};
int current_state[GRID_ROWS][GRID_COLS];

int main()
{
    memcpy(current_state, playfield, sizeof(current_state));
    system("cls");

    bool game_running = true;

    // seeding with time(null) so that every random num will be different each iteration of the code
    srand(time(NULL));
    int start_pos_row = 0;
    int start_pos_col = 1;

    tetrominos[current_tetromino];
    memcpy(tetrominos[current_tetromino].shape, shape_O, sizeof(tetrominos[current_tetromino].shape));
    tetrominos[current_tetromino].y_row = start_pos_row;
    tetrominos[current_tetromino].x_col = start_pos_col;
    tetrominos[current_tetromino].color = color_green;
    tetrominos[current_tetromino].placed = false;

    while (game_running)
    {
        if (tetrominos[current_tetromino].placed == true)
        {
            shape_generator();
        }

        print_grid(playfield, color_white);
        print_shape(tetrominos[current_tetromino].shape, tetrominos[current_tetromino].color, tetrominos[current_tetromino].y_row, tetrominos[current_tetromino].x_col);

        long sleep_time = 500000;
        usleep(sleep_time);
        // 50 000 microseconds = 0.5s
        proccess_input();

        tetrominos[current_tetromino].y_row++;
        if (tetrominos[current_tetromino].y_row + 3 == 24)
        {
            tetrominos[current_tetromino].placed = true;
            current_tetromino++;
            // shape_generator();
        }
        else
        {
        }

        clear_input();
        system("cls");
    }
    return 0;
}

void clear_input()
{
    if (key_pressed)
    {
        while (kbhit())
        {
            getch();
        }
        key_pressed = false;
    }
}

void proccess_input()
{
    if (kbhit() != 0 && getch() == 224 && !key_pressed)
    {
        key_pressed = true;
        int input = _getch();
        switch (input)
        {
        case 75:
            tetrominos[current_tetromino].x_col--;
            break;
        case 77:
            tetrominos[current_tetromino].x_col++;
            break;
        default:
            break;
        }
    };
}

void print_grid(int grid[GRID_ROWS][GRID_COLS], const char *color)
{
    printf("\n");
    printf("\n");
    printf("\n");
    const char *color_off = "\033[0m"; // Reset to default
    for (int i = 0; i < GRID_ROWS; i++)
    {
        for (int j = 0; j < GRID_COLS; j++)
        {
            if (grid[i][j] == 1) // print your grid
            {
                if (i == GRID_ROWS - 1)
                {
                    printf("%s▀%s", color, color_off);
                }
                else
                {
                    printf("%s█%s", color, color_off);
                }
            }
            else
            {
                printf(" ");
            }
        }
        printf("\n");
    }
}
void print_shape(int shape[TETROMINO_ROWS][TETROMINO_COLS], const char *color, int row, int col)
{
    // const char *color_off = "\033[0m"; // Reset to default
    // for (int i = 0; i < TETROMINO_ROWS; i++)
    // {
    //     printf("\033[%i;%iH", row, col);
    //     for (int j = 0; j < TETROMINO_COLS; j++)
    //     {
    //         if (shape[i][j] == 1) // print your square
    //         {
    //             printf("%s█%s", color, color_off);
    //         }
    //         else
    //         {
    //              printf("0");
    //         }
    //     }
    //     printf("\n");
    //     row++;
    // }
    for (int i = 0; i < TETROMINO_ROWS; i++)
    {
        for (int j = 0; j < TETROMINO_COLS; j++)
        {
            if (shape[i][j] == 1) // print your square
            {
                playfield[i][j] =1;
            }
        }
    }
}

void shape_generator()
{
    int random_number = rand() % 100 + 1;
}