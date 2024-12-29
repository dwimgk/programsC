#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
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
        char input;
        system("cls");
        printf("\n");
        printf("%s    ████████%s", color_green, color_off);printf("%s  ██████ %s", color_yellow, color_off);printf("%s████████ %s", color_red, color_off);printf("%s ██████   %s", color_purple, color_off);printf("%s ██████ %s", color_pink, color_off);printf("%s ███████%s\n", color_cyan, color_off);
        printf("%s       ██   %s", color_green, color_off);printf("%s  ██     %s", color_yellow, color_off);printf("%s   ██    %s", color_red, color_off);printf("%s ██   ██  %s", color_purple, color_off);printf("%s   ██   %s", color_pink, color_off);printf("%s ██ %s\n", color_cyan, color_off);
        printf("%s       ██   %s", color_green, color_off);printf("%s  ██████ %s", color_yellow, color_off);printf("%s   ██    %s", color_red, color_off);printf("%s ██████   %s", color_purple, color_off);printf("%s   ██   %s", color_pink, color_off);printf("%s ███████%s\n", color_cyan, color_off);
        printf("%s       ██   %s", color_green, color_off);printf("%s  ██     %s", color_yellow, color_off);printf("%s   ██    %s", color_red, color_off);printf("%s ██   ██  %s", color_purple, color_off);printf("%s   ██   %s", color_pink, color_off);printf("%s      ██ %s  \n", color_cyan, color_off);
        printf("%s       ██   %s", color_green, color_off);printf("%s  ██████ %s", color_yellow, color_off);printf("%s   ██    %s", color_red, color_off);printf("%s ██    ██ %s", color_purple, color_off);printf("%s ██████ %s", color_pink, color_off);printf("%s ███████%s\n", color_cyan, color_off);
        printf("\n");
        printf("\n");
        printf("\n");
        printf("1. PLAY\n");
        printf("2. Scoreboard\n");
        printf("3. Exit program\n");
        printf("What do you wish to do? ");
        scanf(" %c", &input);
        if (input == '1')
        {
            play();
        }
        else if (input == '2')
        {
            scoreboard();
        }
        else if (input == '3')
        {
            printf("\nGoodbye :)\n");
            break;
        }
        else
        {
            printf("\nInvalid input :(, please follow the guidelines :)\n");
            sleep(2);
        }
    }
    return 0;
}

