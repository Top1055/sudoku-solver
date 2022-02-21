#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define dim 9

void solve(int board[dim*dim]);
void get_square(int index, int square[dim], int board[dim*dim]);
int is_valid(int p, int n, int board[dim*dim]);
void print_grid(int board[dim*dim]);

int main() {
    //int board[dim*dim];

    int board[] = {
        5, 3, 0, 0, 7, 0, 0, 0, 0,
        6, 0, 0, 1, 9, 5, 0, 0, 0,
        0, 9, 8, 0, 0, 0, 0, 6, 0,
        8, 0, 0, 0, 6, 0, 0, 0, 3,
        4, 0, 0, 8, 0, 3, 0, 0, 1,
        7, 0, 0, 0, 2, 0, 0, 0, 6,
        0, 6, 0, 0, 0, 0, 2, 8, 0,
        0, 0, 0, 4, 1, 9, 0, 0, 5,
        0, 0, 0, 0, 8, 0, 0, 7, 9};

    solve(board);

    return 0;
}

void solve(int board[dim*dim]) {
    int i, n;

    for(i = 0; i<dim*dim; i++) {
        if(board[i] == 0) {
            for(n = 1; n < 10; n++) {
                if(is_valid(i, n, board)) {
                    board[i] = n;
                    solve(board);
                    board[i] = 0;
                }
            }
            return;
        }
    }
    print_grid(board);
    exit(0);
}

// Checks for violations if placing n inside x y cords
int is_valid(int p, int n, int board[dim*dim]) {
    int i, frac, x_frac, y_frac, index;
    int y = p/dim;
    int x = p - y;

    for(i = 0; i<dim; i++)
        // Check row
        if(board[(y*dim) + i] == n)
            return 0;

    for(i = 0; i<dim; i++)
        // Check column
        if(board[x + (i*dim)] == n)
            return 0;

    // Check square
    frac = sqrt(dim);
    x_frac = (x/frac) * frac;
    y_frac = (y/frac) * frac;
    index = x_frac + (y_frac * frac);

    int square[9];
    get_square(index, square, board);

    for(i = 0; i < dim; i++)
        if(square[i] == n) {
            return 0;
        }

    return 1;
}

// Grab the 3x3 squares and give them as a 1d array
void get_square(int index, int square[dim], int board[dim*dim]) {
    int i;
    int j;
    int x = 0; // Keeps track of loops
    int transform = 3*index;
    int ddim = sqrt(dim); // Size of one side of the square

    // Pick a ddim x ddim square depending on the index
    for(i = transform; i < transform + ddim; i++)
            for(j = transform; j < transform + ddim; j++)
                square[x++] = board[(i*dim) + j];
}

void print_grid(int board[dim*dim]) {
    printf("\n");
    for(int i = 0; i<dim*dim; i++)
        if(i % 9 == 1)
            printf("\n%d", board[i]);
        else
            printf("%d ", board[i]);
}