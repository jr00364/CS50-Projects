#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX]; //** i has the edge over j(true) no edge (false)

// Each pair has a winner, loser
typedef struct //** includes the index of winner and loser
{
    int winner;
    int loser;
}
pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2]; //**maximum number of pairs as the winner doesnt have a pair?

int pair_count; //**number of pairs in array pairs
int candidate_count; //**number of candidates in array candidates

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
bool graph(int winner, int loser);
void print_winner(void);

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
    for (int i = 0; i < candidate_count; i++) //** assigning candidate names to candidates array
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
    for (int i = 0; i < voter_count; i++) //**for each voter
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++) //**for each candidate per voter
        {
            string name = get_string("Rank %i: ", j + 1); //**ranking all of the candidates given by each voter

            if (!vote(j, name, ranks)) //if vote is false
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
    //name matches candidate at location i, also put in the ranking at the same index in the ranks array
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(candidates[i], name) == 0) 
        {
            ranks[rank] = i;
            printf("candidate %s is %i\n", candidates[i], rank + 1);
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    // candidates are ranked, now to insert to the preferences
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            //if (ranks[i] > ranks[j]) //highest rank is 0, so if rank[i] is less than rank[j] candidate i out ranks candidate j
            {
                preferences[ranks[i]][ranks[j]] += 1;
                // printf("%s is preferred over %s\n", candidates[ranks[i]], candidates[ranks[j]]);
            }

        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            if (preferences[i][j] > preferences[j][i]) //if the number of victories of i are higher than j
            {
                pairs[pair_count].winner = i; //using pair_count instead of i becuase if theres a tie i will still increase
                pairs[pair_count].loser = j;
                pair_count += 1;
            }
            else if (preferences[i][j] < preferences[j][i])
            {
                pairs[pair_count].winner = j;
                pairs[pair_count].loser = i;
                pair_count += 1;
            }
        }
    }
    printf("number of pairs are: %i\n\n", pair_count);
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    pair temp;
    // out of the winning pairs who has the highest number of votes?
    for (int i = 0; i < pair_count; i++)
    {
        if (preferences[pairs[i].winner][pairs[i].loser] < preferences[pairs[i + 1].winner][pairs[i + 1].loser])
        {
            temp = pairs[i];
            pairs[i] = pairs[i + 1];
            pairs[i + 1] = temp;
        }
    }
    // print
    return;
}

bool graph(int winner, int loser)
{
    // if at some point the recursion below results in loser == winner, we have started a circle
    if (loser == winner)
    {
        return true;
    }
    for (int i = 0; i < candidate_count; i++) //first pair starts here
    {
        if (locked[loser][i]) // taking the edge that this loser may have on other candidates (loser is the winner here)
        {
            if (graph(winner, i)) // <- is this true or false ? and the original winner is the loser then a cirlce is create
            {
                // if the loser has an edge? 
                return true;
            }
        }
    }
    return false;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    // using winning pairs in add pairs
    for (int i = 0; i < pair_count; i++)
    {
        // if the graph fuction returns false, as in a cylce isnt made by adding an arrow
        if (!graph(pairs[i].winner, pairs[i].loser))
        {
            // lock in the pair
            locked[pairs[i].winner][pairs[i].loser] = true;
        }
    }
    return;
}

// Print the winner of the election
void print_winner(void)
{

    for (int i = 0; i < candidate_count; i++)
    {
        int won = 0;

        for (int j = 0; j < candidate_count; j++)
        {
            // if there isnt an edge
            if (locked[j][i] == false)
            {
                won++;

                if (won == candidate_count)
                {
                    printf("%s\n", candidates[i]);
                }
            }
            // if candidate has as many winning locked pairs as there are number of other candidates

        }
    }
    return;
}

