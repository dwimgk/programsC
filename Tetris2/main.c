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

void print_playfield();
void shape_initialiser();
void position_shapes();
void clear_input();
void proccess_input();
void bottom_collision(int shape_row, int shape_col);
void left_collision(int shape_row, int shape_col);
void right_collision(int shape_row, int shape_col);

void line_checker();
void rearranger(int row_to_clear);

void game_over();
void end_screen();

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

void clear_input()
{
    if (key_pressed)
    {
        while (kbhit())
        {
            getch();
            // if (kbhit() == 0)
            // {
            //     break;
            // }
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
            {
                if (!cannot_move_to_left)
                {
                    pos_col -= 2;
                    if (cannot_move_to_right)
                    {
                        cannot_move_to_right = false;
                    }
                }
                break;
            }
                // right \/
            case 77:
            {

                if (!cannot_move_to_right)
                {
                    pos_col += 2;
                    if (cannot_move_to_left)
                    {
                        cannot_move_to_left = false;
                    }
                }
                break;
            }
            default:
                break;
            }
        }
        else if (detect == 32)
        {
            key_pressed = true;

            if (is_O)
            {
                return;
            }
            if (cannot_move_to_right)
            {
                pos_col -= 2;
            }
            if (cannot_move_to_right && is_I)
            {
                pos_col -= 5;
            }
            if (cannot_move_to_left && cannot_move_to_right)
            {
                return;
            }
            rotation++;
            if (rotation >= 4)
            {
                rotation = 0;
            }
        }
    }
}

void shape_initialiser()
{
    game_over();
    // if(game_stop)
    // {
    //     return;
    // }

    is_I = false;
    is_O = false;
    cannot_move_to_right = false;
    cannot_move_to_left = false;
    rotation = 0;
    int random_number = rand() % 100 + 1;
    // printf("%i", random_number);
    if (random_number >= 0 && random_number < 14)
    {
        memcpy(current_shape, shapes_O, sizeof(current_shape));
        is_O = true;
    }
    else if (random_number >= 14 && random_number < 28)
    {
        memcpy(current_shape, shapes_I, sizeof(current_shape));
        is_I = true;
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
    else if (random_number >= 84 && random_number <= 100)
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
                // if(playfield[shape_row + pos_row+1][shape_col + pos_col]){}
                playfield[shape_row + pos_row][shape_col + pos_col] = current_shape[rotation][shape_row][shape_col];
            }
            if (shape_row == TETROMINO_ROWS && shape_col < TETROMINO_COLS)
            {
                bottom_collision(shape_row, shape_col);
            }
            left_collision(shape_row, shape_col);
            right_collision(shape_row, shape_col);
        }
    }
}
void bottom_collision(int shape_row, int shape_col)
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
void left_collision(int shape_row, int shape_col)
{
    if (shape_col == 0)
    {
        if (non_dynamic_playfield[shape_row + pos_row][shape_col + pos_col - 1] != 0)
        {
            if (current_shape[rotation][shape_row][shape_col] != 0)
            {
                cannot_move_to_left = true;
            }
        }
        else if (non_dynamic_playfield[shape_row + pos_row][shape_col + pos_col + 0] != 0)
        {
            if (current_shape[rotation][shape_row][shape_col + 2] != 0)
            {
                cannot_move_to_left = true;
            }
        }
        else if (non_dynamic_playfield[shape_row + pos_row][shape_col + pos_col + 2] != 0)
        {
            if (current_shape[rotation][shape_row][shape_col + 4] != 0)
            {
                cannot_move_to_left = true;
            }
        }
    }
}
void right_collision(int shape_row, int shape_col)
{
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

void print_playfield()
{
    printf("\033[H\033[J");
    printf("          %i", score);
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

void line_checker()
{
    bool row_full = true;
    int row_to_clear = 0;
    for (int row_counter = GRID_ROWS - 2; row_counter >= 0; row_counter--)
    {
        row_full = true;
        for (int col_checker = 1; col_checker < GRID_COLS - 1; col_checker++)
        {
            if (non_dynamic_playfield[row_counter][col_checker] == 0)
            {
                row_full = false;
            }
        }
        if (row_full)
        {
            row_to_clear = row_counter;
            rearranger(row_to_clear);
            // line_checker();
        }
    }
}
void rearranger(int row_to_clear)
{
    score++;
    for (int current_row = row_to_clear; current_row >= 0; current_row--)
    {
        for (int current_col = 1; current_col < GRID_COLS - 1; current_col++)
        {
            if (current_row != 0)
            {
                non_dynamic_playfield[current_row][current_col] = non_dynamic_playfield[current_row - 1][current_col];
            }
            else
            {
                non_dynamic_playfield[current_row][current_col] = 0;
            }
        }
    }
}

void game_over()
{
    for (int shape_row = 0; shape_row < TETROMINO_ROWS; shape_row++)
    {
        for (int shape_col = 0; shape_col < TETROMINO_COLS; shape_col++)
        {
            if (non_dynamic_playfield[shape_row + start_pos_row][shape_col + start_pos_col] != 0)
            {
                game_stop = true;
            }
        }
    }
}

void end_screen()
{
    system("cls");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("                                            Block out !!!");
    printf("\n");
    printf("\n");
    printf("                                 Game is over, thank you for playing ! :)");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
}