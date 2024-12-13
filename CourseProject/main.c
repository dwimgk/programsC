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
            //break;
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

