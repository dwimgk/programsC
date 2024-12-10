#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>
#include <stdbool.h>
#include <unistd.h>
#include <time.h>
#include <conio.h>
//#include "tetramino.h"
#include "functions.h"
#include "globals.h"

// #define GRID_ROWS 21
// #define GRID_COLS 22
// #define ALL_ROTATIONS 4

// terminal top left corner is (1,1)
int pos_row;
int pos_col;
int current_shape[ALL_ROTATIONS][TETROMINO_ROWS][TETROMINO_COLS];
bool current_shape_isplaced;
bool key_pressed = false;
bool cannot_move_to_right;
bool cannot_move_to_left;
int rotation = 0;
// terminal top left corner is (1,1)
int start_pos_row = 0;
int start_pos_col = 9;
bool is_I;
bool is_O;

int score = 0;

bool game_stop = false;


// playfield
int playfield[GRID_ROWS][GRID_COLS] = {
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},

    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},

    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},

    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},

    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    // 5
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},

    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},

    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},

    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},

    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    // 10
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},

    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},

    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},

    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},

    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    // 15
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},

    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},

    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},

    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},

    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    // 20
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}

};

int non_dynamic_playfield[GRID_ROWS][GRID_COLS];

int main()
{
    memcpy(non_dynamic_playfield, playfield, sizeof(non_dynamic_playfield));
    // seeding with time(null) so that every random num will be different each iteration of the code
    srand(time(NULL));

    system("cls");

    bool game_running = true;
    current_shape_isplaced = false;

    pos_row = start_pos_row;
    pos_col = start_pos_col;

    shape_initialiser();

    while (game_running)
    {
        if (game_stop)
        {
            end_screen();
            return 1;
        }

        cannot_move_to_left = false;
        cannot_move_to_right = false;

        position_shapes();
        print_playfield();
        if (current_shape_isplaced)
        {
            memcpy(non_dynamic_playfield, playfield, sizeof(non_dynamic_playfield));
            shape_initialiser();
            pos_row = start_pos_row;
            pos_col = start_pos_col;
            current_shape_isplaced = false;
        }
        else if (!current_shape_isplaced)
        {
            memcpy(playfield, non_dynamic_playfield, sizeof(playfield));
            pos_row++;
        }
        long sleep_time = 150000 - score * 20000;
        if (sleep_time < 0)
        {
            sleep_time = 0;
        }
        usleep(sleep_time);
        // 50 000 microseconds = 0.5s

        proccess_input();
        clear_input();

        line_checker();

        //system("cls");
    }
    return 0;
}
