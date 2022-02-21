#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <unistd.h>

#define dim 9

void solve(int board[dim*dim]);
void get_square(int index, int square[dim], int board[dim*dim]);
int is_valid(int p, int n, int board[dim*dim]);
void print_grid(int board[dim*dim]);

int main() {
    //int board[dim*dim];

    int board[] = {
        9,0,0,0,0,0,4,0,0,
        0,0,0,5,0,0,0,0,0,
        0,0,6,0,1,7,0,0,2,
        6,0,0,0,8,5,0,9,0,
        0,0,5,2,0,0,0,0,0,
        0,0,0,3,0,0,0,0,8,
        0,0,0,0,3,0,0,0,0,
        0,1,0,0,0,0,0,2,0,
        0,0,7,0,6,8,0,0,1
    };

    solve(board);

    print_grid(board);

    return 0;
}

void solve(int board[dim*dim]) {
    int i, n;

    for(i = 0; i<dim*dim; i++) {
        if(board[i] == 0) {
            for(n = 1; n < 10; n++) {
                if(is_valid(i, n, board)) {
                    //print_grid(board);
                    //printf("\n");
                    board[i] = n;
                    solve(board);
                    board[i] = 0;
                }
            }
            return;
        }
    }
    printf("Done!\n");
    print_grid(board);
    exit(0);
}

// Checks for violations if placing n inside x y cords
int is_valid(int p, int n, int board[dim*dim]) {
    int i, frac, x_frac, y_frac, index;
    int y = p/dim;
    int x = p - (y*dim);

    /*if(n == 8 && p == 9)
        printf("p: %d x: %d y: %d\n", p, x, y);*/

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
    x_frac = (x/frac);
    y_frac = (y/frac) * frac;
    index = x_frac + y_frac;

    /*if(n == 8 && p == 9)
        printf("index: %d (%d + %d)\n", index, x_frac, y_frac);*/

    int square[9];
    get_square(index, square, board);

    /*if(n == 8 && p == 9)
        printf("square:\n");*/

    for(i = 0; i < dim; i++) {
        /*if(n == 8 && p == 9)
            printf("%d ", square[i]);*/
        if(square[i] == n) {
            return 0;
        }
    }

    printf("\n");

    /*if(n == 8 && p == 9)
        exit(0);*/

    return 1;
}

// Grab the 3x3 squares and give them as a 1d array
void get_square(int index, int square[dim], int board[dim*dim]) {
    int i, j;
    int x = 0; // Keeps track of loops
    int ddim = sqrt(dim);
    // offsets
    int y_off = index / ddim;
    int x_off = index % ddim;

    // Pick a ddim x ddim square depending on the index
    for(i = 0; i < ddim; i++)
            for(j = 0; j < ddim; j++)
                square[x++] = board[
                    (((y_off * ddim) + i) * dim) +
                    ((x_off * ddim) + j)
                ];
}

void print_grid(int board[dim*dim]) {
    int x = 0;
    for(int i = 0; i<dim*dim; i++) {
        printf("%d ", board[i]);
        if(x++ == 8) {
            printf("\n");
            x = 0;
        }
    }
    printf("\n");
}