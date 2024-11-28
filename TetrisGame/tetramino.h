#define TETROMINO_ROWS 4
#define TETROMINO_COLS 6

// -\033- is called escape character -> ESC (ASCII 27). After it you write -[- called CSI -> controle sequence introducer,
// -31- is the color as seen above, -m- tells the terminal to apply the color
const char *color_white = "\033[37m";
const char *color_red = "\033[31m";
const char *color_green = "\033[32m";
const char *color_yellow = "\033[33m";
const char *color_blue = "\033[34m";
const char *color_magenta = "\033[35m";
const char *color_cyan = "\033[36m";

// basic implementation of a tetramino grid... it could be defined in a struct in some way
int shape_S[TETROMINO_ROWS][TETROMINO_COLS] = {

    {0, 0, 0, 0, 0, 0},

    {0, 0, 0, 0, 0, 0},

    {0, 0, 1, 1, 1, 1},

    {1, 1, 1, 1, 0, 0}

};
const int shape_O[TETROMINO_ROWS][TETROMINO_COLS] = {

    {0, 0, 0, 0, 0, 0},

    {0, 0, 0, 0, 0, 0},

    {1, 1, 1, 1, 0, 0},

    {1, 1, 1, 1, 0, 0}

};
int shape_Z[TETROMINO_ROWS][TETROMINO_COLS] = {

    {0, 0, 0, 0, 0, 0},

    {0, 0, 0, 0, 0, 0},

    {1, 1, 1, 1, 0, 0},

    {0, 0, 1, 1, 1, 1}

};