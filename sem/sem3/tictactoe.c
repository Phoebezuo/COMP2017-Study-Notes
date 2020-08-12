#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BUF_LEN (100)

char has_won(char board[][3], char c) {
    // check for horizontal completeness
    for (int i = 0; i < 3; i++) {
        int matched = 1; // assued they matched, by default it is true
        for (int j = 0; j < 3; j++) {
            // if (board[i][j] != c) {
            // dereference the array, 2d array in c are align in a linear line
            if ((char)*(*(board+(i*3)+j))) { // type casting from int to char
                matched = 0; // find one that not matched, return false
            }
        }
        if (matched) { return c; }
    }

    // check for vertical completeness
    for (int i = 0; i < 3; i++) {
        int matched = 1; // assued they matched, by default it is true
        for (int j = 0; j < 3; j++) {
            if (board[j][i] != c) {
                matched = 0; // find one that not matched, return false
            }
        }
        if (matched) { return c; }
    }

    // from top left to bottom right
    int diag_match1 = 1;
    for (int i = 0; i < 3; i++) {
        if (board[i][i] != c) {
            diag_match1 = 0;
        }
    }
    if (diag_match1) { return c; }

    // from top righct to bottom left
    int diag_match2 = 1;
    for (int i = 0; i < 3; i++) {
        if (board[i][2-i] != c) {
            diag_match2 = 0;
        }
    }
    if (diag_match2) { return c; }

    return 0;
}

void print_board(char board[3][3]) {
    for (int i = 0; i < 3; i++) {
        printf("|");
        for (int j = 0; j < 3; j++) {
            printf("%c|", board[i][j]);
        }
        puts("");
    }
}

int main(int argc, char** argv){
    char board[3][3];
    char buff[BUF_LEN];
    int x;
    int y;
    int turn = 0;
    char symbols[] = { 'X', 'O' };

    // memset(board[0], ' ', 3);
    // memset(board[1], ' ', 3);
    // memset(board[2], ' ', 3);
    memset(board, ' ', 9);

    while (fgets(buff, BUF_LEN, stdin)) {
        // sscanf return the number of input it scaned
        if(sscanf(buff, "%d %d", &x, &y) == 2){
            board[y][x] = symbols[turn];
            char result = has_won(board, symbols[turn]);
            turn = (turn + 1) % 2; // the values will always be 0 and 1
            print_board(board);

            if (result == 'X') {
                puts("X won!");
                return 0;
            } else if (result == 'O') {
                puts("O won!");
                return 0;
            }
        }
    }

    return 0;
}
