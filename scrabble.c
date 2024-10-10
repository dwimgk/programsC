#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>

int Points[] = {1, 3 , 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};
int Score(string word);
int main()
{
    string player1 = get_string("Player1:  ");
    string player2 = get_string("Player2:  ");

    int sum1=Score(player1);
    int sum2 = Score(player2);

    if(sum1>sum2)
    {
        printf("Player 1 Wins !!!\n");
    }
    else if(sum1<sum2)
    {
        printf("Player 2 Wins !!!\n");
    }
    else
    {
        printf("Tie !!!!!!!!!\n");
    }
}

int Score(string word)
{
    int score=0;

    for(int i=0, len = strlen(word); i< len; i++)
    {
        if(isupper(word[i]))
        {
            score += Points[word[i] - 'A'];
        }
        else if(islower(word[i]))
        {
            score += Points[word[i] - 'a'];
        }
    }

    return score;
}
