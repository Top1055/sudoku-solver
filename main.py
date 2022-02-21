import math

dim = 9

board = [
    0, 9, 0, 0, 1, 0, 0, 0, 7,
    0, 0, 5, 7, 6, 0, 0, 0, 4,
    0, 2, 0, 0, 0, 0, 0, 0, 6,
    0, 5, 0, 0, 7, 0, 9, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0,
    4, 0, 0, 0, 8, 0, 0, 0, 1,
    0, 0, 0, 2, 0, 6, 0, 0, 0,
    0, 0, 2, 0, 0, 8, 1, 0, 0,
    0, 8, 0, 0, 5, 0, 3, 0, 0];

def print_grid(board):
    for i in range(dim*dim):
        if(i % 9 == 1):
            print("\n" + board[i] + " ")
        else:
            print(board[i] + " ")

def solve(board):
    for i in range(dim*dim):
        if(board[i] == 0):
            for n in range(1, 10):
                if(is_valid(i, n, board)):
                    board[i] = n
                    solve(board)
                    board[i] = 0
            return
    print_grid(board)
    exit(0)

# Grab the 3x3 squares and give them as a 1d array
def get_square(index, board):
    ddim = int(math.sqrt(dim)) # Size of one side of the square
    y_off = int(index // ddim)
    x_off = int(index % ddim)
    square = []

    # Pick a ddim x ddim square depending on the index
    for i in range(ddim):
            for j in range(ddim):
                y = ((y_off*ddim) + i) * dim
                x = (x_off*ddim) + j
                square.append(board[y + x])

    return square

# Checks for violations if placing n inside x y cords
def is_valid(p, n, board):
    y = int(p/dim);
    x = p - int(y);

    for i in range(dim):
        # Check row
        if(board[(y*dim) + i] == n):
            return 0;

    for i in range(dim):
        # Check column
        if(board[x + (i*dim)] == n):
            return 0;

    # Check square
    frac = math.sqrt(dim);
    x_frac = (x // frac) * frac;
    y_frac = (y // frac) * frac;
    index = x_frac + (y_frac * frac);
    print(index)

    square = get_square(index, board);

    for i in range(dim):
        if(square[i] == n):
            return 0;

    return 1;

solve(board)