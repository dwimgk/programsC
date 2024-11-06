#include <ctype.h>
#include <cs50.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

bool only_digits(string k);
char cipher(char p, int key);

int main(int argc, string argv[])
{
    string k = argv[1];
    if (argc != 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
    if(only_digits(k) == false)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    string p = get_string("plaintext: ");
    int key= atoi(k);
    printf("ciphertext: ");
    for(int i = 0, n = strlen(p); i < n; i++)
    {
        printf("%c",cipher(p[i], key));
    }
    printf("\n");
    return 0;
}

bool only_digits(string k)
{
    for(int i=0,n=strlen(k);i<n;i++)
    {
        if(isdigit(k[i]) == false)
        {
            return false;
        }
    }
    return true;
}
char cipher(char p, int key)
{
    char indexed=p;
    if (indexed >= 'A' && indexed <= 'Z')
    {
        indexed = (indexed - 'A' + key) % 26 + 'A';
    }
    else if (indexed >= 'a' && indexed <= 'z')
    {
        indexed = (indexed - 'a' + key) % 26 + 'a';
    }
    return indexed;
}
