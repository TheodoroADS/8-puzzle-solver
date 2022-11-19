#pragma once
#include <stdio.h>

typedef struct Board
{
    unsigned char N;
    unsigned char * board;
    unsigned char holei;
    unsigned char holej;
    unsigned int depth;
    struct Board* parent; 
}Board;


Board* newBoard(unsigned char N, unsigned char board[]);

Board * Boardfrom(Board * b , unsigned char swapi1,unsigned char swapj1,unsigned char swapi2, unsigned char swapj2 );

void deleteBoard(Board* b);

char isGoal(Board * b);

char manhattan(Board* b);

char equals(Board* b1 , Board * b);

char has_parent(Board* b);

double board_compare(Board* b1 , Board* b2);

void board_print_to(Board* b, FILE* stream );

void render(Board* b);

char board_is_solvable(Board* b);