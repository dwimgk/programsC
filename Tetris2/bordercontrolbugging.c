#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>
#include <stdbool.h>
#include <unistd.h>
#include <time.h>
#include <conio.h>
#include "tetramino.h"

#define GRID_ROWS 21
#define GRID_COLS 22
#define ALL_ROTATIONS 4

// terminal top left corner is (1,1)
int pos_row;
int pos_col;
int current_shape[ALL_ROTATIONS][TETROMINO_ROWS][TETROMINO_COLS];
bool current_shape_isplaced;
bool cannot_move_to_right;
bool cannot_move_to_left;
bool key_pressed = false;
int rotation = 0;

void print_playfield();
void shape_initialiser();
void position_shapes();
void clear_input();
void proccess_input();

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
    cannot_move_to_right = false;
    cannot_move_to_left = false;

    // terminal top left corner is (1,1)
    int start_pos_row = 0;
    int start_pos_col = 9;
    pos_row = start_pos_row;
    pos_col = start_pos_col;

    shape_initialiser();

    while (game_running)
    {

        position_shapes();
        print_playfield();
        if (current_shape_isplaced)
        {
            memcpy(non_dynamic_playfield, playfield, sizeof(non_dynamic_playfield));
            shape_initialiser();
            pos_row = start_pos_row;
            pos_col = start_pos_col;
            current_shape_isplaced = false;
            cannot_move_to_right = false;
            cannot_move_to_left = false;
        }
        else if (!current_shape_isplaced)
        {
            memcpy(playfield, non_dynamic_playfield, sizeof(playfield));
            pos_row++;
        }
        long sleep_time = 250000;
        usleep(sleep_time);
        // 50 000 microseconds = 0.5s

        proccess_input();
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
    if (kbhit() != 0 && !key_pressed)
    {
        int detect = getch();
        if (detect == 224)
        {
            key_pressed = true;
            int input = getch();
            switch (input)
            {
                // left \/
            case 75:
                if (!cannot_move_to_left)
                {
                    pos_col -= 2;
                    if (cannot_move_to_right)
                    {
                        cannot_move_to_right = false;
                    }
                    break;
                }
                // right \/
            case 77:
                if (!cannot_move_to_right)
                {
                    pos_col += 2;
                    if (cannot_move_to_left)
                    {
                        cannot_move_to_left = false;
                    }
                    break;
                }
            default:
                break;
            }
        }
    }
}

void shape_initialiser()
{
    rotation = 0;
    int random_number = rand() % 100 + 1;
    printf("%i", random_number);
    if (random_number > 0 && random_number < 14)
    {
        memcpy(current_shape, shapes_O, sizeof(current_shape));
    }
    else if (random_number >= 14 && random_number < 28)
    {
        memcpy(current_shape, shapes_I, sizeof(current_shape));
    }
    else if (random_number >= 28 && random_number < 42)
    {
        memcpy(current_shape, shapes_S, sizeof(current_shape));
    }
    else if (random_number >= 42 && random_number < 56)
    {
        memcpy(current_shape, shapes_Z, sizeof(current_shape));
    }
    else if (random_number >= 56 && random_number < 70)
    {
        memcpy(current_shape, shapes_L, sizeof(current_shape));
    }
    else if (random_number >= 70 && random_number < 84)
    {
        memcpy(current_shape, shapes_J, sizeof(current_shape));
    }
    else if (random_number >= 84 && random_number < 100)
    {
        memcpy(current_shape, shapes_T, sizeof(current_shape));
    }
}

void position_shapes()
{
    for (int shape_row = 0; shape_row <= TETROMINO_ROWS; shape_row++)
    {
        for (int shape_col = 0; shape_col <= TETROMINO_COLS; shape_col++)
        {
            if (current_shape[rotation][shape_row][shape_col] != 0 && shape_row < TETROMINO_ROWS && shape_col < TETROMINO_COLS)
            {
                playfield[shape_row + pos_row][shape_col + pos_col] = current_shape[rotation][shape_row][shape_col];
            }
            if (shape_row == TETROMINO_ROWS && shape_col < TETROMINO_COLS)
            {
                if (current_shape[rotation][shape_row - 1][shape_col] != 0)
                {
                    if (playfield[shape_row + pos_row][shape_col + pos_col] != 0)
                    {
                        current_shape_isplaced = true;
                    }
                }
                else if (current_shape[rotation][shape_row - 2][shape_col] != 0)
                {
                    if (playfield[shape_row + pos_row - 1][shape_col + pos_col] != 0)
                    {
                        current_shape_isplaced = true;
                    }
                }
                else if (current_shape[rotation][shape_row - 3][shape_col] != 0)
                {
                    if (playfield[shape_row + pos_row - 2][shape_col + pos_col] != 0)
                    {
                        current_shape_isplaced = true;
                    }
                }
            }

            if (shape_col == 0)
            {
                if (non_dynamic_playfield[shape_row + pos_row][shape_col + pos_col - 1] != 0)
                {
                    if (current_shape[rotation][shape_row][shape_col] != 0)
                    {
                        cannot_move_to_left = true;
                    }
                }
                else if (non_dynamic_playfield[shape_row + pos_row][shape_col + pos_col +1] != 0)
                {
                    if (current_shape[rotation][shape_row][shape_col +3] != 0)
                    {
                        cannot_move_to_left = true;
                    }
                }
                else if (non_dynamic_playfield[shape_row + pos_row][shape_col + pos_col + 5] != 0)
                {
                    if (current_shape[rotation][shape_row][shape_col + 3] != 0)
                    {
                        cannot_move_to_left = true;
                    }
                }
                //else if (non_dynamic_playfield[shape_row + pos_row][shape_col + pos_col + 7] != 0)
                // {
                //     if (current_shape[rotation][shape_row][shape_col + 5] != 0)
                //     {
                //         cannot_move_to_left = true;
                //     }
                // }
            }
            if (shape_col == TETROMINO_COLS)
            {
                if (non_dynamic_playfield[shape_row + pos_row][shape_col + pos_col] != 0)
                {
                    if (current_shape[rotation][shape_row][shape_col - 1] != 0)
                    {
                        cannot_move_to_right = true;
                    }
                }
                else if (non_dynamic_playfield[shape_row + pos_row][shape_col + pos_col - 1] != 0)
                {
                    if (current_shape[rotation][shape_row][shape_col - 3] != 0)
                    {
                        cannot_move_to_right = true;
                    }
                }
                else if (non_dynamic_playfield[shape_row + pos_row][shape_col + pos_col - 3] != 0)
                {
                    if (current_shape[rotation][shape_row][shape_col - 5] != 0)
                    {
                        cannot_move_to_right = true;
                    }
                }
                else if (non_dynamic_playfield[shape_row + pos_row][shape_col + pos_col - 5] != 0)
                {
                    if (current_shape[rotation][shape_row][shape_col - 7] != 0)
                    {
                        cannot_move_to_right = true;
                    }
                }
            }
        }
    }
}

void print_playfield()
{
    printf("\n");
    printf("\n");
    printf("\n");

    for (int i = 0; i < GRID_ROWS; i++)
    {
        for (int j = 0; j < GRID_COLS; j++)
        {
            if (playfield[i][j] == 1) // print your grid
            {
                if (i == GRID_ROWS - 1)
                {
                    printf("%s▀%s", color_white, color_off);
                }
                else
                {
                    printf("%s█%s", color_white, color_off);
                }
            }
            else if (playfield[i][j] == 4) // print your grid
            {
                printf("%s█%s", color_yellow, color_off);
            }
            else if (playfield[i][j] == 3) // print your grid
            {
                printf("%s█%s", color_green, color_off);
            }
            else if (playfield[i][j] == 2) // print your grid
            {
                printf("%s█%s", color_red, color_off);
            }
            else if (playfield[i][j] == 5) // print your grid
            {
                printf("%s█%s", color_purple, color_off);
            }
            else if (playfield[i][j] == 6) // print your grid
            {
                printf("%s█%s", color_cyan, color_off);
            }
            else if (playfield[i][j] == 7) // print your grid
            {
                printf("%s█%s", color_orange, color_off);
            }
            else if (playfield[i][j] == 8) // print your grid
            {
                printf("%s█%s", color_pink, color_off);
            }
            else
            {
                printf(" ");
            }
        }
        printf("\n");
    }
}