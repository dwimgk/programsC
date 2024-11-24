#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
} pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);
bool cyclic(int edge, int end);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    for (int current_candidate = 0; current_candidate < candidate_count; current_candidate++)
    {
        if (strcmp(name, candidates[current_candidate]) == 0)
        {
            ranks[rank] = current_candidate;
            // printf("%i",ranks[0]);
            // printf("%i",ranks[1]);
            // printf("%i",ranks[2]);
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    for (int leading_candidate = 0; leading_candidate < candidate_count; leading_candidate++)
    {
        for (int secondary_candidate = 0; secondary_candidate < candidate_count;
             secondary_candidate++)
        {
            // if(leading_candidate == ranks[secondary_candidate] && leading_candidate !=
            // secondary_candidate)
            // {
            //     preferences[leading_candidate][secondary_candidate]++;
            // }
            if (ranks[leading_candidate] != ranks[secondary_candidate] &&
                leading_candidate < secondary_candidate)
            {
                preferences[ranks[leading_candidate]][ranks[secondary_candidate]]++;
            }
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    // int pairing = 0;
    for (int candidate = 0; candidate < candidate_count; candidate++)
    {
        for (int opposition = candidate + 1; opposition < candidate_count; opposition++)
        {
            if (preferences[candidate][opposition] > preferences[opposition][candidate])
            {
                pairs[pair_count].winner = candidate;
                pairs[pair_count].loser = opposition;
                pair_count++;
                // pairing++;
            }
            else if (preferences[candidate][opposition] < preferences[opposition][candidate])
            {
                pairs[pair_count].winner = opposition;
                pairs[pair_count].loser = candidate;
                pair_count++;
                // pairing++;
            }
        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    for (int first_pair = 0; first_pair < pair_count; first_pair++)
    {
        for (int second_pair = 0; second_pair < pair_count; second_pair++)
        {
            if (preferences[pairs[first_pair].winner][pairs[first_pair].loser] >
                preferences[pairs[second_pair].winner][pairs[second_pair].loser])
            {
                pair temp = pairs[first_pair];
                pairs[first_pair] = pairs[second_pair];
                pairs[second_pair] = temp;
            }
        }
    }
    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    for (int pairing = 0; pairing < pair_count; pairing++)
    {
        int edge = pairs[pairing].winner;
        int end = pairs[pairing].loser;
        if (!cyclic(edge, end))
        {
            locked[edge][end] = true;
        }
    }
    return;
}

bool cyclic(int edge, int end)
{
    if (end == edge)
    {
        return true;
    }
    for (int cycle_checker = 0; cycle_checker < candidate_count; cycle_checker++)
    {
        if (locked[end][cycle_checker] == true && cyclic(edge, cycle_checker))
        {
            return true;
        }
    }
    return false;
}

// Print the winner of the election
void print_winner(void)
{
    for (int candidate = 0; candidate < candidate_count; candidate++)
    {
        bool is_source = true;
        for (int opposition = 0; opposition < candidate_count; opposition++)
        {
            if (locked[opposition][candidate] == true)
            {
                is_source = false;
                break;
            }
        }
        if (is_source == true)
        {
            printf("%s\n", candidates[candidate]);
            //return;
        }
    }
    return;
}
