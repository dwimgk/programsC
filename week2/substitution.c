#include <ctype.h>
#include <cs50.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//bool only_digits(string k);
char cipher(char p, string key);
char AlphLower[] = "abcdefghijklmnopqrstuvwxyz";
char AlphUpper[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

int main(int argc, string argv[])
{
    string k = argv[1];
    int len = strlen(k);
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    if(len != 26)
    {
        printf("key must contain 26 characters\n");
        return 1;
    }

    string p = get_string("plaintext: ");
    printf("ciphertext: ");
    for(int i = 0; i < strlen(p); i++)
    {
        printf("%c",cipher(p[i], k));
    }
    printf("\n");
    return 0;
}

char cipher(char p, string k)
{
    char indexed=p;
    for(int i=0; i<26; i++)
    {
        if(indexed == AlphUpper[i])
        {
            indexed = toupper(k[i]);
            return indexed;
        }
        else if(indexed == AlphLower[i])
        {
            indexed = tolower(k[i]);
            return indexed;
        }
    }
    return indexed;
}
