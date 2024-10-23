#include <ctype.h>
#include <cs50.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int Letters(string text);
int Words(string text);
int Sentences(string text);

int main(void)
{
    string text = get_string("Text: ");
    string input[strlen(text)];

    int letters = Letters(text);
    //printf("%i\n", letters);
    int words = Words(text);
    //printf("%i\n", words);
    int sentences = Sentences(text);
    //printf("%i\n", sentences);
    float L =(float) letters/words*100;
    float S =(float) sentences/words*100;
    float index = 0.0588 * L - 0.296 * S - 15.8;
    printf("Grade: ");
    if(index >=16)
    {
        printf("16+\n");
    }
    else if(index <1)
    {
        printf("Before 1\n");
    }
    else
    {
        printf("%i\n",(int) round(index));
    }
}
int Letters(string text)
{
    int letters = 0;
    int len = strlen(text);
    for(int i=0;  i < len; i++)
    {
        if(text[i] != ' ')
        {
            letters++;
        }
    }
    return letters;
}
int Words(string text)
{
    int words=1;
    int len = strlen(text);
    for(int i=0;  i < len; i++)
    {
        if(text[i] == ' ')
        {
            words++;
        }
    }
    return words;
}
int Sentences(string text)
{
    int sentences=0;
    int len = strlen(text);
    for(int i=0;  i < len; i++)
    {
        if(text[i] == '.' || text[i] == '!' || text[i] == '?')
        {
            sentences++;
        }
    }
    return sentences;
}
