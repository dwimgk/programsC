// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <stdlib.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// TODO: Choose number of buckets in hash table done?
// i have chosen 26 * 26 for the first two letters of each word
// const unsigned int N = 26;
const unsigned int N = 26 * 26;

int counter = 0;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    int index = hash(word);

    node *current = table[index];
    while (current != NULL)
    {
        if (strcasecmp(current->word, word) == 0)
        {
            return true;  // word found
        }
        current = current->next;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function done?
    // maybe word[0] and word[1]
    // so that there are 26 * 26 combos for the first two letters?
    // and so N would be 26 * 26 or sth
    // sourcecode
    // return toupper(word[0]) - 'A';
    int first = toupper(word[0]) - 'A';
    int second = (word[1] != '\0') ? toupper(word[1]) - 'A' : 0;
    if (first < 0 || first > 25)
    {
        first = 0;
    }
    if (second < 0 || second > 25)
    {
        second = 0;
    }

    return (26 * first) + second;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO done?
    FILE *source = fopen(dictionary, "r");
    if (source == NULL)
    {
        printf("Could open file %s.\n", dictionary);
        fclose(source);

        return false;
    }
    char word[LENGTH + 1];
    // EOF is the value -1, and is used to purely to ease understanding the code
    // so in this case, we are scanning each value until the file returns value (-1),
    // signaling it's end
    while (fscanf(source, "%45s", word) != EOF)
    {
        node *first_node = malloc(sizeof(node));
        if (first_node == NULL)
        {
            printf("Could not allocate memory.\n");
            //fclose(source);
            return false;
        }
        strcpy(first_node->word, word);
        first_node->next = NULL;

        int index = hash(word);

        first_node->next = table[index];
        table[index] = first_node;
        counter++;
    }

    fclose(source);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO done
    return counter;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    node *current = NULL;

    for (int i = 0; i < N; i++)
    {
        current = table[i];

        while (current != NULL)
        {
            node *temp = current;
            current = current->next;

            free(temp);
        }
    }
    return true;
}
