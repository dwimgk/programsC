#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>
#include <stdbool.h>
#include <unistd.h>
#include <time.h>
#include <conio.h>

#include "functions.h"
#include "globals.h"

// gcc -o tetris.exe main.c functions.c globals.c

void play();
void game_init();
void scoreboard();

int main()
{
    while (true)
    {
        int input;
        system("cls");
        printf("%s████████%s", color_green, color_off);printf("%s  ██████ %s", color_yellow, color_off);printf("%s████████ %s", color_red, color_off);printf("%s ██████   %s", color_purple, color_off);printf("%s ██████ %s", color_pink, color_off);printf("%s ███████%s\n", color_cyan, color_off);
        printf("%s   ██   %s", color_green, color_off);printf("%s  ██     %s", color_yellow, color_off);printf("%s   ██    %s", color_red, color_off);printf("%s ██   ██  %s", color_purple, color_off);printf("%s   ██   %s", color_pink, color_off);printf("%s ██ %s\n", color_cyan, color_off);
        printf("%s   ██   %s", color_green, color_off);printf("%s  ██████ %s", color_yellow, color_off);printf("%s   ██    %s", color_red, color_off);printf("%s ██████   %s", color_purple, color_off);printf("%s   ██   %s", color_pink, color_off);printf("%s ███████%s\n", color_cyan, color_off);
        printf("%s   ██   %s", color_green, color_off);printf("%s  ██     %s", color_yellow, color_off);printf("%s   ██    %s", color_red, color_off);printf("%s ██   ██  %s", color_purple, color_off);printf("%s   ██   %s", color_pink, color_off);printf("%s      ██ %s  \n", color_cyan, color_off);
        printf("%s   ██   %s", color_green, color_off);printf("%s  ██████ %s", color_yellow, color_off);printf("%s   ██    %s", color_red, color_off);printf("%s ██    ██ %s", color_purple, color_off);printf("%s ██████ %s", color_pink, color_off);printf("%s ███████%s\n", color_cyan, color_off);
        printf("\n");
        printf("\n");
        printf("\n");
        printf("1. PLAY\n");
        printf("2. Scoreboard\n");
        printf("3. Exit program\n");
        printf("What do you wish to do? ");
        scanf("%d", &input);

        if (input == 1)
        {
            play();
            break;
        }
        else if (input == 2)
        {
            scoreboard();
            //scanf("%d", &input);
        }
        else if (input == 3)
        {
            printf("\nGoodbye :)\n");
            break;
        }
        else
        {
            printf("\nInvalid input :(, please follow the guidelines :)\n");
            //scanf("%d", &input);
        }
    }

    // free(player);
    return 0;
}

void scoreboard()
{
    int return_input;
    system("cls");
    FILE *file = fopen("score.txt", "r");
    if (file == NULL)
    {
        perror("error opening file");
        return;
    }

    char ch;
    while ((ch = fgetc(file)) != EOF)
    {
        putchar(ch);
    }

    fclose(file);
    printf("TO RETURN TO THE MENU PLEASE TYPE 1 --> ");
    while (true)
    {
        scanf("%d", &return_input);
        if (return_input == 1)
        {
            return;
        }
        else
        {
            printf("\n Cannot return, input is invalid :(\n");
        }
    }
}
void play()
{
    char player[50];

    printf("Enter player name: ");
    scanf("%49s", player);
    // if (player == NULL)
    // {
    //     printf("could not allocate memory\n");
    //     return;
    // }

    // printf("Enter player name: ");

    // fgets(player, 100, stdin);
    size_t length = strlen(player);
    if (length > 0 && player[length - 1] == '\n')
    {
        player[length - 1] = '\0';
    }

    game_init();

    FILE *file = fopen("score.txt", "a");
    if (file == NULL)
    {
        perror("failed to open file");
        return;
    }
    fprintf(file, "Player: %s\n", player);
    fprintf(file, "Score: %d\n\n", score);

    // Close the file
    fclose(file);

    return;
}
void game_init()
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
            return;
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
    }
    return;
}