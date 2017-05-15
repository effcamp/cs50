/**
 * fifteen.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Implements Game of Fifteen (generalized to d x d).
 *
 * Usage: fifteen d
 *
 * whereby the board's dimensions are to be d x d,
 * where d must be in [DIM_MIN,DIM_MAX]
 *
 * Note that usleep is obsolete, but it offers more granularity than
 * sleep and is simpler to use than nanosleep; `man usleep` for more.
 */
 
#define _XOPEN_SOURCE 500

#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// constants
#define DIM_MIN 3
#define DIM_MAX 9

// board
int board[DIM_MAX][DIM_MAX];
int winboard[DIM_MAX][DIM_MAX];

// dimensions
int d;

// prototypes
void clear(void);
void greet(void);
void init(void);
void draw(void);
bool move(int tile);
bool won(void);
void swap(int* a, int* b);

int main(int argc, string argv[])
{
    // ensure proper usage
    if (argc != 2)
    {
        printf("Usage: fifteen d\n");
        return 1;
    }

    // ensure valid dimensions
    d = atoi(argv[1]);
    if (d < DIM_MIN || d > DIM_MAX)
    {
        printf("Board must be between %i x %i and %i x %i, inclusive.\n",
            DIM_MIN, DIM_MIN, DIM_MAX, DIM_MAX);
        return 2;
    }
    
    // create winning board (for later)
    int tot = 1;
    for (int i = 0; i < d; i++)
    {
        for (int j = 0; j < d; j++)
        {
            winboard[i][j] = tot;
            tot++;
        }
    }
    winboard[d-1][d-1] = 0;
    
    
    
    // open log
    FILE* file = fopen("log.txt", "w");
    if (file == NULL)
    {
        return 3;
    }

    // greet user with instructions
    greet();

    // initialize the board
    init();

    // accept moves until game is won
    while (true)
    {
        // clear the screen
        clear();

        // draw the current state of the board
        draw();

        // log the current state of the board (for testing)
        for (int i = 0; i < d; i++)
        {
            for (int j = 0; j < d; j++)
            {
                fprintf(file, "%i", board[i][j]);
                if (j < d - 1)
                {
                    fprintf(file, "|");
                }
            }
            fprintf(file, "\n");
        }
        fflush(file);

        // check for win
        if (won())
        {
            printf("ftw!\n");
            break;
        }

        // prompt for move
        printf("Tile to move: ");
        int tile = GetInt();
        
        // quit if user inputs 0 (for testing)
        if (tile == 0)
        {
            break;
        }

        // log move (for testing)
        fprintf(file, "%i\n", tile);
        fflush(file);

        // move if possible, else report illegality
        if (!move(tile))
        {
            printf("\nIllegal move.\n");
            usleep(500000);
        }

        // sleep thread for animation's sake
        usleep(500000);
    }
    
    // close log
    fclose(file);

    // success
    return 0;
}

/**
 * Clears screen using ANSI escape sequences.
 */
void clear(void)
{
    printf("\033[2J");
    printf("\033[%d;%dH", 0, 0);
}

/**
 * Greets player.
 */
void greet(void)
{
    clear();
    printf("WELCOME TO GAME OF FIFTEEN\n");
    usleep(2000000);
}

/**
 * Initializes the game's board with tiles numbered 1 through d*d - 1
 * (i.e., fills 2D array with values but does not actually print them).  
 */
void init(void)
{
    // Intializes the board using the total number of tiles (plus zero) and counts down until it gets to 0 to fill the board
    // if the sides of the board are even, it swaps the 2 and 1 for a playable game
    int tot = d*d-1;
    for (int i = 0; i < d; i++)
    {
        for (int j = 0; j < d; j++)
        {
            board[i][j] = tot;
            tot = tot-1;
        }
    }
    if (d % 2 == 0)
    {
        board[d-1][d-2] = 2;
        board[d-1][d-3] = 1;
    }
}

/**
 * Prints the board in its current state.
 */
void draw(void)
{
    // Prints the current configuration of the board. Replaces 0 with an underscore
    for (int i = 0; i < d; i++)
    {
        for (int j = 0; j < d; j++)
        {
            if (board[i][j] != 0)
                printf(" %2d ", board[i][j]);
            else
                printf("  _ ");
        }
        printf("\n\n");
    }
    printf("\n");
}

/**
 * If tile borders empty space, moves tile and returns true, else
 * returns false. 
 */
bool move(int tile)
{
    // Looks for the i and j values of the tile and zero. Checks to see if the i and j of the tile and zero match up for a legal move
    // If the move is legal, returns true. If not, returns false
    int zeroi, zeroj;
    int tmpi, tmpj;
    
    for (int i = 0; i < d; i++)
    {
        for (int j = 0; j < d; j++)
            if (tile == board[i][j])
            {
                tmpi = i;
                tmpj = j;
            }
            else if (board[i][j] == 0)
            {
                zeroi = i;
                zeroj = j;
            }
            
    }
    //A check to make sure that only the tiles vertical or horizontal to the blank piece can be moved
    // If they can be moved, swaps the two tiles
    if (zeroi == tmpi && ((zeroj == tmpj+1) || (zeroj == tmpj-1)))
    {
        swap(&board[tmpi][tmpj], &board[zeroi][zeroj]);
        return true;
    }
    else if (zeroj == tmpj && ((zeroi == tmpi+1) || (zeroi == tmpi-1)))
    {
        swap(&board[tmpi][tmpj], &board[zeroi][zeroj]);
        return true;
    }
    else
        return false;
}

/**
 * Returns true if game is won (i.e., board is in winning configuration), 
 * else false.
 */
bool won(void)
{
    // Compares the current state of the board with winboard that was set up in the main function
    // All the numbers are in the correct ascending order, with 0 being the last number, the counter will be equal to the total
    // number of tiles
    int tot = 0;
    
    for (int i = 0; i < d; i++)
    {
        for (int j = 0; j < d; j++)
        {
            if (board[i][j] == winboard[i][j])
                tot++;
        }
    }
    if (tot == d*d)
        return true;
    else
        return false;
}


// Swap function (just to look pretty and practice pointers)
void swap(int* a, int* b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}