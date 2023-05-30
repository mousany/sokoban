import random

def generate_map(width, height, boxes, walls):
    assert width * height > boxes + walls + 2, "Too many boxes and walls for the given dimensions."

    def random_empty_spot(board):
        while True:
            x = random.randint(0, width - 1)
            y = random.randint(0, height - 1)
            if board[y][x] == ' ':
                return x, y

    # Initialize the empty warehouse
    board = [[' ' for _ in range(width)] for _ in range(height)]

    # Add walls
    for _ in range(walls):
        x, y = random_empty_spot(board)
        board[y][x] = '#'

    # Add boxes
    for _ in range(boxes):
        x, y = random_empty_spot(board)
        board[y][x] = 'O'

    # Add goals
    for _ in range(boxes):
        x, y = random_empty_spot(board)
        board[y][x] = 'x'

    # Add the warehouse worker
    x, y = random_empty_spot(board)
    board[y][x] = '@'

    return board

def print_map(board):
    print("The generated map is:")
    for row in board:
            print(''.join(row))
    print("The generated map in C format is:")
    print("\"" + "".join([''.join(row) for row in board]) + "\"")

width = 20
height = 10
boxes = 1
walls = 1

board = generate_map(width, height, boxes, walls)
print_map(board)