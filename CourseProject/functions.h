#ifndef FUNCTIONS_H
#define FUNCTIONS_H



void print_playfield();
void game_over();


void clear_input();
void bottom_collision(int shape_row, int shape_col);
void left_collision(int shape_row, int shape_col);
void right_collision(int shape_row, int shape_col);
void proccess_input();
void shape_initialiser();
void position_shapes();
void rearranger(int row_to_clear);
void line_checker();

void end_screen();

void game_init();
void play();
void scoreboard();

#endif  // FUNCTIONS_H