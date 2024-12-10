#ifndef GLOBALS_H
#define GLOBALS_H

#include <stdbool.h>

#define GRID_ROWS 21
#define GRID_COLS 22
#define ALL_ROTATIONS 4
#define TETROMINO_ROWS 4
#define TETROMINO_COLS 8

extern int pos_row;
extern int pos_col;
extern int current_shape[ALL_ROTATIONS][TETROMINO_ROWS][TETROMINO_COLS];
extern bool current_shape_isplaced;
extern bool key_pressed;
extern bool cannot_move_to_right;
extern bool cannot_move_to_left;
extern int rotation;
extern int start_pos_row;
extern int start_pos_col;
extern bool is_I;
extern bool is_O;
extern int score;
extern bool game_stop;
extern int playfield[GRID_ROWS][GRID_COLS];
extern int non_dynamic_playfield[GRID_ROWS][GRID_COLS];

extern const char *color_white;
// id 1
extern const char *color_red ;
// id 2
extern const char *color_green;
// id 3
extern const char *color_yellow ;
// id 4
extern const char *color_purple ;
// id 5
extern const char *color_cyan ;
// id 6
extern const char *color_orange ; // Extended color for orange
//id 7
extern const char *color_pink ;   // Extended color for pink
//id 8
extern const char *color_off ; // Reset to default


extern const int shapes_S[4][TETROMINO_ROWS][TETROMINO_COLS];
extern const int shapes_O[4][TETROMINO_ROWS][TETROMINO_COLS];
extern const int shapes_Z[4][TETROMINO_ROWS][TETROMINO_COLS];
extern const int shapes_I[4][TETROMINO_ROWS][TETROMINO_COLS];
extern const int shapes_L[4][TETROMINO_ROWS][TETROMINO_COLS];
extern const int shapes_J[4][TETROMINO_ROWS][TETROMINO_COLS];
extern const int shapes_T[4][TETROMINO_ROWS][TETROMINO_COLS];

#endif  // GLOBALS_H
