#ifndef __stdio_h_
#include <stdio.h>
#endif

#ifndef __string_h_
#include <string.h>
#endif

#ifndef __ttt_h_
#include "ttt.h"
#endif

// Initializes all board in htables to have an init value of 0
void init_boards() {
    for (int i = 0; i < HSIZE; i++) {
        htable[i].init = 0;
    }
}

// Returns the depth of the board - aka the number of moves that havce been made
int depth(Board board) {
    int count = 0;
    for (int i = 0; i < BSIZE; i++) {
        if (board[i] == 'X' || board[i] == 'O') {
            count += 1;
        }
    }
    return count;
}

// Returns the current state of the board
// X for X wins
// O for O wins
// - for tie
// ? for game in progress
char winner(Board board) {
    char last;
    int count = 0;
    for (int i = 0; i < 8; i++) {
        last = board[pos2idx[WINS[i][0]]];
        count += 1;
        for (int j = 1; j < 3; j++) {
            if (board[pos2idx[WINS[i][j]]] == last) {
                count += 1;
                if (count == 3 && (last == 'X' || last == 'O')) {
                    return last;
                }
            } else {
                count = 0;
                break;
            }
        }
    }
    if (depth(board) == 9) {
        return '-';
    } else {
        return '?';
    }
}

// Returns the player whos turn it is currently
// Returns - when the game is over
char turn(Board board) {
    int count = depth(board);

    if (winner(board) != '?') {
        return '-';
    } else if (count % 2 == 0 || count == 0) {
        return 'X';
    } else {
        return 'O';
    }
}

// Creates a new BoardRecord and initializes its values
void init_board(Board board) {
    int hash = board_hash(board);

    htable[hash].init = 1;
    htable[hash].turn = turn(board);
    htable[hash].depth = depth(board);
    strcpy(htable[hash].board, board);
    htable[hash].winner = winner(board);
}

// Connects the nodes together via the moves array
void join_graph(Board board) {
    int hash;
    int newHash;
    char nextChar;
    char nextBoard[BSIZE];
    for (int i = 0; i < 9; i++) {
        hash = board_hash(board);
        if (board[pos2idx[i]] == 'X' || board[pos2idx[i]] == 'O') {
            htable[hash].move[i] = -1; 
        } else {
            nextChar = htable[hash].turn;
            strcpy(nextBoard, board);
            nextBoard[pos2idx[i]] = nextChar;
            newHash = board_hash(nextBoard);
            htable[hash].move[i] = newHash;
            if (htable[newHash].init == 0) {
                init_board(nextBoard);
                if(htable[newHash].winner == '?'){
                    join_graph(nextBoard);
                } else {
                    for(int j = 0; j < 9; j++){
                        htable[newHash].move[j] = -1;
                    }
                }
            }
        }
    }
}

// Computes the score of each possible board
// 1 for X advantage
// -1 for O advantage
// 0 for tie/no advantage
void compute_score(){
    int first;
    for(int i = 9; i > 0; i--){
        for(int j = 0; j < HSIZE; j++){
            if(htable[j].depth == i && htable[j].init == 1){
                if(htable[j].winner == 'X'){
                    htable[j].score = 1;
                } else if(htable[j].winner == 'O') {
                    htable[j].score = -1;
                } else if(htable[j].winner == '-'){
                    htable[j].score = 0;
                } else {
                    first = 1;
                    for(int k = 0; k < 9; k++){
                        if(htable[j].move[k] != -1){
                            if(first){
                                htable[j].score = htable[htable[j].move[k]].score;
                                first = 0;
                            } else if(htable[j].turn == 'X' && htable[htable[j].move[k]].score > htable[j].score){
                                htable[j].score = htable[htable[j].move[k]].score;
                            } else if(htable[j].turn == 'O' && htable[htable[j].move[k]].score < htable[j].score){
                                htable[j].score = htable[htable[j].move[k]].score;
                            }
                        }
                    }
                }
            }
        }
    }
}

// Returns the best move for a given player at a given turn
int best_move(int board){
    int bestHash;
    int bestScore;
    int bestMove;
    int first = 1;
    for(int i = 0; i < 9; i++){
        if(htable[board].move[i] != -1){
            if(first) {
                bestHash = htable[board].move[i];
                bestScore = htable[bestHash].score;
                bestMove = i;
                first = 0;
            } else if(htable[board].turn == 'X' && htable[htable[board].move[i]].score > bestScore){
                bestHash = htable[board].move[i];
                bestScore = htable[bestHash].score;
                bestMove = i;
            } else if(htable[board].turn == 'O' && htable[htable[board].move[i]].score < bestScore){
                bestHash = htable[board].move[i];
                bestScore = htable[bestHash].score;
                bestMove = i;
            }
        }
    }
    return bestMove;
}