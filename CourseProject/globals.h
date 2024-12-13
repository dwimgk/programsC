#ifndef GLOBALS_H
#define GLOBALS_H

#define GRID_ROWS 21
#define GRID_COLS 22
#define ALL_ROTATIONS 4
#define TETROMINO_ROWS 4
#define TETROMINO_COLS 8

extern int pos_row;
extern int pos_col;
extern int current_shape[4][4][8];
extern bool current_shape_isplaced;
extern bool key_pressed;
extern bool cannot_move_to_right;
extern bool cannot_move_to_left;
extern int rotation;
extern int start_pos_row;
extern int start_pos_col;
extern bool is_I;
extern bool is_O;
extern char* player;
extern int score;
extern bool game_stop;
extern int playfield[21][22];
extern int non_dynamic_playfield[21][22];

extern const char *color_white;
extern const char *color_red ;
extern const char *color_green;
extern const char *color_yellow ;
extern const char *color_purple ;
extern const char *color_cyan ;
extern const char *color_orange ;
extern const char *color_pink ;
extern const char *color_off ;


extern const int shapes_S[4][TETROMINO_ROWS][TETROMINO_COLS];
extern const int shapes_O[4][TETROMINO_ROWS][TETROMINO_COLS];
extern const int shapes_Z[4][TETROMINO_ROWS][TETROMINO_COLS];
extern const int shapes_I[4][TETROMINO_ROWS][TETROMINO_COLS];
extern const int shapes_L[4][TETROMINO_ROWS][TETROMINO_COLS];
extern const int shapes_J[4][TETROMINO_ROWS][TETROMINO_COLS];
extern const int shapes_T[4][TETROMINO_ROWS][TETROMINO_COLS];
    

#endif  // GLOBALS_H
