#define TETROMINO_ROWS 4
#define TETROMINO_COLS 6

// -\033- is called escape character -> ESC (ASCII 27). After it you write -[- called CSI -> controle sequence introducer,
// -31- is the color as seen above, -m- tells the terminal to apply the color
const char *color_white = "\033[37m";
// id 1
const char *color_red = "\033[31m";
// id 2
const char *color_green = "\033[32m";
// id 3
const char *color_yellow = "\033[33m";
// id 4
const char *color_purple = "\033[35m";
// id 5
const char *color_cyan = "\033[36m";
// id 6
const char *color_orange = "\033[38;5;214m"; // Extended color for orange
//id 7
const char *color_pink = "\033[38;5;213m";   // Extended color for pink
//id 8
const char *color_off = "\033[0m"; // Reset to default


const int shapes_S[4][TETROMINO_ROWS][TETROMINO_COLS] = {
    {
        {0, 0, 0, 0, 0, 0},

        {0, 0, 0, 0, 0, 0},

        {0, 0, 2, 2, 2, 2},

        {2, 2, 2, 2, 0, 0}
    },
    {
        {0, 0, 0, 0, 0, 0},

        {2, 2, 0, 0, 0, 0},

        {2, 2, 2, 2, 0, 0},

        {0, 0, 2, 2, 0, 0}
    },
    {
        {0, 0, 0, 0, 0, 0},

        {0, 0, 0, 0, 0, 0},

        {0, 0, 2, 2, 2, 2},

        {2, 2, 2, 2, 0, 0}
    },
    {
        {0, 0, 0, 0, 0, 0},

        {2, 2, 0, 0, 0, 0},

        {2, 2, 2, 2, 0, 0},

        {0, 0, 2, 2, 0, 0}
    }
};
const int shape_O[TETROMINO_ROWS][TETROMINO_COLS] = {

    {0, 0, 0, 0, 0, 0},

    {0, 0, 0, 0, 0, 0},

    {4, 4, 4, 4, 0, 0},

    {4, 4, 4, 4, 0, 0}

};
const int shape_Z[TETROMINO_ROWS][TETROMINO_COLS] = {

    {0, 0, 0, 0, 0, 0},

    {0, 0, 0, 0, 0, 0},

    {3, 3, 3, 3, 0, 0},

    {0, 0, 3, 3, 3, 3}

};