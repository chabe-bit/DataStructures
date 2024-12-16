#include <stdio.h>
#include <stdbool.h>
#include "utility.c"
// Backtracking algorithm:
// The backtracking algorithm can be visualzied as a tree, where every 
// node is a potential candidate for solving said problem. Iterate through
// the branches of each node, and if it happens to be incorrect, we reject
// or "backtrack" to the starting point of the node and move to the next.

// GOAL: Find the total count of arrangements of an 8x8 board, number of solutions and compare results - 8 queens puzzle. 

#define ROWS 8
#define COLS 8

// First, I need to check if all angles are valid, row, col, diagnol and anti-diagnal
bool check_angles(int board[ROWS][COLS], int row, int col)
{
    // Check row
    for (int i = 0; i < ROWS; i++)
        if (board[row][i] == 1)
            return false;

    // Check col
    //for (int i = 0; i < COLS; i++)
    //    if (board[0][i] == 1)
    //        return false;

    // Check diagnal
    for (int i = row, j = col; i >= 0 && j >= 0; i--, j--)
        if (board[i][j] == 1) 
            return false;

    // Check anti-diagnal
    for (int i = row, j = col; i < ROWS && j >= 0; i++, j--)
        if (board[i][j] == 1) 
            return false;

    return true;
}


void draw_my_map(int board[ROWS][COLS])
{
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            board[i][j] = 0;
        }
    }
    
    for (int i = 0; i < ROWS; i++)
    {
        board[i][i] = 1;
    }

    for (int i = 0; i < ROWS ; i++)
    {
        board[i][COLS - i - 1] = 1;
    }

    // draw full map  
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            printf("%d ", board[i][j]);
        }
        printf("\n");
    }

    // draw anti-diagnal
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            if (j == COLS - i - 1)
            {
                printf("%d ", board[i][j]);
            }
            else 
            {
                printf(" ");  
            }
        }
        printf("\n");
    }
}


bool solve_queens(int board[ROWS][COLS], int col, int total_combinations, int total_solutions)
{
    // Begins with a queen on the first column
    // Proceed to place a new queen until it's safe 
    // If it's not safe, backtrack to the previous column on a new row

    if (col == ROWS)
    {
        *total_solutions++;
        for (int i = 0; i < ROWS; i++)
        {
            for (int j = 0; j < COLS; j++)
            {
                printf("%d ", board[i][j]);
            }  
            printf("\n");
        }

        return true;
    }
    
    for (int i = 0; i < ROWS; i++)
    {
        *total_combinations++;
        // Place a queen if no other queens are in sight 
        if (check_angles(board, i, col))
        {
            board[i][col] = 1;
            if (solve_queens(board, col + 1, total_combinations, total_solutions))
                return true;
            board[i][col] = 0;
        }
    }

    // end index - starting index to wrap back


    return false;
}




int main()
{
    Stack stack = {0};
    init_stack(&stack);

    int board[ROWS][COLS] = {0};
    int total_combinations = 0;
    int total_solutions = 0;

    if (!(solve_queens(board, 0, &total_combinations, &total_solutions)))
    {
        printf("Not solved!\n");
    }

    printf("Total Combinations: %d\n", total_combinations); 
    printf("Total Solutions: %d\n", total_solutions); 

    return 0;
}
